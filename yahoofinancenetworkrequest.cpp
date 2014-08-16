/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#include <QDebug>
#include <QNetworkRequest>
#include "yahoofinancenetworkrequest.h"
#include "yahoofinance.h"

const int MILLISECONDS_IN_SECOND       = 1000;
const int HTTP_REPLY_CODE_OK           = 200; // 200 OK
const int HTTP_REPLY_MOVED_PERMANENTLY = 301; // 301 Moved Permanently

YahooFinanceNetworkRequest::YahooFinanceNetworkRequest(
        const QString &rQueryIdentifier,
        const QString &rUrl,
        const QStringList &rTickers,
        const QList<YahooFinance::StockParameter> &rParameters,
        QNetworkAccessManager &rNetworkManager,
        QObject *parent) : QObject(parent),
        mQueryIdentifier(rQueryIdentifier),
        mUrl(rUrl),
        mTickers(rTickers),
        mParameters(rParameters),
        mrNetworkManager(rNetworkManager)
{
    connect(&mTimer, SIGNAL(timeout()), SLOT(sendRequest()));
    connect(&mrNetworkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(handleReply(QNetworkReply*)));
}

bool YahooFinanceNetworkRequest::start(quint32 intervalSec)
{
    qDebug() << "YahooFinanceNetworkRequest::start, url:" << mUrl
             << ", interval:" << intervalSec;
    bool request_sent = sendRequest();
    request_sent ? mTimer.start(intervalSec * MILLISECONDS_IN_SECOND) : mTimer.stop();
    return request_sent;
}

void YahooFinanceNetworkRequest::stop()
{
    mpNetworkReply.reset();
    mTimer.stop();
}

bool YahooFinanceNetworkRequest::sendRequest()
{
    qDebug() << "YahooFinanceNetworkRequest::sendRequest, url:" << mUrl;
    if (!mUrl.isValid())
    {
        qDebug() << "YahooFinanceNetworkRequest::sendRequest, invalid URL, request not sent";
        return false;
    }

    mpNetworkReply.reset(mrNetworkManager.get(QNetworkRequest(mUrl)));
    return true;
}

void YahooFinanceNetworkRequest::handleReply(QNetworkReply *pReply)
{
    if (!pReply)
    {
        qDebug() << "YahooFinanceNetworkRequest::handleReply, null handle, ignored";
        return;
    }

    if (pReply == mpNetworkReply.data())
    {
        qDebug() << "YahooFinanceNetworkRequest::handleReply, reply belongs to us, parsing data...";
        const QVariant http_status_code = pReply->attribute(
                    QNetworkRequest::HttpStatusCodeAttribute);
        bool is_error = pReply->error() != QNetworkReply::NoError;

        qDebug() << "YahooFinanceNetworkRequest::handleReply, HTTP status:"
                 << http_status_code.toString()
                 << ", is error:" << is_error;
        if (!is_error && HTTP_REPLY_CODE_OK == http_status_code.toInt())
        {
            int line_index = 0;
            while (pReply->canReadLine() && mTickers.count() > line_index)
            {
                const QString line(pReply->readLine());
                const QString ticker = mTickers.at(line_index);
                const QStringList data = line.simplified().split(",");
                if (mParameters.count() == data.count())
                {
                    QMap<YahooFinance::StockParameter, QString> data_mappings;
                    for (int value_index = 0; value_index < data.count(); value_index++)
                    {
                        const YahooFinance::StockParameter param = mParameters.at(value_index);
                        const QString value = data.at(value_index);
                        qDebug() << "ticker:" << ticker << ", param:" << param << ", value:" << value;
                        data_mappings.insert(param, value);
                    }

                    emit parametersReceived(mQueryIdentifier, ticker, data_mappings);
                }
                else
                {
                    handleError();
                }
                line_index++;
            }
        }
        else if (HTTP_REPLY_MOVED_PERMANENTLY == http_status_code)
        {
            const QVariant redirection_url = pReply->attribute(
                        QNetworkRequest::RedirectionTargetAttribute);
            qDebug() << "Moved permanently, url:" << redirection_url;
            mUrl.setUrl(redirection_url.toString());
            sendRequest();
        }
        else
        {
            handleError();
            qDebug() << "YahooFinanceNetworkRequest::handleReply, ERROR";
        }

        mpNetworkReply.reset();
    }
    else
    {
        qDebug() << "YahooFinanceNetworkRequest::handleReply, unknown handle, not handled";
        pReply->deleteLater();
    }
}

void YahooFinanceNetworkRequest::handleError()
{
    stop();
    emit errorOccured(mQueryIdentifier);
}

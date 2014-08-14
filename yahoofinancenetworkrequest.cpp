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
        const QString &rUrl,
        const QStringList &rTickers,
        const QList<YahooFinance::StockParameter> &rParameters,
        quint32 intervalSec,
        QObject *parent) : QObject(parent),
        mUrl(rUrl),
        mTickers(rTickers),
        mParameters(rParameters),
        mpNetworkManager(new QNetworkAccessManager)
{
    qDebug() << "YahooFinanceNetworkRequest::YahooFinanceNetworkRequest, URL:"
                << rUrl << ", interval:" << intervalSec;
    mTimer.setInterval(intervalSec * MILLISECONDS_IN_SECOND);
    mTimer.setSingleShot(false);

    connect(&mTimer, SIGNAL(timeout()), SLOT(sendRequest()));
    connect(mpNetworkManager.data(), SIGNAL(finished(QNetworkReply*)),
            SLOT(handleReply(QNetworkReply*)));
}

void YahooFinanceNetworkRequest::start()
{
    qDebug() << "YahooFinanceNetworkRequest::start, url:" << mUrl;
    sendRequest();
    mTimer.start();
}

void YahooFinanceNetworkRequest::sendRequest()
{
    qDebug() << "YahooFinanceNetworkRequest::sendRequest, url:" << mUrl;
    if (!mUrl.isValid())
    {
        qDebug() << "YahooFinanceNetworkRequest::sendRequest, invalid URL, request not sent";
        return;
    }

    mpNetworkReply.reset(mpNetworkManager->get(QNetworkRequest(mUrl)));
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
            const QString reply_data(pReply->readAll());
            qDebug() << "YahooFinanceNetworkRequest::handleReply, success, data:"
                     << reply_data;
            // TODO: parse reply data
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
            // TODO: handle error
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

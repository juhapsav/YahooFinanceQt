/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#include <QDebug>
#include "yahoofinancenetworkrequest.h"
#include "yahoofinance.h"

const int MILLISECONDS_IN_SECOND = 1000;

YahooFinanceNetworkRequest::YahooFinanceNetworkRequest(
        const QString &rUrl,
        const QList<YahooFinance::StockParameter> &rParameters,
        quint32 intervalSec,
        QObject *parent) : QObject(parent),
        mUrl(rUrl),
        mParameters(rParameters)
{
    qDebug() << "YahooFinanceNetworkRequest::YahooFinanceNetworkRequest, URL:"
                << rUrl << ", interval:" << intervalSec;
    mTimer.setInterval(intervalSec * MILLISECONDS_IN_SECOND);
    mTimer.setSingleShot(false);

    connect(&mTimer, SIGNAL(timeout()), SLOT(sendRequest()));
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
}

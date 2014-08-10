/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#include <QDebug>
#include <QStringList>
#include <QFlags>
#include "yahoofinance.h"
#include "YahooFinanceDefs.h"

using namespace DwellDone::YahooFinance;

QMap<YahooFinance::StockParameter, QString> YahooFinance::msParameterMappings = initMappings();

YahooFinance::YahooFinance()
{
}

void YahooFinance::query(const QStringList &rTickers, YahooFinance::StockParameters parameters)
{
    if (rTickers.isEmpty() || !parameters)
    {
        qDebug() << "YahooFinance::query, tickers or parameters undefined";
        return;
    }

    qDebug() << "YahooFinance::query, tickers:" << rTickers;
    const QString query_string = YAHOO_FINANCE_QUERY_FORMAT.arg(
                convertTickers(rTickers)).arg(convertParameters(parameters));
    qDebug() << "YahooFinance::query, query string:" << query_string;

    // TODO: HTTP request
}

QString YahooFinance::convertTickers(const QStringList &rTickers)
{
    QString converted_tickers;

    QStringList tickers(rTickers);
    while (!tickers.isEmpty())
    {
        const QString ticker = tickers.takeFirst();
        converted_tickers.append(ticker);
        converted_tickers.append(tickers.isEmpty() ? QString() : "+");
    }
    qDebug() << "YahooFinance::convertTickers, tickers:" << converted_tickers;
    return converted_tickers;
}

QString YahooFinance::convertParameters(YahooFinance::StockParameters parameters)
{
    QString converted_parameters;
    QMapIterator<YahooFinance::StockParameter, QString> iterator(msParameterMappings);
    while (iterator.hasNext())
    {
        iterator.next();
        if (parameters.testFlag(iterator.key()))
        {
            converted_parameters.append(iterator.value());
        }
    }
    qDebug() << "YahooFinance::convertParameters, parameters:" << converted_parameters;
    return converted_parameters;
}

QMap<YahooFinance::StockParameter, QString> YahooFinance::initMappings()
{
    QMap<StockParameter, QString> mappings;
    if (mappings.isEmpty())
    {
        mappings.insert(YAHOO_FINANCE_PARAMETER_DIVIDEND_YIELD, DIVIDEND_YIELD);
        mappings.insert(YAHOO_FINANCE_PARAMETER_DIVIDEND_PER_SHARE, DIVIDEND_PER_SHARE);
        mappings.insert(YAHOO_FINANCE_PARAMETER_DIVIDEND_PAY_DATE, DIVIDEND_PAY_DATE);
        mappings.insert(YAHOO_FINANCE_PARAMETER_EX_DIVIDEND_DATE, EX_DIVIDEND_DATE);
        mappings.insert(YAHOO_FINANCE_PARAMETER_CHANGE_PERCENT_REALTIME, CHANGE_PERCENTAGE_REALTIME);
        mappings.insert(YAHOO_FINANCE_PARAMETER_YEAR_RANGE, YEAR_RANGE);
        mappings.insert(YAHOO_FINANCE_PARAMETER_NAME, NAME);
        mappings.insert(YAHOO_FINANCE_PARAMETER_PE_REALTIME, PE_REALTIME);
    }

    return mappings;
}

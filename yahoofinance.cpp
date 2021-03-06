/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#include <QDebug>
#include <QStringList>
#include <QList>
#include <QUuid>
#include "yahoofinance.h"
#include "yahoofinancenetworkrequest.h"
#include "YahooFinanceDefs.h"

using namespace DwellDone::YahooFinance;

QMap<YahooFinance::StockParameter, QString> YahooFinance::msParameterMappings = initMappings();

YahooFinance::YahooFinance(QObject *pParent) : QObject(pParent),
    mpNetworkManager(new QNetworkAccessManager)
{
}

YahooFinance::~YahooFinance()
{
    qDeleteAll(mNetworkRequests);
}

QString YahooFinance::query(const QStringList &rTickers,
                         const QList<YahooFinance::StockParameter> &rParameters)
{
    if (rTickers.isEmpty() || rParameters.isEmpty())
    {
        qDebug() << "YahooFinance::query, tickers or parameters undefined";
        return QString();
    }

    // TODO: check if existing query is already handling the given tickers and parameters

    const QString identifier = QUuid::createUuid().toString();

    const QString query_string = YAHOO_FINANCE_QUERY_FORMAT.arg(
                convertTickers(rTickers)).arg(convertParameters(rParameters));

    YahooFinanceNetworkRequest *p_request =
            new YahooFinanceNetworkRequest(identifier, query_string, rTickers,
                                           rParameters, *mpNetworkManager);
    connect(p_request,
            SIGNAL(parametersReceived(const QString &,
                                      const QString &,
                                      const QMap<YahooFinance::StockParameter, QString> &)),
            SIGNAL(parameterReceived(const QString &,
                                     const QString &,
                                     const QMap<YahooFinance::StockParameter, QString> &)));
    connect(p_request, SIGNAL(errorOccured(const QString &)),
            SIGNAL(errorOccured(const QString &)));

    mNetworkRequests.insert(identifier, p_request);
    return identifier;
}

bool YahooFinance::start(const QString &rQueryIdentifier, quint32 intervalSec)
{
    return mNetworkRequests.contains(rQueryIdentifier)
            ? mNetworkRequests.value(rQueryIdentifier)->start(intervalSec) : false;
}

bool YahooFinance::stop(const QString &rQueryIdentifier)
{
    if (!mNetworkRequests.contains(rQueryIdentifier))
    {
        qDebug() << "Unknown query identifier";
        return false;
    }

    QScopedPointer<YahooFinanceNetworkRequest> request(
                mNetworkRequests.take(rQueryIdentifier));
    request->stop();
    return true;
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

QString YahooFinance::convertParameters(const QList<YahooFinance::StockParameter> &rParameters)
{
    QString converted_parameters;

    QListIterator<YahooFinance::StockParameter> iterator(rParameters);
    while (iterator.hasNext())
    {
        converted_parameters.append(msParameterMappings.value(iterator.next(), QString()));
    }
    qDebug() << "YahooFinance::convertParameters, parameters:" << converted_parameters;
    return converted_parameters;
}

// TODO: move to utils
QMap<YahooFinance::StockParameter, QString> YahooFinance::initMappings()
{
    QMap<StockParameter, QString> mappings;
    if (mappings.isEmpty())
    {
        mappings.insert(YAHOO_FINANCE_PROPERTY_ASK, YAHOO_FINANCE_PROPERTY_ASK_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_BID, YAHOO_FINANCE_PROPERTY_BID_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_ASK_REALTIME, YAHOO_FINANCE_PROPERTY_ASK_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_BID_REALTIME, YAHOO_FINANCE_PROPERTY_BID_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PREVIOUS_CLOSE, YAHOO_FINANCE_PROPERTY_PREVIOUS_CLOSE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_OPEN, YAHOO_FINANCE_PROPERTY_OPEN_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DIVIDEND_YIELD, YAHOO_FINANCE_PROPERTY_DIVIDEND_YIELD_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DIVIDEND_PER_SHARE, YAHOO_FINANCE_PROPERTY_DIVIDEND_PER_SHARE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DIVIDEND_PAY_DATE, YAHOO_FINANCE_PROPERTY_DIVIDEND_PAY_DATE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DIVIDEND_EX_DATE, YAHOO_FINANCE_PROPERTY_DIVIDEND_EX_DATE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE, YAHOO_FINANCE_PROPERTY_CHANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_AND_PERCENT_CHANGE, YAHOO_FINANCE_PROPERTY_CHANGE_AND_PERCENT_CHANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_REALTIME, YAHOO_FINANCE_PROPERTY_CHANGE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_PERCENTAGE_REALTIME, YAHOO_FINANCE_PROPERTY_CHANGE_PERCENTAGE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_IN_PERCENT, YAHOO_FINANCE_PROPERTY_CHANGE_IN_PERCENT_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_DATE, YAHOO_FINANCE_PROPERTY_LAST_TRADE_DATE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_TRADE_DATE, YAHOO_FINANCE_PROPERTY_TRADE_DATE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_TIME, YAHOO_FINANCE_PROPERTY_LAST_TRADE_TIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_AFTER_HOURS_CHANGE_REALTIME, YAHOO_FINANCE_PROPERTY_AFTER_HOURS_CHANGE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_COMMISSION, YAHOO_FINANCE_PROPERTY_COMMISSION_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_LOW, YAHOO_FINANCE_PROPERTY_DAY_LOW_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_HIGH, YAHOO_FINANCE_PROPERTY_DAY_HIGH_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_REALTIME_WITH_TIME, YAHOO_FINANCE_PROPERTY_LAST_TRADE_REALTIME_WITH_TIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_WITH_TIME, YAHOO_FINANCE_PROPERTY_LAST_TRADE_WITH_TIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_PRICE_ONLY, YAHOO_FINANCE_PROPERTY_LAST_TRADE_PRICE_ONLY_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_ONE_YEAR_TARGET_PRICE, YAHOO_FINANCE_PROPERTY_ONE_YEAR_TARGET_PRICE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_FROM_200_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_CHANGE_FROM_200_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_200_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_200_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_FROM_50_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_CHANGE_FROM_50_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_50_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_50_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_50_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_50_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_200_DAY_MOVING_AVERAGE, YAHOO_FINANCE_PROPERTY_200_DAY_MOVING_AVERAGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE, YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_REALTIME, YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PRICE_PAID, YAHOO_FINANCE_PROPERTY_PRICE_PAID_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_RANGE, YAHOO_FINANCE_PROPERTY_DAY_RANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_DAY_RANGE_REALTIME, YAHOO_FINANCE_PROPERTY_DAY_RANGE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT, YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_ANNUALIZED_GAIN, YAHOO_FINANCE_PROPERTY_ANNUALIZED_GAIN_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN, YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_REALTIME, YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_REALTIME, YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_YEAR_HIGH, YAHOO_FINANCE_PROPERTY_YEAR_HIGH_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_YEAR_LOW, YAHOO_FINANCE_PROPERTY_YEAR_LOW_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_LOW, YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_LOW_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_HIGH, YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_HIGH_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_LOW, YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_LOW_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_HIGH, YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_HIGH_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_YEAR_RANGE, YAHOO_FINANCE_PROPERTY_YEAR_RANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_MORE_INFO, YAHOO_FINANCE_PROPERTY_MORE_INFO_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_MARKET_CAPITALIZATION, YAHOO_FINANCE_PROPERTY_MARKET_CAPITALIZATION_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_MARKET_CAP_REALTIME, YAHOO_FINANCE_PROPERTY_MARKET_CAP_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_FLOAT_SHARES, YAHOO_FINANCE_PROPERTY_FLOAT_SHARES_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_NAME, YAHOO_FINANCE_PROPERTY_NAME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_NOTES, YAHOO_FINANCE_PROPERTY_NOTES_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_SYMBOL, YAHOO_FINANCE_PROPERTY_SYMBOL_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_SHARES_OWNED, YAHOO_FINANCE_PROPERTY_SHARES_OWNED_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_STOCK_EXCHANGE, YAHOO_FINANCE_PROPERTY_STOCK_EXCHANGE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_SHARES_OUTSTANDING, YAHOO_FINANCE_PROPERTY_SHARES_OUTSTANDING_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_VOLUME, YAHOO_FINANCE_PROPERTY_VOLUME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_ASK_SIZE, YAHOO_FINANCE_PROPERTY_ASK_SIZE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_BID_SIZE, YAHOO_FINANCE_PROPERTY_BID_SIZE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LAST_TRADE_SIZE, YAHOO_FINANCE_PROPERTY_LAST_TRADE_SIZE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_AVERAGE_DAILY_VOLUME, YAHOO_FINANCE_PROPERTY_AVERAGE_DAILY_VOLUME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_EARNINGS_PER_SHARE, YAHOO_FINANCE_PROPERTY_EARNINGS_PER_SHARE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_CURRENT_YEAR, YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_CURRENT_YEAR_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_YEAR, YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_YEAR_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_QUARTER, YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_QUARTER_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_BOOK_VALUE, YAHOO_FINANCE_PROPERTY_BOOK_VALUE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_EBITDA, YAHOO_FINANCE_PROPERTY_EBITDA_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PRICE_PER_SALES, YAHOO_FINANCE_PROPERTY_PRICE_PER_SALES_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PRICE_PER_BOOK, YAHOO_FINANCE_PROPERTY_PRICE_PER_BOOK_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PE_RATIO, YAHOO_FINANCE_PROPERTY_PE_RATIO_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PE_RATIO_REALTIME, YAHOO_FINANCE_PROPERTY_PE_RATIO_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PEG_RATIO, YAHOO_FINANCE_PROPERTY_PEG_RATIO_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_CURRENT_YEAR, YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_CURRENT_YEAR_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_NEXT_YEAR, YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_NEXT_YEAR_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_SHORT_RATIO, YAHOO_FINANCE_PROPERTY_SHORT_RATIO_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_TICKER_TREND, YAHOO_FINANCE_PROPERTY_TICKER_TREND_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_TRADE_LINKS, YAHOO_FINANCE_PROPERTY_TRADE_LINKS_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_ORDER_BOOK_REALTIME, YAHOO_FINANCE_PROPERTY_ORDER_BOOK_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HIGH_LIMIT, YAHOO_FINANCE_PROPERTY_HIGH_LIMIT_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_LOW_LIMIT, YAHOO_FINANCE_PROPERTY_LOW_LIMIT_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE, YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_REALTIME, YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_REALTIME_KEY);
        mappings.insert(YAHOO_FINANCE_PROPERTY_REVENUE, YAHOO_FINANCE_PROPERTY_REVENUE_KEY);
    }

    return mappings;
}

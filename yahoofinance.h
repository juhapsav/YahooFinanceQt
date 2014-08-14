/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#ifndef YAHOOFINANCE_H
#define YAHOOFINANCE_H

#include <QMap>
#include <QList>
#include <QStringList>
#include "yahoofinance_global.h"

class YahooFinanceNetworkRequest;

/*
 * Provides access to financial data provided by Yahoo Finance
 */
class YAHOOFINANCESHARED_EXPORT YahooFinance
{
public:
    YahooFinance();
    virtual ~YahooFinance();

    enum StockParameter
    {
        YAHOO_FINANCE_PROPERTY_ASK,
        YAHOO_FINANCE_PROPERTY_BID,
        YAHOO_FINANCE_PROPERTY_ASK_REALTIME,
        YAHOO_FINANCE_PROPERTY_BID_REALTIME,
        YAHOO_FINANCE_PROPERTY_PREVIOUS_CLOSE,
        YAHOO_FINANCE_PROPERTY_OPEN,
        YAHOO_FINANCE_PROPERTY_DIVIDEND_YIELD,
        YAHOO_FINANCE_PROPERTY_DIVIDEND_PER_SHARE,
        YAHOO_FINANCE_PROPERTY_DIVIDEND_PAY_DATE,
        YAHOO_FINANCE_PROPERTY_DIVIDEND_EX_DATE,
        YAHOO_FINANCE_PROPERTY_CHANGE,
        YAHOO_FINANCE_PROPERTY_CHANGE_AND_PERCENT_CHANGE,
        YAHOO_FINANCE_PROPERTY_CHANGE_REALTIME,
        YAHOO_FINANCE_PROPERTY_CHANGE_PERCENTAGE_REALTIME,
        YAHOO_FINANCE_PROPERTY_CHANGE_IN_PERCENT,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_DATE,
        YAHOO_FINANCE_PROPERTY_TRADE_DATE,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_TIME,
        YAHOO_FINANCE_PROPERTY_AFTER_HOURS_CHANGE_REALTIME,
        YAHOO_FINANCE_PROPERTY_DAY_LOW,
        YAHOO_FINANCE_PROPERTY_DAY_HIGH,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_REALTIME_WITH_TIME,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_WITH_TIME,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_PRICE_ONLY,
        YAHOO_FINANCE_PROPERTY_ONE_YEAR_TARGET_PRICE,
        YAHOO_FINANCE_PROPERTY_CHANGE_FROM_200_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_200_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_CHANGE_FROM_50_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_50_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_50_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_200_DAY_MOVING_AVERAGE,
        YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE,
        YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_REALTIME,
        YAHOO_FINANCE_PROPERTY_PRICE_PAID,
        YAHOO_FINANCE_PROPERTY_DAY_RANGE,
        YAHOO_FINANCE_PROPERTY_DAY_RANGE_REALTIME,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT,
        YAHOO_FINANCE_PROPERTY_ANNUALIZED_GAIN,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_REALTIME,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_REALTIME,
        YAHOO_FINANCE_PROPERTY_YEAR_HIGH,
        YAHOO_FINANCE_PROPERTY_YEAR_LOW,
        YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_LOW,
        YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_HIGH,
        YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_LOW,
        YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_HIGH,
        YAHOO_FINANCE_PROPERTY_YEAR_RANGE,
        YAHOO_FINANCE_PROPERTY_MORE_INFO,
        YAHOO_FINANCE_PROPERTY_MARKET_CAPITALIZATION,
        YAHOO_FINANCE_PROPERTY_MARKET_CAP_REALTIME,
        YAHOO_FINANCE_PROPERTY_FLOAT_SHARES,
        YAHOO_FINANCE_PROPERTY_NAME,
        YAHOO_FINANCE_PROPERTY_NOTES,
        YAHOO_FINANCE_PROPERTY_SYMBOL,
        YAHOO_FINANCE_PROPERTY_SHARES_OWNED,
        YAHOO_FINANCE_PROPERTY_STOCK_EXCHANGE,
        YAHOO_FINANCE_PROPERTY_SHARES_OUTSTANDING,
        YAHOO_FINANCE_PROPERTY_VOLUME,
        YAHOO_FINANCE_PROPERTY_ASK_SIZE,
        YAHOO_FINANCE_PROPERTY_BID_SIZE,
        YAHOO_FINANCE_PROPERTY_LAST_TRADE_SIZE,
        YAHOO_FINANCE_PROPERTY_AVERAGE_DAILY_VOLUME,
        YAHOO_FINANCE_PROPERTY_EARNINGS_PER_SHARE,
        YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_CURRENT_YEAR,
        YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_YEAR,
        YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_QUARTER,
        YAHOO_FINANCE_PROPERTY_BOOK_VALUE,
        YAHOO_FINANCE_PROPERTY_EBITDA,
        YAHOO_FINANCE_PROPERTY_PRICE_PER_SALES,
        YAHOO_FINANCE_PROPERTY_PRICE_PER_BOOK,
        YAHOO_FINANCE_PROPERTY_PE_RATIO,
        YAHOO_FINANCE_PROPERTY_PE_RATIO_REALTIME,
        YAHOO_FINANCE_PROPERTY_PEG_RATIO,
        YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_CURRENT_YEAR,
        YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_NEXT_YEAR,
        YAHOO_FINANCE_PROPERTY_SHORT_RATIO,
        YAHOO_FINANCE_PROPERTY_TICKER_TREND,
        YAHOO_FINANCE_PROPERTY_TRADE_LINKS,
        YAHOO_FINANCE_PROPERTY_ORDER_BOOK_REALTIME,
        YAHOO_FINANCE_PROPERTY_HIGH_LIMIT,
        YAHOO_FINANCE_PROPERTY_LOW_LIMIT,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE,
        YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_REALTIME,
        YAHOO_FINANCE_PROPERTY_REVENUE,
        YAHOO_FINANCE_PROPERTY_COMMISSION
    };

    /*
     * @brief Queries stock parameters for specified stock
     * @see parameterReceived
     *
     * @param rTickers list of unique stock ticker, NOTE: Yahoo might limit the maximum number
     * @param rParameters stock parameters
     * @param queryInterval query interval, NOTE: too frequent interval might cause Yahoo
     *        to block this IP address.
     */
    virtual void query(const QStringList &rTickers,
                       const QList<YahooFinance::StockParameter> &rParameters,
                       quint32 queryInterval);

Q_SIGNALS:

    /*
     * @brief This signal is emitted when query completed
     *
     * @param rTicker list of unique stock ticker
     * @param rData map containing properties as key and corresponding values
     */
    void parameterReceived(const QString &rTicker,
                           const QMap<YahooFinance::StockParameter, QString> &rData);

private:

    /*
     * @brief Converts list of tickers to Yahoo query format. For example
     *        list containing "MSFT" and "AAPL" will be formatted to a string
     *        containing "MSFT+AAPL"
     *
     * @param rTickers list of unique stock tickers
     * @return Yahoo Finance query format string
     */
    QString convertTickers(const QStringList &rTickers);

    /*
     * @brief Converts stock parameters to Yahoo Finance query format.
     *
     * @param rParameters requested parameters
     * @return String containing converted parameters
     */
    QString convertParameters(const QList<YahooFinance::StockParameter> &rParameters);

    /*
     * @brief Initialized parameter to Yahoo Finance query format mappings
     *
     * @return mappings
     */
    static QMap<StockParameter, QString> initMappings();

private:

    /*
     * @brief Holds parameter to Yahoo Finance query strings mappings
     */
    static QMap<StockParameter, QString> msParameterMappings;

    /*
     * @brief Holds pointers to network requests, pointers are owned
     */
    QList<YahooFinanceNetworkRequest *> mNetworkRequests;


};

#endif // YAHOOFINANCE_H

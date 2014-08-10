/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#ifndef YAHOOFINANCE_H
#define YAHOOFINANCE_H

#include <QVariant>
#include <QMap>
#include "yahoofinance_global.h"

/*
 * Provides access to financial data provided by Yahoo Finance
 */
class YAHOOFINANCESHARED_EXPORT YahooFinance
{
public:
    YahooFinance();

    enum StockParameter
    {
        YAHOO_FINANCE_PARAMETER_DIVIDEND_YIELD = 1,            // Double, current yield
        YAHOO_FINANCE_PARAMETER_DIVIDEND_PER_SHARE = 2,        // Double, dividend per share
        YAHOO_FINANCE_PARAMETER_DIVIDEND_PAY_DATE = 4,         // QDateTime, dividend pay date
        YAHOO_FINANCE_PARAMETER_EX_DIVIDEND_DATE = 8,          // QDateTime, ex-dividend date
        YAHOO_FINANCE_PARAMETER_CHANGE_PERCENT_REALTIME = 16,  // Double, change percent (realtime)
        YAHOO_FINANCE_PARAMETER_YEAR_RANGE = 32,               // QString, 52 week range
        YAHOO_FINANCE_PARAMETER_NAME = 64,                     // QString, company name
        YAHOO_FINANCE_PARAMETER_PE_REALTIME = 128              // Double, P/E ratio (realtime)
    };
    Q_DECLARE_FLAGS(StockParameters, StockParameter)

    /*
     * @brief Queries stock parameters for specified stock
     * @see parameterReceived
     *
     * @param rTickers list of unique stock ticker
     * @param parameters stock parameter flags
     */
    virtual void query(const QStringList &rTickers, YahooFinance::StockParameters parameters);

Q_SIGNALS:

    /*
     * @brief This signal is emitted when query completed
     *
     * @param rTicker list of unique stock ticker
     * @param parameter stock parameter which was received
     * @param rValue value associated with the parameter. In case of an error invalid QVariant is returned
     */
    void parameterReceived(const QString &rTicker, StockParameter parameter, const QVariant &rValue);

private:

    /*
     * @brief Converts list of tickers to Yahoo query format. For example list containing "MSFT" and "AAPL"
     *        will be formatted to a string containing "MSFT+AAPL"
     *
     * @param rTickers list of unique stock tickers
     * @return Yahoo Finance query format string
     */
    QString convertTickers(const QStringList &rTickers);

    /*
     * @brief Converts stock parameter flags to Yahoo Finance query format.
     *
     * @param parameters requested parameters
     * @return String containing converted parameters
     */
    QString convertParameters(YahooFinance::StockParameters parameters);

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
};

Q_DECLARE_OPERATORS_FOR_FLAGS(YahooFinance::StockParameters)

#endif // YAHOOFINANCE_H

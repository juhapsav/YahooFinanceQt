/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#ifndef YAHOOFINANCEDEFS_H
#define YAHOOFINANCEDEFS_H

namespace DwellDone
{
namespace YahooFinance
{

const QString YAHOO_FINANCE_QUERY_FORMAT = "http://download.finance.yahoo.com/d/quotes.csv?s=%1&f=%2";

// Pricing
const QString YAHOO_FINANCE_PROPERTY_ASK_KEY = "a";
const QString YAHOO_FINANCE_PROPERTY_BID_KEY = "b";
const QString YAHOO_FINANCE_PROPERTY_ASK_REALTIME_KEY = "b2";
const QString YAHOO_FINANCE_PROPERTY_BID_REALTIME_KEY = "b3";
const QString YAHOO_FINANCE_PROPERTY_PREVIOUS_CLOSE_KEY = "p";
const QString YAHOO_FINANCE_PROPERTY_OPEN_KEY = "o";

// Dividends
const QString YAHOO_FINANCE_PROPERTY_DIVIDEND_YIELD_KEY = "y";
const QString YAHOO_FINANCE_PROPERTY_DIVIDEND_PER_SHARE_KEY = "d";
const QString YAHOO_FINANCE_PROPERTY_DIVIDEND_PAY_DATE_KEY = "r1";
const QString YAHOO_FINANCE_PROPERTY_DIVIDEND_EX_DATE_KEY = "q";

// Date
const QString YAHOO_FINANCE_PROPERTY_CHANGE_KEY = "c1";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_AND_PERCENT_CHANGE_KEY = "c";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_REALTIME_KEY = "c6";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_PERCENTAGE_REALTIME_KEY = "k2";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_IN_PERCENT_KEY = "p2";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_DATE_KEY = "d1";
const QString YAHOO_FINANCE_PROPERTY_TRADE_DATE_KEY = "d2";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_TIME_KEY = "t1";

// Averages
const QString YAHOO_FINANCE_PROPERTY_AFTER_HOURS_CHANGE_REALTIME_KEY = "c8";
const QString YAHOO_FINANCE_PROPERTY_COMMISSION_KEY = "c3";
const QString YAHOO_FINANCE_PROPERTY_DAY_LOW_KEY = "g";
const QString YAHOO_FINANCE_PROPERTY_DAY_HIGH_KEY = "h";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_REALTIME_WITH_TIME_KEY = "k1";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_WITH_TIME_KEY = "l";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_PRICE_ONLY_KEY = "l1";
const QString YAHOO_FINANCE_PROPERTY_ONE_YEAR_TARGET_PRICE_KEY = "t8";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_FROM_200_DAY_MOVING_AVERAGE_KEY = "m5";
const QString YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_200_DAY_MOVING_AVERAGE_KEY = "m6";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_FROM_50_DAY_MOVING_AVERAGE_KEY = "m7";
const QString YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_50_DAY_MOVING_AVERAGE_KEY = "m8";
const QString YAHOO_FINANCE_PROPERTY_50_DAY_MOVING_AVERAGE_KEY = "m3";
const QString YAHOO_FINANCE_PROPERTY_200_DAY_MOVING_AVERAGE_KEY = "m4";

// Misc
const QString YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_KEY = "w1";
const QString YAHOO_FINANCE_PROPERTY_DAY_VALUE_CHANGE_REALTIME_KEY = "w4";
const QString YAHOO_FINANCE_PROPERTY_PRICE_PAID_KEY = "p1";
const QString YAHOO_FINANCE_PROPERTY_DAY_RANGE_KEY = "m";
const QString YAHOO_FINANCE_PROPERTY_DAY_RANGE_REALTIME_KEY = "m2";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_KEY = "g1";
const QString YAHOO_FINANCE_PROPERTY_ANNUALIZED_GAIN_KEY = "g3";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_KEY = "g4";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_PERCENT_REALTIME_KEY = "g5";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_GAIN_REALTIME_KEY = "g6";

// 52 week pricing
const QString YAHOO_FINANCE_PROPERTY_YEAR_HIGH_KEY = "k";
const QString YAHOO_FINANCE_PROPERTY_YEAR_LOW_KEY = "j";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_LOW_KEY = "j5";
const QString YAHOO_FINANCE_PROPERTY_CHANGE_FROM_YEAR_HIGH_KEY = "k4";
const QString YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_LOW_KEY = "j6";
const QString YAHOO_FINANCE_PROPERTY_PERCENT_CHANGE_FROM_YEAR_HIGH_KEY = "k5";
const QString YAHOO_FINANCE_PROPERTY_YEAR_RANGE_KEY = "w";

// Symbol info
const QString YAHOO_FINANCE_PROPERTY_MORE_INFO_KEY = "v";
const QString YAHOO_FINANCE_PROPERTY_MARKET_CAPITALIZATION_KEY = "j1";
const QString YAHOO_FINANCE_PROPERTY_MARKET_CAP_REALTIME_KEY = "j3";
const QString YAHOO_FINANCE_PROPERTY_FLOAT_SHARES_KEY = "f6";
const QString YAHOO_FINANCE_PROPERTY_NAME_KEY = "n";
const QString YAHOO_FINANCE_PROPERTY_NOTES_KEY = "n4";
const QString YAHOO_FINANCE_PROPERTY_SYMBOL_KEY = "s";
const QString YAHOO_FINANCE_PROPERTY_SHARES_OWNED_KEY = "s1";
const QString YAHOO_FINANCE_PROPERTY_STOCK_EXCHANGE_KEY = "x";
const QString YAHOO_FINANCE_PROPERTY_SHARES_OUTSTANDING_KEY = "j2";

// Volume
const QString YAHOO_FINANCE_PROPERTY_VOLUME_KEY = "v";
const QString YAHOO_FINANCE_PROPERTY_ASK_SIZE_KEY = "a5";
const QString YAHOO_FINANCE_PROPERTY_BID_SIZE_KEY = "b6";
const QString YAHOO_FINANCE_PROPERTY_LAST_TRADE_SIZE_KEY = "k3";
const QString YAHOO_FINANCE_PROPERTY_AVERAGE_DAILY_VOLUME_KEY = "a2";

// Ratios
const QString YAHOO_FINANCE_PROPERTY_EARNINGS_PER_SHARE_KEY = "e";
const QString YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_CURRENT_YEAR_KEY = "e7";
const QString YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_YEAR_KEY = "e8";
const QString YAHOO_FINANCE_PROPERTY_EPS_ESTIMATE_NEXT_QUARTER_KEY = "e9";
const QString YAHOO_FINANCE_PROPERTY_BOOK_VALUE_KEY = "b4";
const QString YAHOO_FINANCE_PROPERTY_EBITDA_KEY = "j4";
const QString YAHOO_FINANCE_PROPERTY_PRICE_PER_SALES_KEY = "p5";
const QString YAHOO_FINANCE_PROPERTY_PRICE_PER_BOOK_KEY = "p6";
const QString YAHOO_FINANCE_PROPERTY_PE_RATIO_KEY = "r";
const QString YAHOO_FINANCE_PROPERTY_PE_RATIO_REALTIME_KEY = "r2";
const QString YAHOO_FINANCE_PROPERTY_PEG_RATIO_KEY = "r5";
const QString YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_CURRENT_YEAR_KEY = "r6";
const QString YAHOO_FINANCE_PROPERTY_PRICE_PER_EPS_ESTIMATE_NEXT_YEAR_KEY = "r7";
const QString YAHOO_FINANCE_PROPERTY_SHORT_RATIO_KEY = "s7";

// Misc
const QString YAHOO_FINANCE_PROPERTY_TICKER_TREND_KEY = "t7";
const QString YAHOO_FINANCE_PROPERTY_TRADE_LINKS_KEY = "t6";
const QString YAHOO_FINANCE_PROPERTY_ORDER_BOOK_REALTIME_KEY = "i5";
const QString YAHOO_FINANCE_PROPERTY_HIGH_LIMIT_KEY = "l2";
const QString YAHOO_FINANCE_PROPERTY_LOW_LIMIT_KEY = "l3";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_KEY = "v1";
const QString YAHOO_FINANCE_PROPERTY_HOLDINGS_VALUE_REALTIME_KEY = "v7";
const QString YAHOO_FINANCE_PROPERTY_REVENUE_KEY = "s6";

} // namespace YahooFinance
} // namespace DwellDone

#endif // YAHOOFINANCEDEFS_H

#ifndef YAHOOFINANCENETWORKREQUEST_H
#define YAHOOFINANCENETWORKREQUEST_H

#include <QObject>
#include <QTimer>
#include "yahoofinance.h"

class YahooFinanceNetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit YahooFinanceNetworkRequest(
            const QString &rUrl,
            const QList<YahooFinance::StockParameter> &rParameters,
            quint32 intervalSec,
            QObject *parent = 0);

    /*
     * @brief Starts sending network request in configured interval
     */
    virtual void start();

private Q_SLOTS:

    /*
     * @brief Sends HTTP request
     */
    void sendRequest();

Q_SIGNALS:

    /*
     * @brief Signals query results
     *
     * @param rTicker unique stock ticker
     * @param rData map containing received data
     */
    void parametersReceived(const QString &rTicker,
                            const QMap<YahooFinance::StockParameter, QString> &rData);

private:

    /*
     * @brief Holds URL where the network request is sent
     */
    QString mUrl;

    /*
     * @brief Holds ordered list of parameters, order is used when parsing reply
     */
    QList<YahooFinance::StockParameter> mParameters;

    /*
     * @brief Timer used to send the request in intervals
     */
    QTimer mTimer;
};

#endif // YAHOOFINANCENETWORKREQUEST_H

#ifndef YAHOOFINANCENETWORKREQUEST_H
#define YAHOOFINANCENETWORKREQUEST_H

#include <QObject>
#include <QTimer>
#include <QScopedPointer>
#include <QNetworkReply>
#include <QUrl>
#include "yahoofinance.h"

class QNetworkReply;
class QNetworkAccessManager;

class YahooFinanceNetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit YahooFinanceNetworkRequest(
            const QString &rQueryIdentifier,
            const QString &rUrl,
            const QStringList &rTickers,
            const QList<YahooFinance::StockParameter> &rParameters,
            QNetworkAccessManager &rNetworkManager,
            QObject *parent = 0);

    /*
     * @brief Starts sending network request in configured interval
     *
     * @param interval for network requests
     * @return success/failure
     */
    virtual bool start(quint32 interval);

    /*
     * @brief Stops sending network requests
     */
    virtual void stop();

Q_SIGNALS:

    /*
     * @brief Signals query results
     *
     * @param rQueryIdentifier unique query identifier
     * @param rTicker unique stock ticker
     * @param rData map containing received data
     */
    void parametersReceived(const QString &rQueryIdentifier,
                            const QString &rTicker,
                            const QMap<YahooFinance::StockParameter, QString> &rData);

    /*
     * @brief Query has failed and will not retry automatically
     *
     * @param rQueryIdentifier unique query identifier
     */
    void errorOccured(const QString &rQueryIdentifier);

private Q_SLOTS:

    /*
     * @brief Sends HTTP request
     *
     * @return success/failure
     */
    bool sendRequest();

    /*
     * @brief Handles network reply
     *
     * @param pReply reply handle (ownership taken)
     */
    void handleReply(QNetworkReply *pReply);

private:

    /*
     * @brief Handles error situation internally and emits errorOccured
     */
    void handleError();

private:

    /*
     * @brief Holds unique query identifier
     */
    QString mQueryIdentifier;

    /*
     * @brief Holds URL where the network request is sent
     */
    QUrl mUrl;

    /*
     * @brief Holds ordered list of tickers, order is used when parsing reply
     */
    QStringList mTickers;

    /*
     * @brief Holds ordered list of parameters, order is used when parsing reply
     */
    QList<YahooFinance::StockParameter> mParameters;

    /*
     * @brief Holds reference to network access manager
     */
    QNetworkAccessManager &mrNetworkManager;

    /*
     * @brief Timer used to send the request in intervals
     */
    QTimer mTimer;

    /*
     * @brief Network reply handle
     */
    QScopedPointer<QNetworkReply> mpNetworkReply;
};

#endif // YAHOOFINANCENETWORKREQUEST_H

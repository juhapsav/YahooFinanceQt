#-------------------------------------------------
#
# Project created by QtCreator 2014-08-10T16:29:36
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = YahooFinance
TEMPLATE = lib

DEFINES += YAHOOFINANCE_LIBRARY

SOURCES += yahoofinance.cpp \
    yahoofinancenetworkrequest.cpp

HEADERS += yahoofinance.h\
        yahoofinance_global.h \
    YahooFinanceDefs.h \
    yahoofinancenetworkrequest.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

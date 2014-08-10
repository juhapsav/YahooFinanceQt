/************************************************************
 * Copyright 2014 Juha-Pekka Savolainen. info@dwelldone.fi  *
 * For licensing information refer to attached LICENSE file *
 ************************************************************/

#ifndef YAHOOFINANCE_GLOBAL_H
#define YAHOOFINANCE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(YAHOOFINANCE_LIBRARY)
#  define YAHOOFINANCESHARED_EXPORT Q_DECL_EXPORT
#else
#  define YAHOOFINANCESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // YAHOOFINANCE_GLOBAL_H

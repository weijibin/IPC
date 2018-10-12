#ifndef HHIPC_GLOBAL_H
#define HHIPC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HHIPC_LIBRARY)
#  define HHIPCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HHIPCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HHIPC_GLOBAL_H

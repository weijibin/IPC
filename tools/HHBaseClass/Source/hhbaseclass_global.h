#ifndef HHBASECLASS_GLOBAL_H
#define HHBASECLASS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HHBASECLASS_LIBRARY)
#  define HHBASECLASSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HHBASECLASSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HHBASECLASS_GLOBAL_H
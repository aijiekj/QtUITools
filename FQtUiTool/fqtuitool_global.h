#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FQTUITOOL_LIB)
#  define FQTUITOOL_EXPORT Q_DECL_EXPORT
# else
#  define FQTUITOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define FQTUITOOL_EXPORT
#endif

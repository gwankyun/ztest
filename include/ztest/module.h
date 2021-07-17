#pragma once

#ifndef USE_MODULE
#  if defined(__cpp_modules)
#    define USE_MODULE 1
#  else
#    define USE_MODULE 0
#  endif
#endif

#ifndef EXPORT_BEGIN
#  if USE_MODULE
#    define EXPORT_BEGIN export {
#  else
#    define EXPORT_BEGIN
#  endif
#endif

#ifndef EXPORT_END
#  if USE_MODULE
#    define EXPORT_END }
#  else
#    define EXPORT_END
#  endif
#endif

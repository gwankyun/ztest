#pragma once

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

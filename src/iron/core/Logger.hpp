#pragma once

// Logging macros...for now everything is logged to console -- TBR (tons)

#ifndef IRON_LOGGER
  #define IRON_LOGGER
  #define LOG_BASE(file, line, context, level, msg) (std::cout << level << " " << file << ":" << line << " " << context << " - " << msg << std::endl)

  #define LOG_TRACE(msg) (LOG_BASE(__FILE__, __LINE__, __func__, "TRACE", msg))
  #define LOG_DEBUG(msg) (LOG_BASE(__FILE__, __LINE__, __func__, "DEBUG", msg))
  #define LOG_INFO (msg) (LOG_BASE(__FILE__, __LINE__, __func__, "INFO ", msg))
  #define LOG_ERROR(msg) (LOG_BASE(__FILE__, __LINE__, __func__, "ERROR", msg))
  #define LOG_FATAL(msg) (LOG_BASE(__FILE__, __LINE__, __func__, "FATAL", msg))
#endif

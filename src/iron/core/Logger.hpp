#pragma once

// Logging macros...for now everything is logged to console -- TBR (tons)

#ifndef IRON_LOGGER
  #define IRON_LOGGER
  #define LOG_BASE(file, line, level, msg) (std::cout << level << " " << file << ":" << line << " - " << msg << std::endl)

  #define LOG_TRACE(msg) (LOG_BASE(__FILE__, __LINE__, "TRACE", msg))
  #define LOG_DEBUG(msg) (LOG_BASE(__FILE__, __LINE__, "DEBUG", msg))
  #define LOG_INFO (msg) (LOG_BASE(__FILE__, __LINE__, "INFO ", msg))
  #define LOG_ERROR(msg) (LOG_BASE(__FILE__, __LINE__, "ERROR", msg))
  #define LOG_FATAL(msg) (LOG_BASE(__FILE__, __LINE__, "FATAL", msg))
#endif

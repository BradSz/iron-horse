#pragma once

#define BOOST_LOG_DYN_LINK
#include <boost/log/trivial.hpp>

// Logging macros...for now everything is logged to console -- TBR (tons)

#ifndef IRON_LOGGER
  #define IRON_LOGGER
  #define LOG_TRACE(msg) BOOST_LOG_TRIVIAL(trace)   << msg;
  #define LOG_DEBUG(msg) BOOST_LOG_TRIVIAL(debug)   << msg;
  #define LOG_INFO(msg)  BOOST_LOG_TRIVIAL(info)    << msg;
  #define LOG_WARN(msg)  BOOST_LOG_TRIVIAL(warning) << msg;
  #define LOG_ERROR(msg) BOOST_LOG_TRIVIAL(error)   << msg;
  #define LOG_FATAL(msg) BOOST_LOG_TRIVIAL(fatal)   << msg;
#endif

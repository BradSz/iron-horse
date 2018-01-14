#pragma once

// Boost
#include <boost/asio/io_service.hpp>
//#include <boost/core/nocopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

// STD and STL
#include <algorithm>
#include <chrono>
#include <climits>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <stdint.h>
#include <sstream>
#include <unordered_set>
#include <vector>

// Threading
#include <condition_variable>
#include <mutex>
#include <thread>

// Convenience Typedefs (after external files are included)
#include <iron/core/Typedefs.hpp>

// Iron Utilities
#include <iron/threading/Boxed.hpp>
#include <iron/core/Logger.hpp>


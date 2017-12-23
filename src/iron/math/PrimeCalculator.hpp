#pragma once

#include <boost/container/flat_set.hpp>

#include <iron/core.h>

#include <iron/math/PrimeStash.hpp>

namespace iron {

struct PrimeCalculator {

    PrimeCalculator()
      : mStash(),
        mIOService(),
        mThreadPool(),
        mWork(new boost::asio::io_service::work(mIOService)) {

      unsigned numThreads = std::max((unsigned)4, (unsigned)2*boost::thread::hardware_concurrency());
      for (unsigned idx = 0; idx < numThreads; ++idx) {
          mThreadPool.create_thread(boost::bind(&boost::asio::io_service::run, &mIOService));
      }

      LOG_INFO("Created thread pool with (" << numThreads << ") threads");
    }

    ~PrimeCalculator() {
      mWork.reset();
      mThreadPool.join_all();
    }

    // Stubbed capability, not yet multithreaded
    bool isPrime(uint64_t inVal) {
      if (inVal < 2) return false;
      uint64_t stopAt = std::sqrt(inVal);
      for (uint64_t trial = 2; trial <= stopAt; ++trial) {
        if (inVal % trial == 0) return false;
      }
      return true;
    }

  private:

    PrimeStash mStash;
    boost::asio::io_service mIOService;
    boost::thread_group     mThreadPool;
    std::unique_ptr<boost::asio::io_service::work> mWork;
};

} /* iron */

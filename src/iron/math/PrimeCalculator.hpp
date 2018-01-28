#pragma once

#include <boost/container/flat_set.hpp>

#include <iron/core.h>

#include <iron/math/PrimeStash.hpp>

namespace iron {
namespace math {

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

      LOG_DEBUG("Created thread pool with (" << numThreads << ") threads");

      mPrimes.insert(2);
    }

    ~PrimeCalculator() {
      mWork.reset();
      mThreadPool.join_all();
    }

    // Stubbed capability, not yet multithreaded
    bool isPrime(uint64_t inVal) {
      LOG_TRACE(__func__ << "(" << inVal << ")");

      // Check previously computed
      if (mPrimes.count(inVal))      { return true;  }
      if (inVal < *mPrimes.rbegin()) { return false; }

      const uint64_t sqrtVal  = std::sqrt(inVal);

      while (*mPrimes.rbegin() < sqrtVal) {
        uint64_t trial = (*mPrimes.rbegin()) + 1;
        while (!isPrime(trial)) {
          ++trial;
        }
        mPrimes.insert(trial);
      }
      for (uint64_t p : mPrimes) {
        if (inVal % p == 0) return false;
      }

      return true;
    }

  protected:
    bool hasCached(uint64_t inVal) {
      uint64_t lastPrime    = mPrimes.empty() ? 2 : (*mPrimes.rbegin());
      uint64_t primeSquared = lastPrime * lastPrime;

      return (primeSquared >= inVal);
    }

  private:

    PrimeStash mStash;
    boost::asio::io_service mIOService;
    boost::thread_group     mThreadPool;
    std::unique_ptr<boost::asio::io_service::work> mWork;
    boost::container::flat_set<uint64_t> mPrimes;
};

} /* math */
} /* iron */

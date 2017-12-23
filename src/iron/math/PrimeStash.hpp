#pragma once

#include <iron/core.h>

#include <boost/container/flat_set.hpp>

namespace iron {

struct PrimeStash {

    PrimeStash() : Primes() {
      Primes.insert(2);
    }

  // For now, strictly positive. Could be genericized and pulled out of PrimeStash
  template <typename IntegerContainer_t>
  static bool isDivisibleByAnyOf(uint64_t inEvaluated, IntegerContainer_t inValues) {
    for (auto trial : inValues) {
      if (inEvaluated % trial == 0){
        return true;
      }
    }
    return false;
  }

  uint64_t lastStashed()                  const { return *Primes.crbegin(); }
  bool     canEvaluate(uint64_t inNumber) const { return lastStashed()*lastStashed() >= inNumber; }

  boost::container::flat_set<uint64_t> Primes;
};

} /* iron */

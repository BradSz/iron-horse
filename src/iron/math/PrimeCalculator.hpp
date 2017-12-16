#pragma once

#include <iron/core.h>

namespace iron {

struct PrimeCalculator {

  // For now, strictly positive, dealing with concretes
  template <typename IntegerContainer_t >
  static bool isDivisibleByAnyOf(uint64_t inEvaluated, IntegerContainer_t inValues) {
    for (auto trial : inValues) {
      if (inEvaluated % trial == 0){
        return true;
      }
    }
    return false;
  }
};

} /* iron */

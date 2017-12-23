#include <iron/core.h>
#include <iron/math/PrimeCalculator.hpp>

int main(int argc, char** argv) {

  // Determine if requested value is prime
  iron::PrimeCalculator pc;
  for (uint64_t trial = 0; trial < 10; ++trial) {
    if(pc.isPrime(trial)) {
      std::cout << trial << " is prime" << std::endl;
    } else {
      std::cout << trial << " is not prime" << std::endl;
    }
  }

  return 0;
}

#define BOOST_TEST_MODULE prime_calculator
#include <boost/test/included/unit_test.hpp>

#include <iron/math/PrimeCalculator.hpp>

BOOST_AUTO_TEST_SUITE(prime_calculator)

struct Fixture : public ::iron::math::PrimeCalculator {
  
};

BOOST_FIXTURE_TEST_CASE(PrimesUnderTenTest, Fixture)
{
  BOOST_CHECK_EQUAL(false, isPrime(0));
  BOOST_CHECK_EQUAL(false, isPrime(1));
  BOOST_CHECK_EQUAL(true,  isPrime(2));
  BOOST_CHECK_EQUAL(true,  isPrime(3));
  BOOST_CHECK_EQUAL(false, isPrime(4));
  BOOST_CHECK_EQUAL(true,  isPrime(5));
  BOOST_CHECK_EQUAL(false, isPrime(6));
  BOOST_CHECK_EQUAL(true,  isPrime(7));
  BOOST_CHECK_EQUAL(false, isPrime(8));
  BOOST_CHECK_EQUAL(false, isPrime(9));
}

BOOST_FIXTURE_TEST_CASE(LargePrimesTest, Fixture)
{
  BOOST_CHECK_EQUAL(true,  isPrime(999983));
  BOOST_CHECK_EQUAL(false, isPrime(999999));
}


BOOST_FIXTURE_TEST_CASE(CachedResults100Test, Fixture)
{
  BOOST_CHECK_EQUAL(false, hasCached(100));
  BOOST_CHECK_EQUAL(false, hasCached(121));
  BOOST_CHECK_EQUAL(false, hasCached(122));

  BOOST_CHECK_EQUAL(false, isPrime  (100));

  BOOST_CHECK_EQUAL(true,  hasCached(100));
  BOOST_CHECK_EQUAL(true,  hasCached(121));
  BOOST_CHECK_EQUAL(false, hasCached(122));
}

BOOST_AUTO_TEST_SUITE_END()


#define BOOST_TEST_MODULE boxed
#include <boost/test/included/unit_test.hpp>

#include <iron/math/PrimeCalculator.hpp>

BOOST_AUTO_TEST_SUITE(boxed)

BOOST_AUTO_TEST_CASE(IsDivisibleByAnyOfTest)
{
  std::vector<uint64_t> previous;
  previous.push_back(2);
  previous.push_back(3);
  previous.push_back(5);
  previous.push_back(7);
  previous.push_back(11);

  // Success checks
  BOOST_CHECK( iron::PrimeCalculator::isDivisibleByAnyOf(2,  previous));
  BOOST_CHECK( iron::PrimeCalculator::isDivisibleByAnyOf(3,  previous));
  BOOST_CHECK( iron::PrimeCalculator::isDivisibleByAnyOf(4,  previous));

  // Failure checks
  BOOST_CHECK(!iron::PrimeCalculator::isDivisibleByAnyOf(1,  previous));
  BOOST_CHECK(!iron::PrimeCalculator::isDivisibleByAnyOf(13, previous));
}


BOOST_AUTO_TEST_SUITE_END()


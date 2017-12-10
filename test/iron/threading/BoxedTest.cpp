#define BOOST_TEST_MODULE boxed
#include <boost/test/included/unit_test.hpp>

#include <iron/threading/Boxed.hpp>

BOOST_AUTO_TEST_SUITE(boxed)

struct Fixture : public iron::box<std::string> {
    Fixture()
      : iron::box<std::string>("BaseText"),
        BaseText("BaseText")
    {
      // Sanity check that test setup is right/spelled correctly
      BOOST_REQUIRE_EQUAL(BaseText, *mData);
    }

    std::string BaseText;
};

BOOST_FIXTURE_TEST_CASE(CloneTest, Fixture)
{
  std::shared_ptr<std::string> cloneData = clone();

  // Verify cloned data is the same
  BOOST_CHECK_EQUAL(BaseText, *cloneData);

  // Verify modifications to cloned data do not affect original
  cloneData->clear();
  BOOST_CHECK_NE(BaseText, *cloneData);
}

BOOST_AUTO_TEST_SUITE_END()

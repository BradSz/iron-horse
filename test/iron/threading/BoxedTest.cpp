#define BOOST_TEST_MODULE boxed
#include <boost/test/included/unit_test.hpp>

#include <iron/threading/Boxed.hpp>

BOOST_AUTO_TEST_SUITE(boxed)

struct Fixture : public iron::Box<std::string> {
    Fixture()
      : iron::Box<std::string>(std::shared_ptr<std::string>(new std::string("BaseText"))),
        BaseText   ("BaseText"),
        MutatedText("MutatedText")
    {
      // Sanity check that test setup is right/spelled correctly
      BOOST_REQUIRE_EQUAL(BaseText,        *mData            );
      BOOST_REQUIRE_NE   (BaseText,        MutatedText       );
      BOOST_REQUIRE_NE   (BaseText.size(), MutatedText.size());
    }

    std::string BaseText;
    std::string MutatedText;
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

BOOST_FIXTURE_TEST_CASE(ViewTest, Fixture)
{
  // Verify multiple views can be used
  view_type view1 = view();
  view_type view2 = view();

  // Verify the views point to the same data
  BOOST_CHECK_EQUAL(BaseText, *view1);
  BOOST_CHECK_EQUAL(BaseText, *view2);
}

BOOST_FIXTURE_TEST_CASE(MutTest, Fixture)
{
  mut_type mut1 = mut();

  // Verify mutable data is the same
  BOOST_CHECK_EQUAL(BaseText, *mut1);

  // Verify modification is possible
  *mut1 = MutatedText;
  BOOST_CHECK_EQUAL(MutatedText, *mut1);

  // Verify mutation flows back to base class
  mut1.release();
  mut1 = mut();
  BOOST_CHECK_EQUAL(MutatedText       , *mData      );
  BOOST_CHECK_EQUAL(MutatedText       , *mut1       );
  BOOST_CHECK_EQUAL(MutatedText.size(), mut1->size());
}

BOOST_AUTO_TEST_SUITE_END()

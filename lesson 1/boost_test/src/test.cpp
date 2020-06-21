#define BOOST_TEST_MODULE test_mstring
#include <boost/test/included/unit_test.hpp>
#include "basic_mstring.h"

BOOST_AUTO_TEST_SUITE(test_mstring)

BOOST_AUTO_TEST_CASE(test1)
{
    Z::basic_mstring s;
    BOOST_CHECK(s.size_() == 0);
}

BOOST_AUTO_TEST_CASE(test2)
{
    Z::basic_mstring s = "hello world!\r\n";
    BOOST_REQUIRE_EQUAL('h',s[0]);
}

BOOST_AUTO_TEST_SUITE_END()

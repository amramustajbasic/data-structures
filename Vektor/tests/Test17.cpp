#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Get first element of vector") {
  SUBCASE("Get first element of non-empty vector") {
    MojVektor v{1, 2, 3};
    CHECK(v.front() == 1);
  }

  SUBCASE("Get first element of vector with one element") {
    MojVektor v{1};
    CHECK(v.front() == 1);
  }

  SUBCASE("Get first element of empty vector") {
    MojVektor v;
    CHECK_THROWS_AS(v.front(), std::out_of_range);
  }
}


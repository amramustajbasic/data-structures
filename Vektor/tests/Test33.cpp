#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::find() returns correct iterator for non-empty vector") {
  MojVektor v{1, 2, 3, 4, 5};

  SUBCASE("Element is in vector") {
    auto iter = v.find(3);
    REQUIRE(*iter == 3);
  }

  SUBCASE("Element is not in vector") {
    auto iter = v.find(6);
    REQUIRE(iter == v.end());
  }
}

TEST_CASE("MojVektor::find() returns end iterator for empty vector") {
  MojVektor v;

  auto iter = v.find(1);
  REQUIRE(iter == v.end());
}

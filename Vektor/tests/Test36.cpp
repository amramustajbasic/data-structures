#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::rbegin() returns correct iterator") {
  MojVektor v{1, 2, 3, 4, 5};

  auto iter = v.rbegin();
  REQUIRE(*iter == 5);
}

TEST_CASE("MojVektor::rend() returns correct iterator") {
  MojVektor v{1, 2, 3, 4, 5};

  auto iter = v.rend();
  REQUIRE(iter == v.begin() - 1);
}

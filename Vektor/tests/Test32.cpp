#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::end() returns correct iterator") {
  MojVektor v{1, 2, 3, 4, 5};

  auto iter = v.end();
  REQUIRE(iter == (v.data() + 5));
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::Iterator default constructor") {
  SUBCASE(
      "The default constructor should create an iterator pointing to null") {
    MojVektor::Iterator it;
    CHECK(it.operator->() == nullptr);
  }
}

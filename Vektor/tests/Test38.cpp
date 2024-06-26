#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::Iterator::operator[]") {
  MojVektor v;
  v.push_back(1).push_back(2).push_back(3);
  MojVektor::Iterator it = v.begin();

  CHECK(*(it[0]) == 1);
  CHECK(*(it[1]) == 2);
  CHECK(*(it[2]) == 3);
}

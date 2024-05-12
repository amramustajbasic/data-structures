#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::Iterator move constructor") {
  int arr[] = {1, 2, 3};
  MojVektor::Iterator it(arr);

  SUBCASE(
      "The move constructor should move the value from the original "
      "iterator to the new iterator") {
    MojVektor::Iterator it_moved(std::move(it));
    CHECK(it.operator->() == nullptr);
    CHECK(it_moved.operator*() == 1);
  }
}

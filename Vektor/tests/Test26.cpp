#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor::Iterator copy assignment operator") {
  int arr[] = {1, 2, 3};
  MojVektor::Iterator it(arr);

  SUBCASE(
      "The copy assignment operator should copy the value from the "
      "original iterator to the new iterator") {
    int arr2[] = {4, 5, 6};
    MojVektor::Iterator it2(arr2);
    it2 = it;
    CHECK(*it2 == 1);
  }
}

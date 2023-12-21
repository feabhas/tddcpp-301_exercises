// test_gdo.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "doctest.h"

#include "GarageDoorOpener.h"
#include <exception>

TEST_CASE("Door initially closed")
{
  GarageDoorOpener garageDoorOpener{};
  CHECK(garageDoorOpener.door_is_closed() == false);
}

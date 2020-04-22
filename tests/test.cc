// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <island/engine.h>
#include <island/location.h>

#include <catch2/catch.hpp>

TEST_CASE("Location addition overload test", "[location]") {
  island::Location first_location(10, 20);
  island::Location second_location(5, 10);
  island::Location location = first_location + second_location;

  REQUIRE(location.GetRow() == 15);
  REQUIRE(location.GetCol() == 30);
}

TEST_CASE("Location mod overload test", "[location]") {
  island::Location first_location(10, 20);
  island::Location second_location(4, 10);
  island::Location location = first_location % second_location;

  REQUIRE(location.GetRow() == 2);
  REQUIRE(location.GetCol() == 0);
}
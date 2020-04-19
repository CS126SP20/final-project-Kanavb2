// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_PLAYER_H_
#define ISLAND_PLAYER_H_

#include <utility>

#include "location.h"

namespace island {

/** Represents a player in the game. */
struct Player {

  Player(std::string name, Location location)
        : name_(std::move(name)),
          location_(location){}

  std::string name_;
  Location location_;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

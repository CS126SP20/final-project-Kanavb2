// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_PLAYER_H_
#define ISLAND_PLAYER_H_

#include <utility>
#include <string>

#include "location.h"
#include "statistics.h"

namespace island {
/** Represents a player in the game. */
struct Player {
  Player(std::string name, Location location, Statistics statistics)
        : name_(std::move(name)),
          location_(location),
          statistics_(statistics){}

  std::string name_;
  Location location_;
  Statistics statistics_;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

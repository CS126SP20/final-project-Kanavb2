// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_PLAYER_H_
#define ISLAND_PLAYER_H_

#include <utility>

#include "character.h"

namespace island {

/** Represents a player in the game. */
struct Player : Character {
  /** Constructor for the player, calls super class constructor. */
  Player(const std::string& name, const Location& location,
      const Statistics& statistics, std::vector<Item>& inventory, size_t money)
        : Character(name, location, statistics),
          inventory_(inventory),
          money_(money) {}

  /** The player's inventory with all of their items. */
  std::vector<Item> inventory_;

  /** The amount of money the player has. */
  size_t money_;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

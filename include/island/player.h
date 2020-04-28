// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_PLAYER_H_
#define ISLAND_PLAYER_H_

#include <utility>

#include "location.h"
#include "statistics.h"
#include "item.h"

namespace island {
/** Represents a player in the game. */
struct Player {
  /** Constructor for the player. */
  Player(const std::string& name, const Location& location,
      const Statistics& statistics, std::vector<Item>& inventory,
      size_t money)
        : name_(name),
          location_(location),
          statistics_(statistics),
          inventory_(inventory),
          money_(money) {}

  /** The name of the player. */
  const std::string& name_;

  /** The current location of the player. */
  Location location_;

  /** The statistics for the player, used in combat. */
  const Statistics& statistics_;

  /** The player's inventory with all of their items. */
  std::vector<Item>& inventory_;

  /** The amount of money the player has. */
  size_t money_;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

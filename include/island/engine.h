// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_ENGINE_H_
#define ISLAND_ENGINE_H_

#include "direction.h"
#include "player.h"
#include "map.h"

#include <cstddef>
#include <string>

namespace island {

/**
 * This is the game engine, the primary way to interact with the game.
 */
class Engine {
 public:

  /**
   * Creates a new game for the island.
   *
   * @param width the width of the island map
   * @param height the height of the island map
   * @param player_name the name of the player
   * @param player_loc the location of the player
   * @param player_stats the statistics of the player
   * @param player_inventory the list of items the player has
   * @param player_money the amount of money the player has
   */
  Engine(size_t width, size_t height,
         const std::string& player_name,
         const Location& player_loc,
         const Statistics& player_stats,
         const std::vector<Item>& player_inventory, size_t player_money);

  /** Executes a time step, moves the player character. */
  void ExecuteTimeStep();

  /** Gets the location delta value from a direction. */
  Location FromDirection(const Direction& direction) const;

  /** Saves the game. */
  void Save();

  /** Determines whether the direction the player wants to move in is valid. */
  bool IsValidDirection(const Direction& direction) const;

  /** Changes the direction of the player character with each step. */
  inline void SetDirection(const Direction& direction) {
    direction_ = direction;
  }

  /**
   * Accessor function for the player in the game.
   *
   * @return the player in the game engine
   */
  inline Player GetPlayer() const {
    return player_;
  }

 private:
  /** The width of the island map. */
  size_t width_;

  /** The height of the island map. */
  size_t height_;

  /** The direction the player character moves in. */
  Direction direction_;

  /** The object representing the player character. */
  Player player_;

  /** Map of the game. */
  Map map_;
};

}  // namespace island

#endif // ISLAND_ENGINE_H_

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
         std::vector<Item> player_inventory, size_t player_money);

  /** Executes a time step, moves the player character. */
  void ExecuteTimeStep();

  /** Gets the location delta value from a direction. */
  Location FromDirection(const Direction& direction) const;

  /** Saves the game. */
  void Save();

  /** Determines whether the direction the player wants to move in is valid. */
  bool IsValidDirection(const Direction& direction) const;

  /**
   * Gets the location the player is facing
   *
   * @param direction the last direction the player moved in
   * @return the location the player is looking at
   */
  Location GetFacingLocation(const Direction& direction) const;

  /**
   * Gets the tile type at the specified location on the map
   *
   * @param location the location at which the tile type is required
   * @return the tile type as a Tile enum object
   */
  Tile GetTileType(const Location& location) const;

  /** Changes the direction of the player character with each step. */
  inline void SetDirection(const Direction& direction) {
    direction_ = direction;
  }

  /**
   * Adds the specified item to the player's inventory.
   *
   * @param item the item to be added
   */
  void AddInventoryItem(const Item& item);

  /**
   * Removes the specified item from the player's inventory
   *
   * @param item the item to be removed
   */
  void RemoveInventoryItem(const Item& item);

  /**
   * Accessor function for an item in the player's inventory.
   *
   * @param index the index of the item in the inventory
   * @return the item to be retrieved
   */
  inline Item GetInventoryItem(size_t index) const {
    return player_.inventory_[index];
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

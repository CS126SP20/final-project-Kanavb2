// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_ENGINE_H_
#define ISLAND_ENGINE_H_

#include "direction.h"
#include "player.h"
#include "map.h"
#include "npc.h"

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
   * @param items all the items in the game
   * @param player_name the name of the player
   * @param player_loc the location of the player
   * @param player_stats the statistics of the player
   * @param player_inventory the list of items the player has
   * @param player_money the amount of money the player has
   */
  Engine(size_t width, size_t height,
         std::vector<Item> items,
         const std::string& player_name,
         const Location& player_loc,
         const Statistics& player_stats,
         std::vector<Item> player_inventory, size_t player_money);

  /** Initializes the Npcs throughout the map. */
  void InitializeNpcs();

  /** Executes a time step, moves the player character. */
  void ExecuteTimeStep();

  /** Gets the location delta value from a direction. */
  Location GetLocationDelta(const Direction& direction) const;

  /** Saves the game. */
  void Save();

  /** Determines whether the direction the player wants to move in is valid. */
  bool IsValidDirection(const Direction& direction) const;

  /**
   * Gets the npc that is at the location specified on the map.
   *
   * @param location the location at which the npc is
   */
  Npc GetNpcAtLocation(const Location& location) const;

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
   * Removes the specified item from the player's inventory.
   *
   * @param name the name of the item to be removed
   */
  void RemoveInventoryItem(const std::string& name);

  /**
   * Adds the specified item to the list of items in the game.
   *
   * @param item the item to be added
   */
  void AddItem(const Item& item);

  /**
   * Removes the specified item from the list of items in the game.
   *
   * @param item_name the name of the item to be removed
   */
  void RemoveItem(const std::string& item_name);

  /**
   * Sets the tile at a particular location to a new Tile value
   * Wrapper function for Map's SetTile
   *
   * @param location the location where the value of the tile is to be changed
   * @param tile the new value of the tile
   */
  void SetTile(const Location& location, const Tile& tile);

  /**
   * Accessor function for any item in the game.
   *
   * @param item_name the name of the item to be retrieved
   * @return the item to be retrieved
   */
  Item GetItem(const std::string& item_name) const;

  /**
   * Adds a certain amount of money to the player's pocket
   *
   * @param money_to_add the amount of money to be added
   */
  void AddMoney(size_t money_to_add) {
    player_.money_ += money_to_add;
  }

  /**
   * Remove a certain amount of money from the player's pocket
   *
   * @param money_to_remove the amount money to be removed
   */
  void RemoveMoney(size_t money_to_remove) {
    player_.money_ -= money_to_remove;
  }

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

  /**
   * Accessor function for the list of npcs in the game.
   *
   * @return the npcs in the game
   */
  inline std::vector<Npc> GetNpcs() {
    return npcs_;
  }

  /**
   * Accessor function for the key value.
   *
   * @return whether the key has been found or not
   */
  inline bool GetKey() const {
    return is_key_found_;
  }

  /**
   * Sets the value of the variable that stores whether the key has been found.
   *
   * @param is_key_found true if the key is found, false otherwise
   */
  inline void SetKey(bool is_key_found) {
    is_key_found_ = is_key_found;
  }

 private:
  /** The width of the island map. */
  size_t width_;

  /** The height of the island map. */
  size_t height_;

  /** Determines whether the key to the house has been found. */
  bool is_key_found_;

  /** The direction the player character moves in. */
  Direction direction_;

  /** The object representing the player character. */
  Player player_;

  /** Map of the game. */
  Map map_;

  /** The list of all items in the game. */
  std::vector<Item> items_;

  /**
   * The list of all the non player characters in the game.
   */
  std::vector<Npc> npcs_;

  /**
   * The list of all the non player characters in the game, mapped from the
   * name of the npc to the location where they are on the map.
   */
  std::unordered_map<std::string, Location> npc_locations_;
};

}  // namespace island

#endif // ISLAND_ENGINE_H_

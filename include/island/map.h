// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_MAP_H_
#define ISLAND_MAP_H_

#include <island/location.h>

#include <unordered_map>
#include <vector>

namespace island {

/** The map size in terms of tile size. */
const size_t kMapSize = 50;

/** Represents each tile in the map. */
enum Tile {
  kGrass,
  kRoad,
  kSand,
  kCold,
  kFarm,
  kWater,
  kPuddle,
  kTree,
  kNotice,
  kMailBox,
  kBarrier,
  kHouse,
  kDoor,
  kInvalid,
  kExtreme,
  kKey,
  kNpc
};

/** Class which represents the map for the entire game. */
class Map {
public:
  /** Constructor which initializes the map with tile values. */
  Map();

  /** Initializes the map for the tiles, mapping a char to a tile object. */
  void InitializeMapTiles();

  /**
   * Determines whether the player can move onto a particular tile on the map.
   *
   * @param x the x coordinate of the tile the user wants to move to
   * @param y the y coordinate of the tile the user wants to move to
   * @return whether or not the tile is traversable
   */
  bool IsAccessibleTile(const Location& location) const;

  /**
   * Gets the tile type at the specified location on the map
   *
   * @param location the location at which the tile type is required
   * @return the tile type as a Tile enum object
   */
  Tile GetTile(const Location& location) const;

  /**
   * Sets the tile at a particular location to a new Tile value
   *
   * @param location the location where the value of the tile is to be changed
   * @param tile the new value of the tile
   */
  void SetTile(const Location& location, const Tile& tile);

 private:
  /**
   * Stores the tile values to be read from the file, with the character
   * representing a tile in the file as the key, and the tile itself as the
   * value.
   */
  std::unordered_map<char, Tile> letter_tiles_;

  /** Stores all the tile values for the map. */
  std::vector<std::vector<Tile>> raw_map_;
};

}  // namespace island

#endif  // ISLAND_MAP_H_

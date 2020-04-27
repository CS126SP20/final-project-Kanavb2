// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_MAP_H_
#define ISLAND_MAP_H_

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
  kOpenDoor,
  kClosedDoor,
  kInvalid,
  kExtreme,
  kNpc
};

/** Class which represents the map for the entire game. */
class Map {
public:
  /** Constructor which initializes the map with tile values. */
  Map();

  /**
   * Determines whether the player can move onto a particular tile on the map.
   *
   * @param x the x coordinate of the tile the user wants to move to
   * @param y the y coordinate of the tile the user wants to move to
   * @return whether or not the tile is traversable
   */
  bool IsTraversableTile(int row, int col) const;

private:
  /** Stores all the tile values for the map. */
  std::vector<std::vector<Tile>> raw_map_;
};

}  // namespace island

#endif  // ISLAND_MAP_H_

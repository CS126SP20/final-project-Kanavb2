// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_MAP_H_
#define ISLAND_MAP_H_

namespace island {

/** Class which represents the map for the entire game. */
class Map {
public:
  /** Represents each tile in the map. */
  enum Tile {
    kDirt,
    kGrass,
    kPath,
    kWater,
    kWall
  };

  /** Constructor which initializes the map with tile values. */
  Map();

  /**
   * Determines whether the player can move onto a particular tile on the map.
   *
   * @param x the x coordinate of the tile the user wants to move to
   * @param y the y coordinate of the tile the user wants to move to
   * @return whether or not the tile is traversable
   */
  bool IsTraversableTile(int x, int y);

private:
  /** Stores all the tile values for the map. */
  std::array<std::array<Tile, 64>, 64> raw_map_;
};

}  // namespace island

#endif  // ISLAND_MAP_H_

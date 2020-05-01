// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/map.h>

#include <fstream>

namespace island {

Map::Map() {
  std::ifstream map_file("assets/map_tileset.txt");
  char tile;
  InitializeMapTiles();
  for (size_t row = 0; row < kMapSize; row++) {
    raw_map_.emplace_back();
    for (size_t col = 0; col < kMapSize; col++) {
      map_file >> tile;
      raw_map_[row].push_back(letter_tiles_.at(tile));
    }
  }
}

void Map::InitializeMapTiles() {
  letter_tiles_.insert(std::pair<char, Tile>('i', kInvalid));
  letter_tiles_.insert(std::pair<char, Tile>('g', kGrass));
  letter_tiles_.insert(std::pair<char, Tile>('r', kRoad));
  letter_tiles_.insert(std::pair<char, Tile>('s', kSand));
  letter_tiles_.insert(std::pair<char, Tile>('c', kCold));
  letter_tiles_.insert(std::pair<char, Tile>('f', kFarm));
  letter_tiles_.insert(std::pair<char, Tile>('w', kWater));
  letter_tiles_.insert(std::pair<char, Tile>('p', kPuddle));
  letter_tiles_.insert(std::pair<char, Tile>('t', kTree));
  letter_tiles_.insert(std::pair<char, Tile>('n', kNotice));
  letter_tiles_.insert(std::pair<char, Tile>('m', kMailBox));
  letter_tiles_.insert(std::pair<char, Tile>('b', kBarrier));
  letter_tiles_.insert(std::pair<char, Tile>('h', kHouse));
  letter_tiles_.insert(std::pair<char, Tile>('o', kOpenDoor));
  letter_tiles_.insert(std::pair<char, Tile>('k', kClosedDoor));
  letter_tiles_.insert(std::pair<char, Tile>('e', kExtreme));
  letter_tiles_.insert(std::pair<char, Tile>('q', kNpc));
}

bool Map::IsAccessibleTile(const Location& location) const {
  return raw_map_[location.GetRow()][location.GetCol()] == kGrass
  || raw_map_[location.GetRow()][location.GetCol()] == kRoad
  || raw_map_[location.GetRow()][location.GetCol()] == kSand
  || raw_map_[location.GetRow()][location.GetCol()] == kPuddle;
}

Tile Map::GetTile(const Location& location) const {
  return raw_map_[location.GetRow()][location.GetCol()];
}

}  // namespace island
// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/map.h>

#include <fstream>

namespace island {
  Map::Map() {
    std::ifstream map_file("assets/map_tileset");
    char tile;
    for (size_t row = 0; row < kMapSize; row++) {
      raw_map_.emplace_back();
      for (size_t col = 0; col < kMapSize; col++) {
        map_file >> tile;
        switch (tile) {
          case 'i': {
            raw_map_[row].push_back(kInvalid);
            break;
          }
          case 'g': {
            raw_map_[row].push_back(kGrass);
            break;
          }
          case 'r': {
            raw_map_[row].push_back(kRoad);
            break;
          }
          case 's': {
            raw_map_[row].push_back(kSand);
            break;
          }
          case 'c': {
            raw_map_[row].push_back(kCold);
            break;
          }
          case 'f': {
            raw_map_[row].push_back(kFarm);
            break;
          }
          case 'w': {
            raw_map_[row].push_back(kWater);
            break;
          }
          case 'p': {
            raw_map_[row].push_back(kPuddle);
            break;
          }
          case 't': {
            raw_map_[row].push_back(kTree);
            break;
          }
          case 'n': {
            raw_map_[row].push_back(kNotice);
            break;
          }
          case 'm': {
            raw_map_[row].push_back(kMailBox);
            break;
          }
          case 'b': {
            raw_map_[row].push_back(kBarrier);
            break;
          }
          case 'h': {
            raw_map_[row].push_back(kHouse);
            break;
          }
          case 'o': {
            raw_map_[row].push_back(kOpenDoor);
            break;
          }
          case 'k': {
            raw_map_[row].push_back(kClosedDoor);
            break;
          }
          case 'e': {
            raw_map_[row].push_back(kExtreme);
            break;
          }
          default: raw_map_[row].push_back(kNpc);
        }
      }
    }
  }

  bool Map::IsTraversableTile(const Location& location) const {
    return raw_map_[location.GetRow()][location.GetCol()] == kGrass
    || raw_map_[location.GetRow()][location.GetCol()] == kRoad
    || raw_map_[location.GetRow()][location.GetCol()] == kSand
    || raw_map_[location.GetRow()][location.GetCol()] == kPuddle;
  }

  Tile Map::GetTile(const Location& location) const {
    return raw_map_[location.GetRow()][location.GetCol()];
  }
}  // namespace island
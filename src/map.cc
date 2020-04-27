// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <fstream>

#include <island/map.h>

namespace island {
  Map::Map() {
    std::ifstream map_file("assets/map_tileset");
    char tile;
    for (size_t col = 0; col < kMapSize; col++) {
      for (size_t row = 0; row < kMapSize; row++) {
        map_file >> tile;
        switch (tile) {
          case 'i': {
            raw_map_[row][col] = kInvalid;
            break;
          }
          case 'g': {
            raw_map_[row][col] = kGrass;
            break;
          }
          case 'r': {
            raw_map_[row][col] = kRoad;
            break;
          }
          case 's': {
            raw_map_[row][col] = kSand;
            break;
          }
          case 'c': {
            raw_map_[row][col] = kCold;
            break;
          }
          case 'f': {
            raw_map_[row][col] = kFarm;
            break;
          }
          case 'w': {
            raw_map_[row][col] = kWater;
            break;
          }
          case 'p': {
            raw_map_[row][col] = kPuddle;
            break;
          }
          case 't': {
            raw_map_[row][col] = kTree;
            break;
          }
          case 'n': {
            raw_map_[row][col] = kNotice;
            break;
          }
          case 'm': {
            raw_map_[row][col] = kMailBox;
            break;
          }
          case 'b': {
            raw_map_[row][col] = kBarrier;
            break;
          }
          case 'h': {
            raw_map_[row][col] = kHouse;
            break;
          }
          case 'o': {
            raw_map_[row][col] = kOpenDoor;
            break;
          }
          case 'e': {
            raw_map_[row][col] = kClosedDoor;
            break;
          }
          default: raw_map_[row][col] = kNpc;
        }
      }
    }
  }

  bool Map::IsTraversableTile(int row, int col) const {
    return raw_map_[row][col] == kGrass
    || raw_map_[row][col] == kRoad
    || raw_map_[row][col] == kSand
    || raw_map_[row][col] == kPuddle;
  }
}  // namespace island
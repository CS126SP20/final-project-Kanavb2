// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/map.h>

namespace island {
  Map::Map() {
    Tile test[] =
        {kInvalid, kInvalid, kInvalid, kInvalid, kInvalid, kInvalid, kInvalid,
            kGrass, kHouse, kHouse, kHouse, kHouse, kHouse, kHouse, kInvalid,
            kInvalid, kFence, kGrass, kGrass, kGrass, kGrass, kGrass, kGrass,
            kGrass, kGrass, kGrass, kPath, kInvalid, kInvalid, kInvalid,
            kInvalid, kInvalid, kInvalid, kInvalid, kInvalid, kInvalid,
            kInvalid, kInvalid, kInvalid, kInvalid, kInvalid, kInvalid,
            kInvalid, kInvalid, kInvalid, kInvalid, kInvalid, kInvalid,
            kInvalid, kInvalid};

    for (size_t row = 0; row < kMapSize; row++) {
      for (size_t col = 0; col < kMapSize; col++) {
        if (col == 0) {
          raw_map_[row][col] = test[row];
        } else {
          raw_map_[row][col] = Tile::kGrass;
        }
      }
    }
  }

  bool Map::IsTraversableTile(int row, int col) const {
    return raw_map_[row][col] == kGrass || raw_map_[row][col] == kPath;
  }
}  // namespace island
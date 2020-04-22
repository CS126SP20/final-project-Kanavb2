// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/map.h>

namespace island {
  Map::Map() {
    for (size_t row = 0; row < kMapSize; row++) {
      for (size_t col = 0; col < kMapSize; col++) {
        raw_map_[row][col] = kWater;
      }
    }
  }

  bool Map::IsTraversableTile(int x, int y) {
    return false;
  }
}  // namespace island
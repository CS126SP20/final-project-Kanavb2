// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/engine.h>
#include <island/location.h>

namespace island {

// Converts a direction into a delta location.
Location FromDirection(const Direction& direction) {
  switch (direction) {
    case Direction::kUp:
      return {-1, 0};
    case Direction::kDown:
      return {+1, 0};
    case Direction::kLeft:
      return {0, -1};
    case Direction::kRight:
      return {0, +1};
  }
}

Engine::Engine(size_t width, size_t height) {
  width_ = width;
  height_ = height;
  direction_ = Direction::kRight;
}

void Engine::Step() {
  Location direction_loc = FromDirection(direction_);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);
}

void Engine::Save() {

}

}  // namespace island

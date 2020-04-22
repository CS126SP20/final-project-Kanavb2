// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/engine.h>
#include <island/location.h>

#include <utility>

namespace island {

// Converts a direction into a delta location.
Location FromDirection(const Direction& direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, +1};
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {+1, 0};
  }
}

Engine::Engine(size_t width, size_t height)
    :   player_ {Player("meow", {7, 7})}{
  width_ = width;
  height_ = height;
  direction_ = Direction::kRight;
}

void Engine::Step() {
  Location direction_loc = FromDirection(direction_);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);
  player_.location_ = new_loc;
}

void Engine::Save() {

}

}  // namespace island

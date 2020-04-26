// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/engine.h>
#include <island/location.h>

#include <utility>

namespace island {

Engine::Engine(size_t width, size_t height)
    :   player_ {Player("meow", {7, 7},
        {10,10,10,10})},
        width_{width},
        height_{height},
        direction_{Direction::kRight} {}

Location Engine::FromDirection(const Direction& direction) const {
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

void Engine::ExecuteTimeStep() {
  Location direction_loc = FromDirection(direction_);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);
  player_.location_ = new_loc;
}

void Engine::Save() {

}

bool Engine::IsValidDirection(const Direction &direction) const {
  Location direction_loc = FromDirection(direction);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);

  return map_.IsTraversableTile(new_loc.GetRow(), new_loc.GetCol());
}

}  // namespace island

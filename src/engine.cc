// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/engine.h>
#include <island/location.h>

namespace island {

Engine::Engine(size_t width, size_t height,
    const std::string& player_name,
    const Location& player_loc,
    const Statistics& player_stats,
    const std::vector<Item>& player_inventory, size_t player_money)
    :   player_ {Player(player_name, player_loc, player_stats, player_inventory,
                    player_money)},
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
  player_.location_.SetRow(new_loc.GetRow());
  player_.location_.SetCol(new_loc.GetCol());
}

void Engine::Save() {

}

bool Engine::IsValidDirection(const Direction &direction) const {
  Location direction_loc = FromDirection(direction);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);

  return map_.IsTraversableTile(new_loc);
}

Location Engine::GetFacingLocation(const Direction& direction) const {
  Location direction_loc = FromDirection(direction);
  return (player_.location_ + direction_loc) % Location(height_, width_);
}

Tile Engine::GetTileType(const Location& location) const {
  return map_.GetTile(location);
}

void Engine::AddInventoryItem(const Item& item) {
  player_.inventory_.push_back(item);
}

void Engine::RemoveInventoryItem(const Item &item) {
  for (size_t index = 0; index < player_.inventory_.size(); index++) {
    if (player_.inventory_[index].name_ == item.name_) {
      player_.inventory_.erase(player_.inventory_.begin() + index);
      break;
    }
  }
}

}  // namespace island

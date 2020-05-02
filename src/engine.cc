// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/engine.h>
#include <island/location.h>

#include <utility>

namespace island {

Engine::Engine(size_t width, size_t height, std::vector<Item> items,
    const std::string& player_name, const Location& player_loc,
    const Statistics& player_stats, std::vector<Item> player_inventory,
    size_t player_money)
    :   player_ {Player(player_name, player_loc, player_stats,
                      player_inventory, player_money)},
        width_{width},
        height_{height},
        items_{std::move(items)},
        direction_{Direction::kRight} {
  InitializeNpcs();
}

void Engine::InitializeNpcs() {
  npcs_.push_back(Npc("Rosalyn", {15, 2}, Statistics(10,10,10,10), false));
  npcs_.push_back(Npc("John", {20, 1}, Statistics(10,10,10,10), false));
  npcs_.push_back(Npc("Rod", {16, 48}, Statistics(10,10,10,10), false));
  npcs_.push_back(Npc("Klutz", {28, 20}, Statistics(10,10,10,10), false));
  npcs_.push_back(Npc("Azura", {38, 10}, Statistics(10,10,10,10), false));

  npcs_.push_back(Npc("Sven", {25, 20}, Statistics(7,7,7,7), true));
  npcs_.push_back(Npc("Elf", {26, 20}, Statistics(11,11,11,11), true));
}

Location Engine::GetLocationDelta(const Direction& direction) const {
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
  Location direction_loc = GetLocationDelta(direction_);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);
  player_.location_.SetRow(new_loc.GetRow());
  player_.location_.SetCol(new_loc.GetCol());
}

void Engine::Save() {

}

bool Engine::IsValidDirection(const Direction &direction) const {
  Location direction_loc = GetLocationDelta(direction);
  Location new_loc =
      (player_.location_ + direction_loc) % Location(height_, width_);

  return map_.IsAccessibleTile(new_loc);
}


Npc Engine::GetNpcAtLocation(const Location &location) const {
  for (const auto& npc : npcs_) {
    if (npc.location_.GetRow() == location.GetRow() &&
        npc.location_.GetCol() == location.GetCol()) {
      return npc;
    }
  }
}

Location Engine::GetFacingLocation(const Direction& direction) const {
  Location direction_loc = GetLocationDelta(direction);
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

void Engine::AddItem(const Item& item) {
  items_.push_back(item);
}

void Engine::RemoveItem(const std::string& item_name) {
  for (size_t index = 0; index < items_.size(); index++) {
    if (items_[index].name_ == item_name) {
      items_.erase(items_.begin() + index);
      return;
    }
  }
}

Item Engine::GetItem(const std::string& item_name) const {
  for (auto& item : items_) {
    if (item.name_ == item_name) {
      return item;
    }
  }
}

void Engine::SetTile(const Location& location, const Tile& tile) {
  map_.SetTile(location, tile);
}

}  // namespace island

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <nlohmann/json.hpp>

#include <island/engine.h>
#include <island/location.h>

#include <fstream>
#include <utility>

namespace island {

using nlohmann::json;

Engine::Engine(size_t width, size_t height, std::vector<Item> items,
    const std::string& player_name, const Location& player_loc,
    const Statistics& player_stats, std::vector<Item> player_inventory,
    size_t player_money)
    :   player_ {Player(player_name, player_loc, player_stats,
                      player_inventory, player_money)},
        width_{width},
        height_{height},
        items_{std::move(items)},
        direction_{Direction::kRight},
        is_key_found_{false} {
  InitializeNpcs();
}

void Engine::InitializeNpcs() {
  npcs_.push_back(Npc("Rosalyn", {15, 2}, Statistics(10,10,10,10), false, 0));
  npcs_.push_back(Npc("John", {20, 1}, Statistics(10,10,10,10), false, 0));
  npcs_.push_back(Npc("Rod", {16, 48}, Statistics(10,10,10,10), false, 0));
  npcs_.push_back(Npc("Klutz", {28, 20}, Statistics(10,10,10,10), false, 0));
  npcs_.push_back(Npc("Azura", {38, 10}, Statistics(10,10,10,10), false, 0));
  npcs_.push_back(Npc("Boi", {36, 36}, Statistics(10, 10, 10, 10), false, 0));
  npcs_.push_back(Npc("Sven", {25, 20}, Statistics(7,7,7,7), true, 500));
  npcs_.push_back(Npc("Elf", {26, 20}, Statistics(11,11,11,11), true, 1000));
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
  std::ofstream write_file("assets/saved_game.json");
  json game_engine;
  json json_items;
  json json_inventory_items;

  for (const auto& item : items_) {
    json_items["name"] = item.name_;
    json_items["description"] = item.description_;
    json_items["file_path"] = item.file_path_;
  }
  for (const auto& inventory_item : player_.inventory_) {
    json_inventory_items["name"] = inventory_item.name_;
    json_inventory_items["description"] = inventory_item.description_;
    json_inventory_items["file_path"] = inventory_item.file_path_;
  }

  game_engine["width"] = width_;
  game_engine["height"] = height_;
  game_engine["is_key_found"] = is_key_found_;
  game_engine["direction"] = direction_;
  game_engine["player"]["name"] = player_.name_;
  game_engine["player"]["location"]["row"] = player_.location_.GetRow();
  game_engine["player"]["location"]["col"] = player_.location_.GetCol();
  game_engine["player"]["statistics"]["hp"] = player_.statistics_.hit_points_;
  game_engine["player"]["statistics"]["atk"] = player_.statistics_.attack_;
  game_engine["player"]["statistics"]["def"] = player_.statistics_.defense_;
  game_engine["player"]["statistics"]["spe"] = player_.statistics_.speed_;
  game_engine["player"]["money"] = player_.money_;
  game_engine["items"] = json_items;
  game_engine["inventory_items"] = json_inventory_items;

  write_file << game_engine;
}

void Engine::Load(const std::string& file_path) {
  std::ifstream read_file(file_path);
  json game_engine;
  read_file >> game_engine;

  std::vector<Item> items;
  std::vector<Item> inventory_items;
  json json_items;
  json json_inventory_items;

  for (const auto& item : json_items) {
    items.emplace_back(item["name"], item["description"], item["file_path"]);
  }
  for (const auto& inventory_item : json_inventory_items) {
    inventory_items.emplace_back(inventory_item["name"],
        inventory_item["description"], inventory_item["file_path"]);
  }

  width_ = game_engine["width"];
  height_ = game_engine["height"];
  is_key_found_ = game_engine["is_key_found"];
  items_ = items;
  player_.name_ = game_engine["player"]["name"];
  player_.location_ = {game_engine["player"]["location"]["row"],
                       game_engine["player"]["location"]["col"]};
  player_.statistics_.hit_points_ = game_engine["player"]["statistics"]["hp"];
  player_.statistics_.attack_ = game_engine["player"]["statistics"]["atk"];
  player_.statistics_.defense_ = game_engine["player"]["statistics"]["def"];
  player_.statistics_.speed_ = game_engine["player"]["statistics"]["spe"];
  player_.inventory_ = inventory_items;
  player_.money_ = game_engine["player"]["money"];

  if (is_key_found_) {
    map_.SetTile(kKeyLocation, kTree);
  }
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

void Engine::RemoveInventoryItem(const std::string& name) {
  for (size_t index = 0; index < player_.inventory_.size(); index++) {
    if (player_.inventory_[index].name_ == name) {
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

Item Engine::GetItemFromIndex(size_t index) const {
  return items_[index];
}

void Engine::SetTile(const Location& location, const Tile& tile) {
  map_.SetTile(location, tile);
}

}  // namespace island

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_PLAYER_H_
#define ISLAND_PLAYER_H_

namespace island {

/** Represents a player in the game. */
struct Player {
  Player(const std::string& name) : name(name) {}
  std::string name;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_NPC_H_
#define ISLAND_NPC_H_

namespace island {
/** Represents a non player character in the game. */
struct Npc {
  Npc(std::string name, Location location, Statistics statistics)
        : name_(std::move(name)),
        location_(location),
        statistics_(statistics){}

  std::string name_;
  Location location_;
  Statistics statistics_;
};

}  // namespace island

#endif // ISLAND_NPC_H_

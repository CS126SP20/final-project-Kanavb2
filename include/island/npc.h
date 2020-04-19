// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_NPC_H_
#define ISLAND_NPC_H_

namespace island {

/** Represents a non player character in the game. */
struct Npc {
  Npc(const std::string& name) : name(name) {}
  std::string name;
};

}  // namespace island

#endif // ISLAND_NPC_H_

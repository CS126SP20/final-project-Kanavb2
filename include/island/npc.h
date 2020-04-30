// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_NPC_H_
#define ISLAND_NPC_H_

#include "character.h"

namespace island {
/** Represents a non player character in the game. */
struct Npc : Character {
  /** The constructor for the npc, calls super class constructor. */
  Npc(const std::string& name, const Location& location,
      const Statistics& statistics)
      : Character(name, location, statistics) {}
};

}  // namespace island

#endif // ISLAND_NPC_H_

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_NPC_H_
#define ISLAND_NPC_H_

#include "character.h"

namespace island {

/** Represents a non player character in the game. */
struct Npc : Character {
  /** The constructor for the npc, calls super class constructor. */
  Npc(const std::string& name, const Location& location,
      const Statistics& statistics, bool is_combatable, size_t money)
      : Character(name, location, statistics), is_combatable_(is_combatable),
        money_(money) {}

  /** Determines whether the player can battle the npc. */
  bool is_combatable_;

  /** The money the player gains when they defeat the npc in battle. */
  size_t money_;
};

}  // namespace island

#endif // ISLAND_NPC_H_

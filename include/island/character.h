// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_CHARACTER_H_
#define ISLAND_CHARACTER_H_

#include <utility>

#include "location.h"
#include "statistics.h"
#include "item.h"

namespace island {

/** Represents a character in the game. */
struct Character {
  /** The constructor for the character. */
  Character(const std::string& name, const Location& location,
            const Statistics& statistics)
        : name_(name),
          location_(location),
          statistics_(statistics) {}

  /** The name of the character. */
  const std::string& name_;

  /** The current location of the character. */
  Location location_;

  /** The statistics for the character, used in battle. */
  const Statistics& statistics_;
};

}  // namespace island

#endif // ISLAND_PLAYER_H_

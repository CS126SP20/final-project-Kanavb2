// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_STATISTICS_H_
#define ISLAND_STATISTICS_H_

namespace island {

/** Manages the statistics of a character in the game. */
struct Statistics {
  /** The constructor for the Statistics of a character. */
  Statistics(size_t hit_points, size_t attack, size_t defense, size_t speed)
  : hit_points_{hit_points},
    attack_{attack},
    defense_{defense},
    speed_{speed} {}

  /**
   * The hit points the character has.
   * Changes based on the damage dealt to the character.
   */
  size_t hit_points_;

  /**
   * The attack statistic for the character.
   * Used to determine how much damage is to be dealt in a battle.
   */
  size_t attack_;

  /**
   * The defense statistic for the character.
   * Used to determine how much damage the character takes in a battle.
   */
  size_t defense_;

  /**
   * The speed statistic for the character.
   * Used to determine which character moves first in a battle.
   */
  size_t speed_;
};

}  // namespace island

#endif // ISLAND_STATISTICS_H_

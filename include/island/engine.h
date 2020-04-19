// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_ENGINE_H_
#define ISLAND_ENGINE_H_

#include "direction.h"

namespace island {

/**
 * This is the game engine; the primary way to interact with the game.
 */
class Engine {
 public:
  /**
   * Creates a new game for the island.
   *
   * @param width the width of the island map
   * @param height the height of the island map
   */
  Engine(size_t width, size_t height);

  /** Executes a time step, moves the player character. */
  void Step();

  /** Saves the game. */
  void Save();

  /** Changes the direction of the player character with each step. */
  void SetDirection(const Direction& direction);

 private:
  /** The width of the island map. */
  const size_t width_;

  /** The height of the island map. */
  const size_t height_;

  /** The direction the player character moves in. */
  const Direction direction_;
};

}  // namespace island

#endif // ISLAND_ENGINE_H_

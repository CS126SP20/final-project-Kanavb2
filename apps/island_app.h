// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <island/engine.h>
#include <island/direction.h>
#include <island/location.h>
#include <island/map.h>

namespace islandapp {

/** Enum used to represents the game's current state. */
enum class GameState {
  kPlaying,
  kPaused,
  kMenu
};

/** The class that interacts with cinder to run the game. */
class IslandApp : public cinder::app::App {
public:
  /** The constructor for the game. */
  IslandApp();

  /** The setup function, called before the game is launched. */
  void setup() override;

  /** The update function, called roughly every frame to
   * update what happens in the game, and what the user sees.
   */
  void update() override;

  /**
   * The graphic related function, called whenever a change is to be made
   * to the graphics that the user sees.
   */
  void draw() override;

  /**
   * The key bind function, called to tell the game what to do
   * when a certain key is pressed on the keyboard.
   */
  void keyDown(cinder::app::KeyEvent) override;

private:
  /**
   * Draws the player on the map.
   */
  void DrawPlayer() const;

  /**
   * Draws the map in the background of the game.
   */
  void DrawMap() const;

  /**
   * Determines what the program should do when one of the
   * movement directed keys is pressed on the keyboard.
   *
   * @param direction the direction to move in
   */
  void HandleMovement(island::Direction direction);

  /**
   * Determines what the player character should look like
   * when they move in a particular direction.
   *
   * @return the TextureRef representing the image of the player character
   */
  cinder::gl::TextureRef GetPlayerDirectionImage() const;

private:
  /** The game engine responsible for running the game. */
  island::Engine engine_;

  /** Represents the current state of the game. */
  GameState state_;

  /** The time elapsed since the update function has been called. */
  std::chrono::time_point<std::chrono::system_clock> last_time_;

  /** The speed or delay of the game, i.e. a lesser value is faster. */
  const size_t speed_;

  /** The name of the player. */
  const std::string player_name_;

  /** Determines whether the game is paused or not. */
  bool paused_;

  /** Determines whether the user changed their direction
   * after the previous directional command.
   */
  bool is_changed_direction_;

  /** The number of directional commands
   * since the direction was last changed changed.
   */
  size_t last_changed_direction_;

  /** The previous direction that the user moved in. */
  island::Direction prev_direction_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

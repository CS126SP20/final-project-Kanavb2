// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <island/engine.h>
#include <island/direction.h>
#include <island/location.h>
#include <island/map.h>
#include <island/item.h>

#include <string>

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
  /** The number of movement sprites for the player. */
  const size_t kNumSprites = 4;

  /** The screen size in terms of tile size. */
  const size_t kScreenSize = 40;

  /** The tile size for the player terms of pixels. */
  const size_t kPlayerTileSize = 40;

  /** The tile size for the map terms of pixels. */
  const size_t kMapTileSize = 50;

  /** The speed of the player character. */
  const size_t kSpeed = 50;

  /** The divider for how much of the total screen the user should view. */
  const size_t kScreenDivider = 2;

  /** The multiplier for how many pixels the camera translates the view. */
  const float kTranslationMultiplier = 40.0;

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
   * Handles the movement of the camera with respect to the player.
   * Makes sure the camera cannot move out of the map area.
   */
  void HandleCameraInteractions();

  /**
   * Determines what the player character should look like
   * when they move in a particular direction.
   *
   * @return the TextureRef representing the image of the player character
   */
  cinder::gl::TextureRef GetPlayerDirectionImage() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves down.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetDownDirectionImage() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves up.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetUpDirectionImage() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves left.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetLeftDirectionImage() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves right.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetRightDirectionImage() const;

  /**
   * Determines what the program should do when one of the
   * movement directed keys is pressed on the keyboard.
   *
   * @param direction the direction to move in
   */
  void HandleMovement(island::Direction direction);

  void HandlePlayerInteractions() const;

  /** The game engine responsible for running the game. */
  island::Engine engine_;

  /** Represents the current state of the game. */
  GameState state_;

  /** The time elapsed since the update function has been called. */
  std::chrono::time_point<std::chrono::system_clock> last_time_;

  /** The speed or delay of the game, i.e. a lesser value is faster. */
  size_t speed_;

  /**
   * Determines whether the user changed their direction
   * after the previous directional command.
   */
  bool is_changed_direction_;

  /**
   * The number of directional commands
   * since the direction was last changed changed.
   */
  size_t last_changed_direction_;

  /** The previous direction that the user moved in. */
  island::Direction prev_direction_;

  /** The location object to offset the rendering by, illusion of a camera. */
  island::Location camera_;
};

}  // namespace islandapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

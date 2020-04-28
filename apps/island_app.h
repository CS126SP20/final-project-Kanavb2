// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_ISLANDAPP_H_
#define FINALPROJECT_APPS_ISLANDAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <island/engine.h>
#include <island/direction.h>
#include <island/location.h>
#include <island/map.h>
#include <island/item.h>

#include <string>
#include <fstream>

namespace islandapp {

/** Enum used to represents the game's current state. */
enum class GameState {
  kPlaying,
  kPaused,
  kDisplayingText,
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

  /** The font size of the text to be displayed to the user. */
  const size_t kFontSize = 30;

  /** The width of the text box to be displayed. */
  const size_t kTextBoxWidth = 800;

  /** The height of the text box to be displayed. */
  const size_t kTextBoxHeight = 150;

  /** The speed at which characters are displayed in the text box. */
  const size_t kCharSpeed = 1;

  /** Determines how far down the text box is placed, higher is further down. */
  const float kTextLocMultiplier = 2.0;

  /** The number of pixels the text is offset from the textbox. */
  const size_t kTextOffset = 10;

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
   * Draws the text box that displays the player's interaction text.
   */
  void DrawTextBox();

  /**
   * Called whenever the user is shown a text box.
   *
   * @tparam C The typename for the color of the text
   * @param text the text to be displayed
   * @param color the color of the text
   * @param size the size of the text
   * @param loc the location on the screen where the text is to be displayed
   */
  template <typename C>
  void PrintText(const std::string& text, const C& color,
                  const cinder::ivec2& size, const cinder::vec2& loc) const;

  /**
   * Translates the outputted image and text.
   *
   * @param is_up true if the translation is upward, false otherwise
   */
  void Translate(bool is_up) const;

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
  void HandleMovement(const island::Direction& direction);

  /**
   * Handles the player's interactions with the map, displays text on the
   * screen accordingly.
   */
  void HandlePlayerInteractions();

  /**
   * Determines the text to be displayed when the player interacts with the map
   * by retrieving the file associated with the tile.
   *
   * @param tile the tile with which the player interacts
   * @return the file path storing the text to be displayed
   */
  std::string GetDisplayFile(const island::Tile& tile) const;

  /**
   * Retrieves the text from a file.
   *
   * @param file_path the path to the file to be read from
   * @return the text stored in the file
   */
  std::string GetTextFromFile(const std::string& file_path) const;

  /** The game engine responsible for running the game. */
  island::Engine engine_;

  /** Represents the current state of the game. */
  GameState state_;

  /** The time elapsed since the update function has been called. */
  std::chrono::time_point<std::chrono::system_clock> last_time_;

  /** The speed or delay of the game, i.e. a lesser value is faster. */
  size_t speed_;

  /** Keeps track of the characters to be displayed in a text message. */
  size_t char_counter_;

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

  /** The text to be displayed when the player interacts with the map. */
  std::string display_text_;

  /** The location object to offset the rendering by, illusion of a camera. */
  island::Location camera_;
};

}  // namespace islandapp

#endif  // FINALPROJECT_APPS_ISLANDAPP_H_

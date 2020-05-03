// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_ISLANDAPP_H_
#define FINALPROJECT_APPS_ISLANDAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
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
  kInventory
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

  /** The number of pixels the text is offset from the textbox. */
  const size_t kTextOffset = 10;

  /** The maximum number of items the player can hold. */
  const size_t kMaxInventorySize = 5;

  /** Determines how far down the text box is placed, higher is further down. */
  const double kTextLocMultiplier = 2.0;

  /** The multiplier for how many pixels the camera translates the view. */
  const double kTranslationMultiplier = 40.0;

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
   * Initializes the audio objects that play through the game.
   */
  void InitializeAudio();

  /**
   * Initializes all the items that exist in the game.
   */
  void InitializeItems();

  /**
   * Initializes the file paths used to relay text on the screen.
   */
  void InitializeDisplayFilePaths();

  /**
   * Initializes the npc file paths used to relay the npcs' dialogue.
   */
   void InitializeNpcTextFilePaths();

  /**
   * Initializes the npc sprite file paths to display the npcs on the screen.
   */
  void InitializeNpcSpriteFilePaths();

  /**
   * Initializes the sprites to be drawn on the screen.
   */
  void InitializeActiveNpcSpriteFiles();

  /**
   * Adds the npc sprites to the map to be used to draw the sprites.
   *
   * @param name the name of the npc
   */
  void AddNpcSprites(const std::string& name);

  /**
   * Draws the map in the background of the game.
   */
  void DrawMap() const;

  /**
   * Draws the player on the map.
   */
  void DrawPlayer() const;

  /**
   * Draws the npcs throughout the map.
   * Non const since it accesses engine's list of npcs.
   */
  void DrawNpcs();

  /**
   * Draws the text box that displays the player's interaction text.
   * Non const since the typewriter effect used changes char_counter_.
   */
  void DrawTextBox();

  /**
   * Draws the inventory which displays the player's items.
   */
  void DrawInventory() const;

  /**
   * Draws the items in the inventory.
   */
  void DrawItems() const;

  /**
   * Draws the money the player currently has in the inventory menu.
   */
  void DrawMoney() const;

  /**
   * Draws the description of the inventory of the player.
   */
  void DrawInventoryDescription() const;

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
  void MovePlayerCamera();

  /**
   * Determines what the player character should look like
   * when they move in a particular direction.
   *
   * @return the TextureRef representing the image of the player character
   */
  cinder::gl::TextureRef GetPlayerImage() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves down.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetDownImagePath() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves up.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetUpImagePath() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves left.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetLeftImagePath() const;

  /**
   * Gets the direction image path to be displayed for the
   * player character when the user moves right.
   *
   * @return the string containing the correct image path to be displayed
   */
  std::string GetRightImagePath() const;

  /**
   *
   *
   * @param name
   * @param direction
   * @return
   */
  std::string GetActiveNpcImagePath
      (const std::string& name, const island::Direction& direction);

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
  void ExecutePlayerInteractions();

  /**
   * Handles the player's interactions with any npc, be it
   * talking or initiating a battle.
   */
  void ExecuteNpcInteraction(const island::Location& location);

  /**
   * Retrieves the text from a file.
   *
   * @param file_path the path to the file to be read from
   * @return the text stored in the file
   */
  std::string GetTextFromFile(const std::string& file_path) const;

  /** Represents the current state of the game. */
  GameState state_;

  /** The time elapsed since the update function has been called. */
  std::chrono::time_point<std::chrono::system_clock> last_time_;

  /** The handler for the background audio. */
  cinder::audio::VoiceRef background_audio_;

  /** The handler for the text displaying audio. */
  cinder::audio::VoiceRef text_audio_;

  /** The game engine responsible for running the game. */
  island::Engine engine_;

  /** The previous direction that the user moved in. */
  island::Direction prev_direction_;

  /** The location object to offset the rendering by, illusion of a camera. */
  island::Location camera_;

  /**
   * Stores the paths to the display files for the texts with the
   * tile as the key and the file path as the corresponding value.
   */
  std::unordered_map<island::Tile, std::string> display_text_files_;

  /**
   * Stores the npc dialogue with the name of the npc as the key and
   * the file path as the corresponding value.
   */
  std::unordered_map<std::string, std::string> npc_text_files_;

  /**
   * Stores the npc sprites with the name of the npc as the key and
   * the file path as the corresponding value.
   */
  std::unordered_map<std::string, std::string> npc_sprite_files_;

  /**
   * The npc sprites which are drawn on the screen, mapped with the npc name
   * as the key and the direction in which they are facing as the value.
   */
  std::unordered_map<std::string, island::Direction> active_npc_sprite_files_;

  /** The text to be displayed when the player interacts with the map. */
  std::string display_text_;

  /** The speed or delay of the game, i.e. a lesser value is faster. */
  size_t speed_;

  /** Keeps track of the characters to be displayed in a text message. */
  size_t char_counter_;

  /**
   * The number of directional commands
   * since the direction was last changed changed.
   */
  size_t last_changed_direction_;

  /**
   * Determines whether the user changed their direction
   * after the previous directional command.
   */
  bool is_changed_direction_;
};

}  // namespace islandapp

#endif  // FINALPROJECT_APPS_ISLANDAPP_H_

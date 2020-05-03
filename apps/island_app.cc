// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include "island_app.h"

#include <cinder/ImageIo.h>
#include <cinder/gl/draw.h>

#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
#endif

namespace islandapp {

using cinder::Color;
using cinder::Rectf;
using cinder::TextBox;
using cinder::ColorA;
using cinder::app::KeyEvent;
using island::Direction;
using island::Location;
using island::Tile;
using island::Npc;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

IslandApp::IslandApp()
    : engine_{island::kMapSize, island::kMapSize,
              std::vector<island::Item>(),
              "meow",
              {10, 4},
              {10, 10, 10, 10},
              std::vector<island::Item>(),
              1200},
      state_{GameState::kPlaying},
      speed_{kSpeed},
      char_counter_{0},
      last_changed_direction_{0},
      is_changed_direction_{false},
      prev_direction_{Direction::kDown},
      camera_{0,0}
      {}

void IslandApp::setup() {
  InitializeAudio();
  InitializeItems();
  InitializeDisplayFilePaths();
  InitializeNpcTextFilePaths();
  InitializeNpcSpriteFilePaths();
  InitializeActiveNpcSpriteFiles();

  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
}

void IslandApp::InitializeAudio() {
  cinder::audio::SourceFileRef background_src = cinder::audio::load
      (cinder::app::loadAsset("background_music.mp3"));
  background_audio_ = cinder::audio::Voice::create(background_src);
  background_audio_->start();

  cinder::audio::SourceFileRef text_src = cinder::audio::load
      (cinder::app::loadAsset("text_sound.wav"));
  text_audio_ = cinder::audio::Voice::create(text_src);
}

void IslandApp::InitializeItems() {
  island::Item shoe("shoe",
      "Footwear that helps you outspeed others in battle.",
      "assets/shoe.png");
  island::Item sword("sword",
                     "A legendary sword, it is said that it "
                     "grants the user amazing attack power.",
                     "assets/sword.png");
  island::Item shield("shield",
                      "Armour that increases your defensive prowess,"
                      " helping you take hits better in battle.",
                      "assets/shield.png");
  island::Item heart("heart",
                     "An extra heart, it will help strengthen "
                     "your life force in battle.",
                     "assets/heart.png");
  island::Item key("key",
                      "Looks like a key to someone's house",
                      "assets/key.png");

  engine_.AddItem(shoe);
  engine_.AddItem(sword);
  engine_.AddItem(shield);
  engine_.AddItem(heart);
  engine_.AddItem(key);
}

void IslandApp::InitializeDisplayFilePaths() {
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kCold, "assets/text/cold.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kFarm, "assets/text/farm.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kWater, "assets/text/water.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kPuddle, "assets/text/puddle.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kTree, "assets/text/flora.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kNotice, "assets/text/notice.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kMailBox, "assets/text/mail_box.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kDoor, "assets/text/closed_door.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kExtreme, "assets/text/extreme.txt"));
  display_text_files_.insert(std::pair<Tile, string>
      (Tile::kKey, "assets/text/key.txt"));
}

void IslandApp::InitializeNpcTextFilePaths() {
  for (const auto& npc : engine_.GetNpcs()) {
    npc_text_files_.insert(std::pair<string, string>
       (npc.name_, "assets/npc/dialogue/" + npc.name_ + ".txt"));
  }
  ChangeMarketDialogue();
}

void IslandApp::InitializeNpcSpriteFilePaths() {
  for (const auto& npc : engine_.GetNpcs()) {
    AddNpcSprites(npc.name_);
  }
}

void IslandApp::AddNpcSprites(const std::string& name) {
  npc_sprite_files_.insert(std::pair<string, string>
      (name + "_right", "assets/npc/images/" + name + "_right.png"));
  npc_sprite_files_.insert(std::pair<string, string>
      (name + "_left", "assets/npc/images/" + name + "_left.png"));
  npc_sprite_files_.insert(std::pair<string, string>
      (name + "_up", "assets/npc/images/" + name + "_up.png"));
  npc_sprite_files_.insert(std::pair<string, string>
      (name + "_down", "assets/npc/images/" + name + "_down.png"));
}

void IslandApp::InitializeActiveNpcSpriteFiles() {
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Rosalyn", Direction::kUp));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("John", Direction::kDown));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Azura", Direction::kLeft));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Klutz", Direction::kRight));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Rod", Direction::kUp));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Sven", Direction::kUp));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Elf", Direction::kUp));
  active_npc_sprite_files_.insert(std::pair<string, Direction>
      ("Boi", Direction::kUp));
}

void IslandApp::update() {
  if (state_ == GameState::kPaused) {
    return;
  }

  const auto time = system_clock::now();
  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    if (is_changed_direction_) {
      engine_.ExecuteTimeStep();
      is_changed_direction_ = false;
    }
    last_time_ = time;
  }

  if (!background_audio_->isPlaying()) {
    background_audio_->start();
  }

  MovePlayerCamera();
}

void IslandApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(Color(1,1,1));

  Translate(false);
  DrawMap();
  DrawPlayer();
  DrawNpcs();
  if (state_ == GameState::kDisplayingText || state_ == GameState::kMarket) {
    DrawTextBox();
  } else if (state_ == GameState::kInventory) {
    DrawInventory();
  }
  Translate(true);
}

void IslandApp::DrawMap() const {
  auto map = cinder::gl::Texture::create
      (cinder::loadImage("assets/map.png"));
  cinder::gl::draw(map, Rectf( 0,
                               0,
                               kMapTileSize * kScreenSize,
                               kMapTileSize * kScreenSize));
}

void IslandApp::DrawPlayer() const {
  Location loc = engine_.GetPlayer().location_;
  cinder::gl::TextureRef image = GetPlayerImage();
  cinder::gl::draw(image, Rectf( kPlayerTileSize * loc.GetRow(),
                                 kPlayerTileSize * loc.GetCol(),
                                 kPlayerTileSize * (loc.GetRow() + 1),
                                 kPlayerTileSize * (loc.GetCol() + 1)));
}

void IslandApp::DrawNpcs() {
  for (const auto& npc : engine_.GetNpcs()) {
    Location loc = npc.location_;
    Direction facing_direction = active_npc_sprite_files_[npc.name_];
    string image_path = GetActiveNpcImagePath(npc.name_, facing_direction);

    cinder::gl::TextureRef image =
        cinder::gl::Texture::create(cinder::loadImage(image_path));
    cinder::gl::draw(image, Rectf( kPlayerTileSize * loc.GetRow(),
                                   kPlayerTileSize * loc.GetCol(),
                                   kPlayerTileSize * (loc.GetRow() + 1),
                                   kPlayerTileSize * (loc.GetCol() + 1)));
  }
}

void IslandApp::DrawTextBox() {
  const cinder::vec2 center = getWindowCenter();
  const double width = getWindowWidth();
  const double height = getWindowHeight();
  const cinder::ivec2 size = {kTextBoxWidth, kTextBoxHeight};
  const Color color = Color::black();
  auto text_box = cinder::gl::Texture::create
      (cinder::loadImage("assets/text_box.png"));

  if (char_counter_ < display_text_.size()) {
    char_counter_ +=  kCharSpeed;
    text_audio_->start();
  }
  string to_display = display_text_.substr(0, char_counter_);

  Translate(true);
  cinder::gl::draw(text_box, Rectf( 0,
                              (center.y + height * kTextLocMultiplier)
                              / (kTextLocMultiplier + 1.0),
                              width, height));
  PrintText(to_display, color, size, {width, height});
  Translate(false);
}

void IslandApp::DrawInventory() const {
  const cinder::vec2 center = getWindowCenter();
  const double width = getWindowWidth();
  const double height = getWindowHeight();

  Translate(true);
  auto inventory = cinder::gl::Texture::create
      (cinder::loadImage("assets/inventory.png"));
  cinder::gl::draw(inventory, Rectf(center.x / kScreenDivider,
                               center.y / kScreenDivider,
                              (center.x + width) / kScreenDivider,
                              (center.y + height) / kScreenDivider));
  DrawItems();
  DrawMoney();
  DrawInventoryDescription();
  Translate(false);
}

template <typename C>
void IslandApp::PrintText(const string& text, const C& color,
    const cinder::ivec2& size, const cinder::vec2& loc) const {
  cinder::gl::color(color);
  const cinder::vec2 center = getWindowCenter();
  const double width = getWindowWidth();
  const double height = getWindowHeight();
  auto box = TextBox()
      .alignment(TextBox::LEFT)
      .font(cinder::Font(kNormalFont, kFontSize))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto texture = cinder::gl::Texture::create(box.render());
  cinder::gl::draw(texture,
      Rectf( kTextOffset,(center.y + height * kTextLocMultiplier) /
                    (kTextLocMultiplier + 1.0) + kTextOffset, width, height));
}

void IslandApp::DrawItems() const {
  const cinder::vec2 center = getWindowCenter();
  const double width = getWindowWidth();
  const double height = getWindowHeight();

  for (size_t ite = 0; ite < engine_.GetPlayer().inventory_.size(); ite++) {
    auto item_image = cinder::gl::Texture::create
        (cinder::loadImage
        (engine_.GetInventoryItem(ite).file_path_));

    double offset_start = (double) (ite) * 43.0 / 800.0 * width + width / 16.0;
    cinder::gl::draw(item_image,
        Rectf(center.x / kScreenDivider + offset_start,
              center.y / kScreenDivider + height * 90.0 / 800.0,
              center.x / kScreenDivider + offset_start + width / 20.0,
              center.y / kScreenDivider + height * 140 / 800.0));
  }
}

void IslandApp::DrawMoney() const {
  cinder::gl::color(Color::black());
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {150, 100};
  const double width = getWindowWidth();
  const double height = getWindowHeight();

  auto box = TextBox()
      .alignment(TextBox::LEFT)
      .font(cinder::Font(kNormalFont, kFontSize))
      .size(size)
      .color(Color::black())
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text("$" + std::to_string(engine_.GetPlayer().money_));

  const auto texture = cinder::gl::Texture::create(box.render());

  cinder::gl::draw(texture,
   Rectf( center.x / kScreenDivider + 50.0 / 800.0 * width,
          center.y / kScreenDivider + 20.0 / 800.0 * height,
          center.x / kScreenDivider + 200.0 / 800.0 * width,
          center.y / kScreenDivider + 100.0 / 800.0 * height));
}

void IslandApp::DrawInventoryDescription() const {
  cinder::gl::color(Color::black());
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {350, 130};
  const double width = getWindowWidth();
  const double height = getWindowHeight();
  string text;
  size_t inventory_size = engine_.GetPlayer().inventory_.size();

  if (inventory_size == 0) {
    text = "You have no items! You should try and search around, "
           "or perhaps even buy some.";
  } else if (inventory_size == kMaxInventorySize) {
    text = "You have all the items. I believed in you from the very beginning!";
  } else {
    text = "These items of yours sure are impressive, "
           "but there's still a few more you can get!";
  }

  auto box = TextBox()
      .alignment(TextBox::LEFT)
      .font(cinder::Font(kNormalFont, 2.0 * kFontSize / 3))
      .size(size)
      .color(Color::black())
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto texture = cinder::gl::Texture::create(box.render());

  cinder::gl::draw(texture,
     Rectf( center.x / kScreenDivider + 50.0 / 800.0 * width,
            center.y / kScreenDivider + 320.0 / 800.0 * height,
            center.x / kScreenDivider + 400.0 / 800.0 * width,
            center.y / kScreenDivider + 450.0 / 800.0 * height));
}

void IslandApp::Translate(bool is_up) const {
  float direction;
  if (is_up) {
    direction = 1.0;
  } else {
    direction = -1.0;
  }

  cinder::gl::translate(
      direction * (camera_.GetRow() * kTranslationMultiplier),
      direction * (camera_.GetCol() * kTranslationMultiplier));
}

cinder::gl::TextureRef IslandApp::GetPlayerImage() const {
  string image_path;
  switch (prev_direction_) {
    case Direction::kDown:
      image_path = GetDownImagePath();
      break;
    case Direction::kUp:
      image_path = GetUpImagePath();
      break;
    case Direction::kLeft:
      image_path = GetLeftImagePath();
      break;
    case Direction::kRight:
      image_path = GetRightImagePath();
      break;
  }

  return cinder::gl::Texture::create(cinder::loadImage(image_path));
}

string IslandApp::GetDownImagePath() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/player/down_nomove.png";
    case 1 :
      return "assets/player/down_left.png";
    case 2 :
      return "assets/player/down_nomove.png";
    case 3 :
      return "assets/player/down_right.png";
  }
  return "";
}

string IslandApp::GetUpImagePath() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/player/up_nomove.png";
    case 1 :
      return "assets/player/up_left.png";
    case 2 :
      return "assets/player/up_nomove.png";
    case 3 :
      return "assets/player/up_right.png";
  }
  return "";
}

string IslandApp::GetLeftImagePath() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/player/left_nomove.png";
    case 1 :
      return "assets/player/left_left.png";
    case 2 :
      return "assets/player/left_nomove.png";
    case 3 :
      return "assets/player/left_right.png";
  }
  return "";
}

string IslandApp::GetRightImagePath() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/player/right_nomove.png";
    case 1 :
      return "assets/player/right_left.png";
    case 2 :
      return "assets/player/right_nomove.png";
    case 3 :
      return "assets/player/right_right.png";
  }
  return "";
}

string IslandApp::GetActiveNpcImagePath
      (const string& name, const Direction& direction) {
  string dir_path;
  switch (direction) {
    case Direction::kUp :
      dir_path = "_up";
      break;
    case Direction::kDown :
      dir_path = "_down";
      break;
    case Direction::kLeft :
      dir_path = "_left";
      break;
    case Direction::kRight :
      dir_path = "_right";
      break;
  }
  return npc_sprite_files_[name + dir_path];
}


void IslandApp::MovePlayerCamera() {
  size_t screen_width = getWindowWidth();
  size_t screen_height = getWindowHeight();
  camera_.SetRow(engine_.GetPlayer().location_.GetRow() -
                            (screen_width / kScreenSize) / kScreenDivider);
  camera_.SetCol(engine_.GetPlayer().location_.GetCol() -
                            (screen_height / kScreenSize) / kScreenDivider);

  if (camera_.GetRow() < 0) {
    camera_.SetRow(0);
  }

  if (camera_.GetCol() < 0) {
    camera_.SetCol(0);
  }

  size_t max_camera_width = kMapTileSize - screen_width / kScreenSize;
  size_t max_camera_height = kMapTileSize - screen_height / kScreenSize;

  if (camera_.GetRow() > max_camera_width) {
    camera_.SetRow(max_camera_width);
  }

  if (camera_.GetCol() >  max_camera_height) {
    camera_.SetCol(max_camera_height);
  }
}

void IslandApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      HandleMovement(Direction::kUp);
      break;
    }

    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      HandleMovement(Direction::kDown);
      break;
    }

    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      HandleMovement(Direction::kLeft);
      break;
    }

    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      HandleMovement(Direction::kRight);
      break;
    }

    case KeyEvent::KEY_p: {
      if (state_ != GameState::kPaused) {
        state_ = GameState::kPaused;
      } else {
        state_ = GameState::kPlaying;
      }
      break;
    }

    case KeyEvent::KEY_z: {
      if ((state_ == GameState::kDisplayingText || state_ == GameState::kMarket)
        && char_counter_ != display_text_.size()) {
        char_counter_ = display_text_.size();
        return;
      } else {
        char_counter_ = 0;
      }

      ExecutePlayerInteractions(event);
      break;
    }

    case KeyEvent::KEY_x: {
      if (state_ == GameState::kDisplayingText) {
        return;
      } else if (state_ == GameState::kInventory) {
        state_ = GameState::kPlaying;
      } else {
        state_ = GameState::kInventory;
      }
      break;
    }

    case KeyEvent::KEY_y:
      ExecuteMarketInteraction(event);
      break;
  }
}

void IslandApp::HandleMovement(const Direction& direction) {
  if (state_ == GameState::kDisplayingText || state_ == GameState::kInventory) {
    return;
  }

  if (prev_direction_ == direction) {
    last_changed_direction_++;
  } else {
    last_changed_direction_ = 0;
  }
  prev_direction_ = direction;

  if (!engine_.IsValidDirection(direction)) {
    return;
  }

  is_changed_direction_ = true;
  engine_.SetDirection(direction);
}

void IslandApp::ExecutePlayerInteractions(const KeyEvent& key_event) {
  if (state_ == GameState::kDisplayingText) {
    state_ = GameState::kPlaying;
  } else if (state_ == GameState::kPlaying || state_ == GameState::kMarket){
    Location facing_location = engine_.GetFacingLocation(prev_direction_);
    Tile facing_tile = engine_.GetTileType(facing_location);
    string file_path;

    if (facing_location.GetRow() == kMarketLocation.GetRow()
      && facing_location.GetCol() == kMarketLocation.GetCol()) {
      ExecuteMarketInteraction(key_event);
      return;
    }

    if (facing_tile == island::kNpc) {
      ExecuteNpcInteraction(facing_location);
      return;
    }

    state_ = GameState::kDisplayingText;
    if (display_text_files_.count(facing_tile)) {
      if (facing_tile == Tile::kKey) {
        engine_.SetKey(true);
        engine_.AddInventoryItem(engine_.GetItem("key"));
        engine_.RemoveItem("key");
        engine_.SetTile(facing_location, Tile::kTree);
      }

      file_path = display_text_files_[facing_tile];
      display_text_ = GetTextFromFile(file_path);
    } else {
      state_ = GameState::kPlaying;
    }
  }
}

void IslandApp::ExecuteMarketInteraction(const KeyEvent& key_event) {
  if (npc_text_files_["Boi"] == "assets/npc/dialogue/Boi_no_items.txt") {
    return;
  }
  Npc npc = engine_.GetNpcAtLocation(kMarketLocation);
  UpdateActiveNpcSprites(npc);

  display_text_ = GetTextFromFile(npc_text_files_["Boi"]);
  if(key_event.getCode() == KeyEvent::KEY_y) {
    BuyItem(0);
  } else {
    if (state_ == GameState::kMarket) {
      state_ = GameState::kPlaying;
      return;
    } else {
      state_ = GameState::kMarket;
    }
  }
}

void IslandApp::BuyItem(size_t item_index) {
  bool has_enough_money = engine_.GetPlayer().money_ >= kItemPrice;
  if (has_enough_money && engine_.GetNumItems() > item_index) {
    ChangeMarketDialogue();
    engine_.AddInventoryItem(engine_.GetItemFromIndex(item_index));
    engine_.RemoveItem(engine_.GetItemFromIndex(item_index).name_);
    engine_.RemoveMoney(kItemPrice);
    state_ = GameState::kPlaying;
  } else {
    display_text_ = GetTextFromFile
        ("assets/npc/dialogue/Boi_no_money.txt");
  }
}

void IslandApp::ChangeMarketDialogue() {
  string dialogue = npc_text_files_["Boi"];
  if (dialogue == "assets/npc/dialogue/Boi.txt") {
    dialogue = "assets/npc/dialogue/Boi_shoes.txt";
  } else if (dialogue == "assets/npc/dialogue/Boi_shoes.txt") {
    dialogue = "assets/npc/dialogue/Boi_sword.txt";
  } else if (dialogue == "assets/npc/dialogue/Boi_sword.txt") {
    dialogue = "assets/npc/dialogue/Boi_shield.txt";
  } else if (dialogue == "assets/npc/dialogue/Boi_shield.txt") {
    dialogue = "assets/npc/dialogue/Boi_heart.txt";
  } else if (dialogue == "assets/npc/dialogue/Boi_heart.txt") {
    dialogue = "assets/npc/dialogue/Boi_no_items.txt";
  }
  npc_text_files_["Boi"] = dialogue;
}

void IslandApp::ExecuteNpcInteraction(const island::Location& location) {
  Npc npc = engine_.GetNpcAtLocation(location);

  if (npc_text_files_["Klutz"] == "assets/npc/dialogue/Klutz_during_key.txt") {
    npc_text_files_["Klutz"] = "assets/npc/dialogue/Klutz_after_key.txt";
  }

  UpdateActiveNpcSprites(npc);
  display_text_ = GetTextFromFile(npc_text_files_[npc.name_]);

  if (state_ == GameState::kDisplayingText) {
    state_ = GameState::kPlaying;
  } else {
    state_ = GameState::kDisplayingText;
  }

/*  if (npc.is_combatable_) {
    return;
  } else {

  }*/
}

void IslandApp::UpdateActiveNpcSprites(const Npc& npc) {
  Direction facing_direction;
  switch (prev_direction_) {
    case Direction::kUp :
      facing_direction = Direction::kDown;
      break;
    case Direction::kDown :
      facing_direction = Direction::kUp;
      break;
    case Direction::kLeft :
      facing_direction = Direction::kRight;
      break;
    case Direction::kRight :
      facing_direction = Direction::kLeft;
      break;
  }
  active_npc_sprite_files_[npc.name_] = facing_direction;
}

std::string IslandApp::GetTextFromFile(const string& file_path) {
  if (engine_.GetKey() && file_path == "assets/npc/dialogue/Klutz.txt") {
    engine_.SetKey(false);
    engine_.AddMoney(kKeyMoney);
    engine_.RemoveInventoryItem("key");
    npc_text_files_["Klutz"] = "assets/npc/dialogue/Klutz_during_key.txt";
  }

  std::ifstream file(file_path);
  std::string display_text;
  std::getline(file, display_text, '\0');

  return display_text;
}

}  // namespace islandapp

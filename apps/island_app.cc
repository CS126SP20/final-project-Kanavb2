// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include "island_app.h"

#include <cinder/ImageIo.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>

namespace islandapp {

using cinder::Color;
using cinder::Rectf;
using cinder::app::KeyEvent;
using island::Direction;
using island::Location;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

IslandApp::IslandApp()
    : engine_{island::kMapSize, island::kMapSize, "meow",
              {7, 0},
              {10, 10, 10, 10},
              std::vector<island::Item>(),
              0},
      state_{GameState::kPlaying},
      speed_{kSpeed},
      last_changed_direction_{0},
      is_changed_direction_{false},
      prev_direction_{Direction::kDown},
      camera_{0,0}
      {}

void IslandApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
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

  HandleCameraInteractions();
}

void IslandApp::draw() {
  if (state_ == GameState::kPaused) {
    return;
  }

  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(Color(1,1,1));
  cinder::gl::translate(
      - (camera_.GetRow() * kTranslationMultiplier),
      - (camera_.GetCol() * kTranslationMultiplier));

  DrawMap();
  DrawPlayer();

  cinder::gl::translate(
      (camera_.GetRow() * kTranslationMultiplier),
      (camera_.GetCol() * kTranslationMultiplier));
}

void IslandApp::DrawPlayer() const {
  Location loc = engine_.GetPlayer().location_;
  cinder::gl::TextureRef image = GetPlayerDirectionImage();
  cinder::gl::draw(image, Rectf( kPlayerTileSize * loc.GetRow(),
                                 kPlayerTileSize * loc.GetCol(),
                                 kPlayerTileSize * (loc.GetRow() + 1),
                                 kPlayerTileSize * (loc.GetCol() + 1)));
}

void IslandApp::DrawMap() const {
  auto map = cinder::gl::Texture::create
      (cinder::loadImage("assets/map.png"));
  cinder::gl::draw(map, Rectf( 0,
                                0,
                                kMapTileSize * kScreenSize,
                                kMapTileSize * kScreenSize));
}

cinder::gl::TextureRef IslandApp::GetPlayerDirectionImage() const {
  string image_path;
  switch (prev_direction_) {
    case Direction::kDown: {
      image_path = GetDownDirectionImage();
      break;
    }
    case Direction::kUp: {
      image_path = GetUpDirectionImage();
      break;
    }
    case Direction::kLeft: {
      image_path = GetLeftDirectionImage();
      break;
    }
    case Direction::kRight: {
      image_path = GetRightDirectionImage();
      break;
    }
  }

  return cinder::gl::Texture::create (cinder::loadImage(image_path));
}

string IslandApp::GetDownDirectionImage() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/down_nomove.png";
    case 1 :
      return "assets/down_left.png";
    case 2 :
      return "assets/down_nomove.png";
    case 3 :
      return "assets/down_right.png";
  }
  return "";
}

string IslandApp::GetUpDirectionImage() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/up_nomove.png";
    case 1 :
      return "assets/up_left.png";
    case 2 :
      return "assets/up_nomove.png";
    case 3 :
      return "assets/up_right.png";
  }
  return "";
}

string IslandApp::GetLeftDirectionImage() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/left_nomove.png";
    case 1 :
      return "assets/left_left.png";
    case 2 :
      return "assets/left_nomove.png";
    case 3 :
      return "assets/left_right.png";
  }
  return "";
}

string IslandApp::GetRightDirectionImage() const {
  switch (last_changed_direction_ % kNumSprites) {
    case 0 :
      return "assets/right_nomove.png";
    case 1 :
      return "assets/right_left.png";
    case 2 :
      return "assets/right_nomove.png";
    case 3 :
      return "assets/right_right.png";
  }
  return "";
}

void IslandApp::HandleCameraInteractions() {
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
    }

    case KeyEvent::KEY_z: {
      HandlePlayerInteractions();
    }
  }
}

void IslandApp::HandleMovement(Direction direction) {
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

void IslandApp::HandlePlayerInteractions() const {
  Location facing_tile = engine_.GetFacingLocation(prev_direction_);

}


}  // namespace islandapp

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include "island_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/ImageIo.h>

namespace islandapp {

using cinder::Color;
using cinder::Rectf;
using cinder::app::KeyEvent;
using island::Direction;
using island::Location;
using std::chrono::seconds;
using std::chrono::system_clock;

/** The number of movement sprites for the player. */
const size_t kNumSprites = 4;

/** The screen size in terms of tile size. */
const size_t kScreenSize = 40;

/** The tile size in for the player terms of pixels. */
const size_t kPlayerTileSize = 20;

/** The tile size in for the map terms of pixels. */
const size_t kMapTileSize = 25;

/** The speed of the player character. */
const size_t kSpeed = 50;

IslandApp::IslandApp()
    : engine_{island::kMapSize, island::kMapSize},
      state_{GameState::kPlaying},
      player_name_{"meow"},
      paused_{false},
      speed_{kSpeed},
      last_changed_direction_{0},
      is_changed_direction_{false},
      prev_direction_{Direction::kDown}
      {}

void IslandApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
}

void IslandApp::update() {
  if (paused_) {
    return;
  }

  const auto time = system_clock::now();
  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    if (is_changed_direction_) {
      engine_.Step();
      is_changed_direction_ = false;
    }
    last_time_ = time;
  }
}

void IslandApp::draw() {
  if (paused_) {
    return;
  }

  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(Color(1,1,1));
  DrawMap();
  DrawPlayer();
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
      (cinder::loadImage("resources/map.png"));
  cinder::gl::draw(map, Rectf( 0,
                                0,
                                kMapTileSize * (kScreenSize),
                                kMapTileSize * (kScreenSize)));
}

cinder::gl::TextureRef IslandApp::GetPlayerDirectionImage() const {
  std::string image_path;
  switch (prev_direction_) {
    case island::Direction::kDown: {
      switch (last_changed_direction_ % kNumSprites) {
        case 0 :
          image_path = "resources/down_nomove.png";
          break;
        case 1 :
          image_path = "resources/down_left.png";
          break;
        case 2 :
          image_path = "resources/down_nomove.png";
          break;
        case 3 :
          image_path = "resources/down_right.png";
          break;
      }
      break;
    }
    case Direction::kUp: {
      switch (last_changed_direction_ % kNumSprites) {
        case 0 :
          image_path = "resources/up_nomove.png";
          break;
        case 1 :
          image_path = "resources/up_left.png";
          break;
        case 2 :
          image_path = "resources/up_nomove.png";
          break;
        case 3 :
          image_path = "resources/up_right.png";
          break;
      }
      break;
    }
    case Direction::kLeft: {
      switch (last_changed_direction_ % kNumSprites) {
        case 0 :
          image_path = "resources/left_nomove.png";
          break;
        case 1 :
          image_path = "resources/left_left.png";
          break;
        case 2 :
          image_path = "resources/left_nomove.png";
          break;
        case 3 :
          image_path = "resources/left_right.png";
          break;
      }
      break;
    }
    case Direction::kRight: {
      switch (last_changed_direction_ % kNumSprites) {
        case 0 :
          image_path = "resources/right_nomove.png";
          break;
        case 1 :
          image_path = "resources/right_left.png";
          break;
        case 2 :
          image_path = "resources/right_nomove.png";
          break;
        case 3 :
          image_path = "resources/right_right.png";
          break;
      }
      break;
    }
  }

  return cinder::gl::Texture::create (cinder::loadImage(image_path));
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
      paused_ = !paused_;
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

}  // namespace myapp

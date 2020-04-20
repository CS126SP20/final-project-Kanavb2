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
const size_t kScreenSize = 16;

/** The center of the screen. */
const size_t kCenterScreen = 7;

/** The tile size in terms of pixels. */
const size_t kTileSize = 50;

/** The speed of the player character. */
const size_t kSpeed = 50;

IslandApp::IslandApp()
    : engine_{kScreenSize, kScreenSize},
      state_{GameState::kPlaying},
      player_name_{"meow"},
      paused_{false},
      speed_{kSpeed},
      last_changed_direction_{0},
      is_changed_direction_{false},
      prev_direction_{Direction::kDown}
      {}

void IslandApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
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
  cinder::gl::enableAlphaBlending();
  if (paused_) {
    return;
  }

  cinder::gl::clear();
  cinder::gl::clear(Color(0, 0, 0));
  DrawPlayer();
}

void IslandApp::DrawPlayer() const {
  Location loc = engine_.GetPlayer().location_;
  cinder::gl::TextureRef image = GetPlayerDirectionImage();
  cinder::gl::draw(image, Rectf( kTileSize * kCenterScreen,
                                 kTileSize * kCenterScreen,
                                 kTileSize * (kCenterScreen + 1),
                                 kTileSize * (kCenterScreen + 1)));
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
  is_changed_direction_ = true;
  engine_.SetDirection(direction);

  if (prev_direction_ == direction) {
    last_changed_direction_++;
  } else {
    last_changed_direction_ = 0;
  }
  prev_direction_ = direction;
}

}  // namespace myapp

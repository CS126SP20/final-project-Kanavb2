// Copyright (c) 2020 [Your Name]. All rights reserved.

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


IslandApp::IslandApp()
    : engine_{16, 16},
      state_{GameState::kPlaying},
      player_name_{"meow"},
      paused_{false},
      speed_{50},
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
  cinder::gl::draw(image, Rectf( 50 * loc.GetRow(),
                                 50 * loc.GetCol(),
                                 50 * loc.GetRow() + 50,
                                 50 * loc.GetCol() + 50));
}

cinder::gl::TextureRef IslandApp::GetPlayerDirectionImage() const {

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

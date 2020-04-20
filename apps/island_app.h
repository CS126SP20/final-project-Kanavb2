// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <island/engine.h>
#include <island/direction.h>
#include <island/location.h>

namespace islandapp {

enum class GameState {
  kPlaying,
  kPaused,
};

class IslandApp : public cinder::app::App {
public:
  IslandApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
  void DrawPlayer() const;
  cinder::gl::TextureRef GetPlayerDirectionImage() const;

private:
  island::Engine engine_;
  GameState state_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  const size_t speed_;
  const std::string player_name_;
  bool paused_;
  bool is_changed_direction_;
  size_t last_changed_direction_;
  island::Direction prev_direction_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

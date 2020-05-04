// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include "island_app.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace islandapp {

DEFINE_string(player_name, "Meow", "The name of the player");
DEFINE_bool(new_game, true, "Whether the player plays a new game");
DEFINE_string(load, "assets/saved_game.json",
    "The file path to the save state");

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("The Island");
}

}  // namespace islandapp

// This is a macro that runs the application.
CINDER_APP(islandapp::IslandApp,
           RendererGl(RendererGl::Options().msaa(islandapp::kSamples)),
           islandapp::SetUp)

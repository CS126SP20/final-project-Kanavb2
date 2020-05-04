// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include <string>
#include <vector>

#include "island_app.h"

using cinder::app::App;
using cinder::app::RendererGl;
using std::string;
using std::vector;

namespace islandapp {

DEFINE_string(player_name, "Meow", "The name of the player");
DEFINE_string(load, "assets/saved_game.json", "The save file");
DEFINE_bool(new_game, false, "Whether the player plays a new game");

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

/**
 * Parses the command line arguments using gflags
 *
 * @param args the vector to store the args in
 */
void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "Play a game of The Island. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

/**
 * The setup for the app, initializes the game's settings
 *
 * @param settings the settings from cinder::app
 */
void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("The Island");
}

}  // namespace islandapp

// This is a macro that runs the application.
CINDER_APP(islandapp::IslandApp,
           RendererGl(RendererGl::Options().msaa(islandapp::kSamples)),
           islandapp::SetUp)

// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "island_app.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace islandapp {

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

#include "breakout_app.h"

using breakout::BreakoutApp;

void prepareSettings(BreakoutApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BreakoutApp, ci::app::RendererGl, prepareSettings);

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>

#include "../include/gui.hpp"

int main() {
  Gui program;
  program.randomSetup();
  program.run();

  return 0;
}
#ifndef EGUI_HPP
#define EGUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>

#include "../include/body.hpp"

class Gui {
 public:
  ////////////////////////////////////////////////////////////////////////////////

  Gui();
  void setup();
  void randomSetup();
  void run();

 private:
  ////////////////////////////////////////////////////////////////////////////////
  // WINDOW

  sf::RenderWindow window_;
  std::vector<Body> bodies_;
  bool pause_{false};

  void bodiesUpdate();
  void bodiesDraw();

  ////////////////////////////////////////////////////////////////////////////////
};

#endif
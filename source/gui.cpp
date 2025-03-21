#include "../include/gui.hpp"

#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "../include/body.hpp"
#include "../include/constants.hpp"
#include "../include/graphics.hpp"

Gui::Gui()
    : window_(sf::VideoMode(constants::windowWidth, constants::windowHeight),
              "Three Body Problem") {}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setup() {
  Body sun1{30000000.f, {0.f, 0.f}, {0, 0}, {0, 0}, 15, sf::Color::Yellow};
  // Body sun2{1000000.f, {150.f, 0.f}, {0, -100}, {0, 0}, 15,
  // sf::Color::Yellow}; Body sun3{3000000.f, {0.f, 100.f}, {100, 0}, {0, 0},
  // 15, sf::Color::Yellow};

  Body body2{5000.f, {500.f, 0.f}, {0, 200}, {0, 0}, 5, sf::Color::Green};
  Body body3{7000.f, {-400.f, 0.f}, {0, -300}, {0, 0}, 5, sf::Color::Green};
  Body body4{100000.f, {-450.f, 0.f}, {0, -250}, {0, 0}, 5, sf::Color::Green};
  Body body5{3000.f, {350.f, 0}, {0, 150}, {0, 0}, 5, sf::Color::Green};

  sf::Color planet{sf::Color::Blue};

  Body sat1{100.f, {500.f, 10.f}, {20, 200}, {0, 0}, 3, planet};
  Body sat2{100.f, {-410.f, 0.f}, {0, -290}, {0, 0}, 3, planet};
  Body sat3{100.f, {-450.f, 15.f}, {15, -250}, {0, 0}, 3, planet};
  Body sat4{100.f, {-450.f, -15.f}, {-35, -250}, {0, 0}, 3, planet};
  Body sat5{100.f, {-475.f, 3.f}, {0, -220}, {0, 0}, 3, planet};
  Body sat6{100.f, {-460.f, 0.f}, {3, -270}, {0, 0}, 3, planet};

  bodies_.push_back(sun1);
  // bodies_.push_back(sun2);
  // bodies_.push_back(sun3);
  bodies_.push_back(body2);
  bodies_.push_back(body3);
  bodies_.push_back(body4);
  bodies_.push_back(body5);
  bodies_.push_back(sat1);
  bodies_.push_back(sat2);
  bodies_.push_back(sat3);
  bodies_.push_back(sat4);
  bodies_.push_back(sat5);
  bodies_.push_back(sat6);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::run() {
  window_.setPosition({constants::windowPosX, constants::windowPosY});
  window_.setFramerateLimit(constants::windowFrameRate);
  sf::Event event;

  while (window_.isOpen()) {
    while (window_.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed: {
          window_.close();
          break;
        }
        default:
          break;
      }
    }
    window_.clear(sf::Color::Black);

    bodiesDraw();
    bodiesUpdate();

    window_.display();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::bodiesUpdate() {
  for (size_t i{0}; i < bodies_.size(); i++) {
    for (size_t j{0}; j < bodies_.size(); j++) {
      if (i == j) {
        continue;
      }
      bodies_[i].interaction(bodies_[j]);
    }
    bodies_[i].update();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::bodiesDraw() {
  for (size_t i{0}; i < bodies_.size(); i++) {
    window_.draw(circleBody(bodies_[i]));
  }
}
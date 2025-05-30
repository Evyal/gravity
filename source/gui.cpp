#include "../include/gui.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cmath>
#include <cstddef>
#include <vector>

#include "../include/body.hpp"
#include "../include/constants.hpp"
#include "../include/graphics.hpp"
#include "../include/random.hpp"
#include "celestial.hpp"

Gui::Gui()
    : window_(sf::VideoMode(constants::windowWidth, constants::windowHeight),
              "Three Body Problem") {}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setup() {
  // sf::Color star{sf::Color::Yellow};

  // Body sun1{30000000.f, {0.f, 0.f}, {0, 0}, {0, 0}, 15, star};

  // sf::Color planet{sf::Color::Green};

  // Body body2{5000.f, {500.f, 0.f}, {0, 200}, {0, 0}, 5, planet};
  // Body body3{15000.f, {0, -400.f}, {300, 0}, {0, 0}, 5, planet};
  // Body body4{100000.f, {-450.f, 0.f}, {0, -250}, {0, 0}, 5, planet};
  // Body body5{3000.f, {350.f, 0}, {0, 150}, {0, 0}, 5, planet};

  // sf::Color satellite{sf::Color::Blue};

  // Body sat1{100.f, {500.f, 10.f}, {20, 200}, {0, 0}, 3, satellite};
  // Body sat2{100.f, {0, -415.f}, {324, 0}, {0, 0}, 3, satellite};
  // Body sat3{100.f, {-450.f, 35.f}, {35, -250}, {0, 0}, 3, satellite};
  // Body sat4{100.f, {-450.f, -45.f}, {-45, -250}, {0, 0}, 3, satellite};
  // Body sat5{100.f, {-485.f, 0.f}, {0, -295}, {0, 0}, 3, satellite};
  // Body sat6{100.f, {-425.f, 0.f}, {0, -215}, {0, 0}, 3, satellite};

  // bodies_.push_back(sun1);
  // bodies_.push_back(body2);
  // bodies_.push_back(body3);
  // bodies_.push_back(body4);
  // bodies_.push_back(body5);
  // bodies_.push_back(sat1);
  // bodies_.push_back(sat2);
  // bodies_.push_back(sat3);
  // bodies_.push_back(sat4);
  // bodies_.push_back(sat5);
  // bodies_.push_back(sat6);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::randomSetup() {
  // ThreeBody stars{randomThreeBody({0, 0})};
  // bodies_.push_back(stars.getStar(0));
  // bodies_.push_back(stars.getStar(1));
  // bodies_.push_back(stars.getStar(2));

  // bodies_.push_back(randomStar());
  // std::array<Body, 2> stars{randomTwoBody({0, 0})};
  // bodies_.push_back(stars[0]);
  // bodies_.push_back(stars[1]);

  // bodies_[0].setMass(2.4E8);
  // bodies_[0].setMass(1E10);
  bodies_.push_back(randomStar());

  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomPlanet(bodies_[0]));
  bodies_.push_back(randomSatellite(bodies_[5]));
  bodies_.push_back(randomSatellite(bodies_[5]));
  bodies_.push_back(randomSatellite(bodies_[5]));
  bodies_.push_back(randomSatellite(bodies_[5]));
  bodies_.push_back(randomSatellite(bodies_[5]));
  bodies_.push_back(randomSatellite(bodies_[4]));
  bodies_.push_back(randomSatellite(bodies_[3]));
  bodies_.push_back(randomSatellite(bodies_[3]));
  bodies_.push_back(randomSatellite(bodies_[4]));
  bodies_.push_back(randomSatellite(bodies_[4]));
  bodies_.push_back(randomSatellite(bodies_[3]));
  bodies_.push_back(randomSatellite(bodies_[3]));
  bodies_.push_back(randomSatellite(bodies_[4]));
  bodies_.push_back(randomSatellite(bodies_[4]));
  bodies_.push_back(randomSatellite(bodies_[6]));
  bodies_.push_back(randomSatellite(bodies_[7]));
  bodies_.push_back(randomSatellite(bodies_[7]));
  bodies_.push_back(randomSatellite(bodies_[8]));

  // COOL EFFECT WITH DEBRIS
  std::vector<Body> debris = randomDebrisGroup(bodies_[0]);
  for (size_t i{0}; i < debris.size(); i++) {
    bodies_.push_back(debris[i]);
  }
  debris.clear();

  debris = randomDebrisGroup(bodies_[0]);
  for (size_t i{0}; i < debris.size(); i++) {
    bodies_.push_back(debris[i]);
  }
  debris.clear();

  debris = randomDebrisGroup(bodies_[0]);
  for (size_t i{0}; i < debris.size(); i++) {
    bodies_.push_back(debris[i]);
  }
  debris.clear();

  debris = randomDebrisGroup(bodies_[0]);
  for (size_t i{0}; i < debris.size(); i++) {
    bodies_.push_back(debris[i]);
  }
  debris.clear();

  ///////////////////////////////////////////////////////////////////////////

  // debris = randomDebrisGroup(bodies_[0]);
  // for (size_t i{0}; i < debris.size(); i++) {
  //   bodies_.push_back(debris[i]);
  // }
  // debris.clear();

  // debris = randomDebrisGroup(bodies_[0]);
  // for (size_t i{0}; i < debris.size(); i++) {
  //   bodies_.push_back(debris[i]);
  // }
  // debris.clear();

  // debris = randomDebrisGroup(bodies_[0]);
  // for (size_t i{0}; i < debris.size(); i++) {
  //   bodies_.push_back(debris[i]);
  // }
  // debris.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::run() {
  window_.setPosition({constants::windowPosX, constants::windowPosY});
  window_.setFramerateLimit(constants::windowFrameRate);
  window_.setFramerateLimit(constants::windowFrameRate);
  sf::Event event;

  sf::View view(
      sf::FloatRect(0, 0, constants::windowWidth, constants::windowHeight));
  view.zoom(5.f);

  sf::Clock clock;

  while (window_.isOpen()) {
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          pause_ = !pause_;
          continue;
        }

        if (event.key.code == sf::Keyboard::R) {
          bodies_.clear();
          randomSetup();
        }
      }

      switch (event.type) {
        case sf::Event::Closed: {
          window_.close();
          break;
        }
        default:
          break;
      }
    }

    float deltaTime = clock.restart().asSeconds();
    float moveSpeed = 1000.f;

    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) movement.x -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      movement.x += moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) movement.y -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) movement.y += moveSpeed;
    view.move(movement * deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) view.zoom(0.99f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) view.zoom(1.01f);

    window_.setView(view);

    window_.clear(sf::Color{20, 20, 20});

    bodiesDraw();

    if (!pause_) {
      bodiesUpdate();
    }

    window_.display();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::bodiesUpdate() {
  bool merged;
  do {
    merged = false;
    for (size_t i = 0; i < bodies_.size(); i++) {
      for (size_t j = i + 1; j < bodies_.size(); j++) {
        if (i == j) {
          continue;
        }
        if (mergeBodies(bodies_, i, j)) {
          merged = true;
          break;
        }
      }
      if (merged) {
        break;  // Exit the outer loop as well if a merge occurred
      }
    }
  } while (merged);  // Repeat if a merge occurred

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

//////////////////////////////////////////////////////////////////////////////////////////

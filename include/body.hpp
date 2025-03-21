#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "constants.hpp"

//////////////////////////////////////////////////////////////////////////////////////////

class Body {
 private:
  float mass_{};
  sf::Vector2f position_{};
  sf::Vector2f velocity_{};
  sf::Vector2f acceleration_{};

  float size_{constants::defaultBodySize};
  sf::Color color_{sf::Color::Yellow};

  //////////////////////////////////////////////////////////////////////////////////////////

 public:
  Body();
  Body(float mass, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc);
  Body(float mass, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc,
       float size, sf::Color color);

  //////////////////////////////////////////////////////////////////////////////////////////

  float getMass() const;
  sf::Vector2f getPosition() const;
  sf::Vector2f getVelocity() const;
  sf::Vector2f getAcceleration() const;
  float getSize() const;
  sf::Color getColor() const;

  //////////////////////////////////////////////////////////////////////////////////////////

  void setMass(float mass);
  void setPosition(sf::Vector2f position);
  void setVelocity(sf::Vector2f velocity);
  void setAcceleration(sf::Vector2f acceleration);

  //////////////////////////////////////////////////////////////////////////////////////////

  void interaction(const Body& b);

  //////////////////////////////////////////////////////////////////////////////////////////

  void update();
};

//////////////////////////////////////////////////////////////////////////////////////////

float distance(const Body& b1, const Body& b2);
sf::Vector2f massCenter(const Body& b1, const Body& b2);
sf::Vector2f massCenterVelocity(const Body& b1, const Body& b2);
sf::Color mergeColour(const Body& b1, const Body& b2);
float mergeSize(const Body& b1, const Body& b2);

//////////////////////////////////////////////////////////////////////////////////////////

bool mergeBodies(std::vector<Body>& bodies, size_t i, size_t j);

//////////////////////////////////////////////////////////////////////////////////////////

#endif
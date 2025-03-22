#include "../include/body.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "../include/constants.hpp"

//////////////////////////////////////////////////////////////////////////////////////////

Body::Body()
    : mass_{constants::defaultBodyParameters.mass},
      position_{constants::defaultBodyParameters.pos},
      velocity_{constants::defaultBodyParameters.vel},
      acceleration_{constants::defaultBodyParameters.acc} {}

Body::Body(float mass, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc)
    : mass_{mass}, position_{pos}, velocity_{vel}, acceleration_{acc} {}

Body::Body(float mass, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc,
           float size, sf::Color color)
    : Body(mass, pos, vel, acc) {
  size_ = size;
  color_ = color;
}

//////////////////////////////////////////////////////////////////////////////////////////

float Body::getMass() const { return mass_; }
sf::Vector2f Body::getPosition() const { return position_; }
sf::Vector2f Body::getVelocity() const { return velocity_; }
sf::Vector2f Body::getAcceleration() const { return acceleration_; }
float Body::getSize() const { return size_; }
sf::Color Body::getColor() const { return color_; }

//////////////////////////////////////////////////////////////////////////////////////////

void Body::setMass(float mass) { mass_ = mass; }
void Body::setPosition(sf::Vector2f position) { position_ = position; }
void Body::setVelocity(sf::Vector2f velocity) { velocity_ = velocity; }
void Body::setAcceleration(sf::Vector2f acceleration) {
  acceleration_ = acceleration;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Body::interaction(const Body& b) {
  acceleration_ += constants::interactionStrength * b.getMass() *
                   (b.getPosition() - getPosition()) /
                   powf(distance(*this, b), 3);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Body::update() {
  setVelocity(getVelocity() + getAcceleration() / constants::scalingFactor);
  setPosition(getPosition() + getVelocity() / constants::scalingFactor);
  setAcceleration({0, 0});
}

//////////////////////////////////////////////////////////////////////////////////////////

float distance(const Body& b1, const Body& b2) {
  float dx = b1.getPosition().x - b2.getPosition().x;
  float dy = b1.getPosition().y - b2.getPosition().y;
  return sqrtf(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2f massCenter(const Body& b1, const Body& b2) {
  return (b1.getPosition() * b1.getMass() + b2.getPosition() * b2.getMass()) /
         (b1.getMass() + b2.getMass());
}

//////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2f massCenterVelocity(const Body& b1, const Body& b2) {
  return (b1.getVelocity() * b1.getMass() + b2.getVelocity() * b2.getMass()) /
         (b1.getMass() + b2.getMass());
}

//////////////////////////////////////////////////////////////////////////////////////////

sf::Color mergeColour(const Body& b1, const Body& b2) {
  float s1 = b1.getSize();
  float s2 = b2.getSize();
  sf::Uint8 red = static_cast<sf::Uint8>(
      (b1.getColor().r * s1 * s1 + b2.getColor().r * s2 * s2) /
      (s1 * s1 + s2 * s2));
  sf::Uint8 green = static_cast<sf::Uint8>(
      (b1.getColor().g * s1 * s1 + b2.getColor().g * s2 * s2) /
      (s1 * s1 + s2 * s2));
  sf::Uint8 blue = static_cast<sf::Uint8>(
      (b1.getColor().b * s1 * s1 + b2.getColor().b * s2 * s2) /
      (s1 * s1 + s2 * s2));
  return sf::Color{red, green, blue};
}

//////////////////////////////////////////////////////////////////////////////////////////

float mergeSize(const Body& b1, const Body& b2) {
  return sqrtf(b1.getSize() * b1.getSize() + b2.getSize() * b2.getSize());
}

//////////////////////////////////////////////////////////////////////////////////////////

bool mergeBodies(std::vector<Body>& bodies, size_t i, size_t j) {
  const Body& b1 = bodies[i];
  const Body& b2 = bodies[j];

  if (distance(b1, b2) > (b1.getSize() + b2.getSize()) / 1.5f) {
    return false;
  }

  Body mergedBody{b1.getMass() + b2.getMass(), massCenter(b1, b2),
                  massCenterVelocity(b1, b2),  {0, 0},
                  mergeSize(b1, b2),           mergeColour(b1, b2)};
  bodies.emplace_back(mergedBody);

  bodies.erase(bodies.begin() + static_cast<long>(i));
  if (i > j) {
    bodies.erase(bodies.begin() + static_cast<long>(j));
  } else {
    bodies.erase(bodies.begin() + static_cast<long>(j - 1));
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
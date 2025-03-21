#include "../include/body.hpp"

#include <cmath>
#include <cstdlib>

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
  float bigger = this->size_ > b.size_ ? this->size_ : b.size_;
  if (distance(*this, b) < bigger) {
    return;
  }
  acceleration_ += constants::interactionStrength * b.getMass() *
                   (b.getPosition() - getPosition()) /
                   powf(distance(*this, b), 3);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Body::update() {
  setVelocity(getVelocity() + getAcceleration() / 500.f);
  setPosition(getPosition() + getVelocity() / 500.f);
  setAcceleration({0, 0});
}

//////////////////////////////////////////////////////////////////////////////////////////

float distance(const Body& b1, const Body& b2) {
  float dx = b1.getPosition().x - b2.getPosition().x;
  float dy = b1.getPosition().y - b2.getPosition().y;
  return sqrtf(dx * dx + dy * dy);
}

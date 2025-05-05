#include "../include/random.hpp"

#include <SFML/System/Vector2.hpp>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

#include "../include/constants.hpp"
#include "../include/body.hpp"
#include "../include/celestial.hpp"

std::default_random_engine rng(static_cast<size_t>(
    std::chrono::steady_clock::now().time_since_epoch().count()));

//////////////////////////////////////////////////////////////////////////////////////////

float logBase(float x, float base) { return logf(x) / logf(base); }

//////////////////////////////////////////////////////////////////////////////////////////
// Generate a RANDOM INTEGER (SIZE_T) in the RANGE [min, max], inclusive

size_t randomInt(size_t min, size_t max) {
  std::uniform_int_distribution dist(min, max);
  return dist(rng);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generate a random FLOAT in the range (min, max]

float randomFloat(float min, float max) {
  std::uniform_real_distribution dist(min, max);
  return dist(rng);
}

//////////////////////////////////////////////////////////////////////////////////////////

float randomAngle() { return randomFloat(0, 2 * M_PIf); }

//////////////////////////////////////////////////////////////////////////////////////////

float randomLogFloat(float min, float max) {
  std::uniform_real_distribution<float> dist(std::log(min), std::log(max));
  return std::exp(dist(rng));
}

//////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2f randomPoint(float min, float max) {
  std::uniform_real_distribution dist(min, max);
  return {dist(rng), dist(rng)};
}

//////////////////////////////////////////////////////////////////////////////////////////

Body randomStar(sf::Vector2f center) {
  Body body{
      randomLogFloat(constants::minRandomStarMass,
                     constants::maxRandomStarMass),
      center,
      {0, 0},
      {0, 0},
      randomFloat(constants::minRandomStarSize, constants::maxRandomStarSize),
      constants::starColor};
  return body;
}

std::array<Body, 2> randomTwoBody(sf::Vector2f center) {
  float d = randomFloat(0, 1000);
  float a = randomAngle();
  sf::Vector2f center1{center.x + d * cosf(a), center.y + d * sinf(a)};
  float mass1{randomLogFloat(constants::minRandomStarMass,
                             constants::maxRandomStarMass)};
  float size1{logBase(mass1, 10) * logBase(mass1, 10)};

  Body body1{mass1, center1, {0, 0}, {0, 0}, size1, constants::starColor};

  d = randomFloat(0, 1000);
  a = randomAngle();
  sf::Vector2f center2{center.x + d * cosf(a), center.y + d * sinf(a)};
  float mass2{randomLogFloat(constants::minRandomStarMass,
                             constants::maxRandomStarMass)};
  float size2{logBase(mass2, 10) * logBase(mass2, 10)};

  Body body2{mass2, center2, {0, 0}, {0, 0}, size2, constants::starColor};

  float d12x = (body1.getPosition().x - body2.getPosition().x);
  float d12y = (body1.getPosition().y - body2.getPosition().y);
  float d12 = sqrtf(d12x * d12x + d12y * d12y);
  float a12 = static_cast<float>(atan2(d12y, d12x));

  float v12{sqrtf(mass2 * mass2 / d12 / (mass1 + mass2))};
  float v21{sqrtf(mass1 * mass1 / d12 / (mass1 + mass2))};

  body1.setVelocity({v12 * sinf(a12), -v12 * cosf(a12)});
  body2.setVelocity({v21 * sinf(a12), v21 * cosf(a12)});

  return {body1, body2};
}

std::array<Body, 3> randomThreeBody(sf::Vector2f center) {
  sf::Vector2f center1{center.x + 500, center.y + 433};
  float mass1{randomLogFloat(constants::minRandomStarMass,
                             constants::maxRandomStarMass)};
  float size1{logBase(mass1, 10) * logBase(mass1, 10)};

  Body body1{mass1, center1, {0, 0}, {0, 0}, size1, constants::starColor};

  sf::Vector2f center2{center.x - 500, center.y + 433};
  float mass2{randomLogFloat(constants::minRandomStarMass,
                             constants::maxRandomStarMass)};
  float size2{logBase(mass1, 10) * logBase(mass1, 10)};

  Body body2{mass2, center2, {0, 0}, {0, 0}, size2, constants::starColor};

  sf::Vector2f center3{center.x, center.y - 433};
  float mass3{randomLogFloat(constants::minRandomStarMass,
                             constants::maxRandomStarMass)};
  float size3{logBase(mass3, 10) * logBase(mass3, 10)};

  Body body3{mass3, center3, {0, 0}, {0, 0}, size3, constants::starColor};

  float omega = -sqrtf((mass1 + mass2 + mass3) / (1000 * 1000 * 1000));
  sf::Vector2f centerMass =
      ((mass1 * center1 + mass2 * center2 + mass3 * center3) /
       (mass1 + mass2 + mass3));

  sf::Vector2f displacement1 = center1 - centerMass;
  sf::Vector2f displacement2 = center2 - centerMass;
  sf::Vector2f displacement3 = center3 - centerMass;

  sf::Vector2f v1 = {-omega * displacement1.y, omega * displacement1.x};
  sf::Vector2f v2 = {-omega * displacement2.y, omega * displacement2.x};
  sf::Vector2f v3 = {-omega * displacement3.y, omega * displacement3.x};

  body1.setVelocity(v1);
  body2.setVelocity(v2);
  body3.setVelocity(v3);

  return {body1, body2, body3};
}

Body randomPlanet(const Body &star) {
  float mass{randomLogFloat(constants::minRandomPlanetMass,
                            constants::maxRandomPlanetMass)};
  float d = randomFloat(constants::minRandomPlanetDistance,
                        constants::maxRandomPlanetDistance);
  float a = randomFloat(0, 2 * M_PIf);
  sf::Vector2f centerOffset = {d * cosf(a), d * sinf(a)};

  float vx = randomFloat(constants::minRandomSpeedVarFactor,
                         constants::maxRandomSpeedVarFactor);
  float vy = randomFloat(constants::minRandomSpeedVarFactor,
                         constants::maxRandomSpeedVarFactor);

  float v = sqrtf(star.getMass() / d);
  sf::Vector2f vel = {v * vx * sinf(a), -v * vy * cosf(a)};

  Body body{mass,
            star.getPosition() + centerOffset,
            {vel.x, vel.y},
            {0, 0},
            randomFloat(constants::minRandomPlanetSize,
                        constants::maxRandomPlanetSize),
            constants::planetColor};
  return body;
}

Body randomSatellite(const Body &planet) {
  float mass{randomLogFloat(constants::minRandomSatelliteMass,
                            constants::maxRandomSatelliteMass)};
  float d = randomFloat(constants::minRandomSatelliteDistance,
                        constants::maxRandomSatelliteDistance);
  float a = randomFloat(0, 2 * M_PIf);
  sf::Vector2f centerOffset = {d * cosf(a), d * sinf(a)};

  float vx = randomFloat(constants::minRandomSpeedVarFactor,
                         constants::maxRandomSpeedVarFactor);
  float vy = randomFloat(constants::minRandomSpeedVarFactor,
                         constants::maxRandomSpeedVarFactor);

  float v = sqrtf(planet.getMass() / d);
  sf::Vector2f vel = {v * vx * sinf(a), -v * vy * cosf(a)};

  Body body{mass,
            planet.getPosition() + centerOffset,
            {planet.getVelocity().x + vel.x, planet.getVelocity().y + vel.y},
            {0, 0},
            randomFloat(constants::minRandomSatelliteSize,
                        constants::maxRandomSatelliteSize),
            constants::satelliteColor};
  return body;
}

Body randomDebris() {
  float mass{randomLogFloat(constants::minRandomDebrisMass,
                            constants::maxRandomDebrisMass)};
  float x =
      randomFloat(-constants::windowWidth / 2.f, constants::windowWidth / 2.f);
  float y = randomFloat(-constants::windowHeight / 2.f,
                        constants::windowHeight / 2.f);

  sf::Vector2f vel{
      randomFloat(-constants::randomDebrisSpeed, constants::randomDebrisSpeed),
      randomFloat(-constants::randomDebrisSpeed, constants::randomDebrisSpeed)};

  Body body{mass,
            {x, y},
            vel,
            {0, 0},
            randomFloat(constants::minRandomDebrisSize,
                        constants::maxRandomDebrisSize),
            constants::debrisColor};
  return body;
}

Body randomDebris(sf::Vector2f center, sf::Vector2f velocity) {
  float mass{randomLogFloat(constants::minRandomDebrisMass,
                            constants::maxRandomDebrisMass)};
  float c{randomFloat(constants::minRandomDebrisCenterDistance,
                      constants::maxRandomDebrisCenterDistance)};
  float d = randomFloat(0, c);
  float a = randomFloat(0, 2 * M_PIf);

  sf::Vector2f newCenter = {center.x + d * cosf(a), center.y + d * sinf(a)};

  velocity.x +=
      randomFloat(-constants::randomDebrisSpeed, constants::randomDebrisSpeed);
  velocity.y +=
      randomFloat(-constants::randomDebrisSpeed, constants::randomDebrisSpeed);

  Body body{mass,
            newCenter,
            {velocity.x, velocity.y},
            {0, 0},
            randomFloat(constants::minRandomDebrisSize,
                        constants::maxRandomDebrisSize),
            constants::debrisColor};
  return body;
}

std::vector<Body> randomDebrisGroup(const Body &star) {
  std::vector<Body> debris{};
  float d = randomFloat(3000, 7000);
  float a = randomFloat(0, 2 * M_PIf);
  sf::Vector2f center{star.getPosition().x + d * cosf(a),
                      star.getPosition().y + d * sinf(a)};
  float v = sqrtf(star.getMass() / d);
  sf::Vector2f vel{v * sinf(a), -v * cosf(a)};

  for (size_t i{0}; i < randomInt(30, 70); i++) {
    debris.emplace_back(randomDebris(center, vel));
  }
  return debris;
}

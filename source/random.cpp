#include "../include/random.hpp"

#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <chrono>
#include <cmath>
#include <random>

#include "../include/constants.hpp"

std::default_random_engine rng(static_cast<size_t>(
    std::chrono::steady_clock::now().time_since_epoch().count()));

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
  float d = randomFloat(3000,7000);
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

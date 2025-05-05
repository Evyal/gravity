#ifndef RANDOM_H
#define RANDOM_H

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

#include "../include/body.hpp"
#include "celestial.hpp"

extern std::default_random_engine rng;

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating NUMBERS

size_t randomInt(size_t min, size_t max);
float randomFloat(float min, float max);
float randomLogFloat(float min, float max);
sf::Vector2f randomPoint(float min, float max);

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating BODIES

Body randomStar(sf::Vector2f center = {0, 0});
std::array<Body, 2> randomTwoBody(sf::Vector2f center = {0, 0});
std::array<Body, 3> randomThreeBody(sf::Vector2f center = {0, 0});
Body randomPlanet(const Body &star);
Body randomSatellite(const Body &planet);
Body randomDebris();
Body randomDebris(sf::Vector2f center, sf::Vector2f velocity);
std::vector<Body> randomDebrisGroup(const Body &star);

#endif
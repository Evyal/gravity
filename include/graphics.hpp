#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

#include "body.hpp"

// DRAW BOID

sf::CircleShape circleBody(const Body &boid);

// sf::RectangleShape getRectangle(const RectanglePar &par,
//                                 const sf::Color &color = sf::Color::Black);

#endif
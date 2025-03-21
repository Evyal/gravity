#include "../include/graphics.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "../include/body.hpp"
#include "../include/constants.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS as TRIANGLES

sf::CircleShape circleBody(const Body &b) {
  float size = b.getSize();
  sf::CircleShape boidBody(size);
  boidBody.setFillColor(b.getColor());
  boidBody.setOrigin(size, size);
  boidBody.setPosition(b.getPosition() + constants::offset);

  return boidBody;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE RECTANGLE

// sf::RectangleShape getRectangle(const RectanglePar &par,
//                                 const sf::Color &color) {
//   sf::RectangleShape rectangle(sf::Vector2f(par.width, par.height));
//   rectangle.setPosition(par.posX, par.posY);
//   rectangle.setFillColor(color);
//   return rectangle;
// }

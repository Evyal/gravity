#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

struct BodyPar {
  float mass{};
  sf::Vector2f pos{};
  sf::Vector2f vel{};
  sf::Vector2f acc{};
};

namespace constants {
////////////////////////////////////////////////////////////////////////////////////////////////////
inline constexpr long windowWidth{1440};
inline constexpr long windowHeight{960};
inline constexpr long windowPosX{120};
inline constexpr long windowPosY{10};
inline constexpr int windowFrameRate{100};
inline const sf::Vector2f offset{static_cast<float>(windowWidth) / 2,
                                 static_cast<float>(windowHeight) / 2};

inline constexpr float defaultMass{1.f};
inline const sf::Vector2f defaultPosition{10.f, 10.f};
inline const sf::Vector2f defaultVelocity{0.f, 0.f};
inline const sf::Vector2f defaultAcceleration{0.f, 0.f};

inline const BodyPar defaultBodyParameters{
    defaultMass, defaultPosition, defaultVelocity, defaultAcceleration};

inline constexpr float interactionStrength{1.f};

inline constexpr float defaultBodySize{5.f};

inline const sf::Color planetColour{sf::Color{60, 10, 0}};

////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace constants

#endif
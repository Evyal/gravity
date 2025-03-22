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
inline constexpr float scalingFactor{10000.f};
inline const sf::Vector2f offset{static_cast<float>(windowWidth) / 2,
                                 static_cast<float>(windowHeight) / 2};

inline constexpr float defaultMass{1.f};
inline const sf::Vector2f defaultPosition{10.f, 10.f};
inline const sf::Vector2f defaultVelocity{0.f, 0.f};
inline const sf::Vector2f defaultAcceleration{0.f, 0.f};
inline constexpr float defaultBodySize{5.f};
inline constexpr float interactionStrength{1.f};

inline const BodyPar defaultBodyParameters{
    defaultMass, defaultPosition, defaultVelocity, defaultAcceleration};

inline const sf::Color starColor{sf::Color::Yellow};
inline constexpr float maxRandomStarMass{1E10};
inline constexpr float minRandomStarMass{1E9};
inline constexpr float maxRandomStarSize{100.f};
inline constexpr float minRandomStarSize{50.f};

inline const sf::Color planetColor{sf::Color::Green};
inline constexpr float maxRandomPlanetMass{1E8};
inline constexpr float minRandomPlanetMass{1E7};
inline constexpr float maxRandomPlanetSize{15.f};
inline constexpr float minRandomPlanetSize{10.f};
inline constexpr float maxRandomPlanetDistance{10000.f};
inline constexpr float minRandomPlanetDistance{1000.f};

inline const sf::Color satelliteColor{sf::Color::Blue};
inline constexpr float maxRandomSatelliteMass{1000.f};
inline constexpr float minRandomSatelliteMass{10.f};
inline constexpr float maxRandomSatelliteSize{5.0f};
inline constexpr float minRandomSatelliteSize{2.0f};
inline constexpr float maxRandomSatelliteDistance{75.f};
inline constexpr float minRandomSatelliteDistance{20.f};

inline const sf::Color debrisColor{sf::Color::Red};
inline constexpr float maxRandomDebrisMass{10.f};
inline constexpr float minRandomDebrisMass{1.};
inline constexpr float maxRandomDebrisSize{2.5f};
inline constexpr float minRandomDebrisSize{0.5f};
inline constexpr float maxRandomDebrisCenterDistance{500.f};
inline constexpr float minRandomDebrisCenterDistance{100.f};
inline constexpr float randomDebrisSpeed{5.f};

inline constexpr float maxRandomSpeedVarFactor{1.05f};
inline constexpr float minRandomSpeedVarFactor{0.95f};

////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace constants

#endif
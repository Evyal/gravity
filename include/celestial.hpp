#ifndef CELESTIAL_HPP
#define CELESTIAL_HPP

#include "body.hpp"

class Star : Body {};

class Planet : Body {};
class Satellite : Body {};
class Comet : Body {};
class Debris : Body {};

#endif
/**
 * @file aabb.cpp
 * @author Dayne Pefley
 * @brief defines the member functions for the aabb
 */

#ifndef AABB_CPP
#define AABB_CPP
#include "aabb.hpp"
#include "SFML/System/Vector2.hpp"

Aabb::Aabb()
  : Aabb({0,0}, {0,0}){}

Aabb::Aabb(const sf::Vector2f &min, const sf::Vector2f &max)
    : min(min), max(max) {}

#endif // !AABB_CPP

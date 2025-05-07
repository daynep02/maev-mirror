/**
 * @file Circle.cpp
 * @author Dayne Pefley
 * @brief defines the functions for the circle class
 */

#ifndef CIRCLE_CPP
#define CIRCLE_CPP

#include "circle.hpp"
#include "rectangle.hpp"
#include "SFML/System/Vector2.hpp"
Circle::Circle() : Circle({0, 0}, 1.0f) {};

Circle::Circle(const sf::Vector2f &position, float radius) {
  shape.setPosition(position);
  shape.setRadius(radius);
}

Circle::~Circle() {}

bool Circle::CollidesWith(Circle *other) {

  if(!HitsBox(other)) return false;

  const sf::Vector2f &ourCenter = shape.getGeometricCenter();
  const sf::Vector2f &theirCenter = other->shape.getGeometricCenter();
  auto s = ourCenter - theirCenter;
  return s.length() < (shape.getRadius() + other->shape.getRadius());

}

bool Circle::CollidesWith(Rectangle* other) {
  if (!HitsBox(other)) return false;
}
#endif // !CIRCLE_CPP

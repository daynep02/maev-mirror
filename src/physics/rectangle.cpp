/**
 * @file Rectangle.cpp
 * @author Dayne Pefley
 * @brief defines the hittable circle
 * this file currently goes unused
 */
#ifndef RECTANGLE_CPP
#define RECTANGLE_CPP
#include "rectangle.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "circle.hpp"

/**
 * @brief a collidable rectangle for the physics system
 */
/**
 * @brief creates a circle at 0,0, with size 1
 */
Rectangle::Rectangle() {}

/**
 * @param position the position at wich the ball is to be created
 * @param radius the radius of the ball
 */
Rectangle::Rectangle(const sf::Vector2f &position, const sf::Vector2f &size)
    : shape(size) {
  shape.setPosition(position);
  vertices[0] = position;
  vertices[1] = {position.x + size.x, position.y};
  vertices[2] = {position.x, position.y + size.y};
  vertices[3] = position + size;

  edges[0] = vertices[0] - vertices[1];
  edges[1] = vertices[0] - vertices[2];
  edges[2] = vertices[1] - vertices[3];
  edges[3] = vertices[2] - vertices[3];

}

/**)
 * @brief destructor for this class, no cleanup needed
 */
Rectangle::~Rectangle() {}

/**
 * @param other the other object to be check for collisin
 * @return true if the objects collide, false otherwise
 */
bool Rectangle::CollidesWith(Circle *other) {
  if (!HitsBox(other))
    return false;
}

/**
 * @param other the other circle to collide with
 * @return true if the objects collide
 */
bool Rectangle::CollidesWith(Rectangle *other) {
  if (!HitsBox(other))
    return false;
  return true;
}

#endif // RETCANGLE_CPP

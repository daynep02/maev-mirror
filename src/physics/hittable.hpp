/**
* @file hittable.hpp
* @author Dayne Pefley
* @brief the declarations of the hittable class
*
*/
#ifndef HITTABLE_HPP
#define HITTABLE_HPP
#include "System/Vector2.hpp"
#include "aabb.hpp"

class Circle;
class Rectangle;
class Hittable {
public:

  Hittable();

  Hittable(Aabb* boundingBox);

  virtual ~Hittable() = 0;

  virtual bool CollidesWith(Circle *other) = 0;
  virtual bool CollidesWith(Rectangle *other) = 0;
  bool HitsBox(Hittable* other);

  const Aabb* BoundingBox();

private:
  int numberOfVertices;
  sf::Vector2f* vertices;
  sf::Vector2f* edges;
  Aabb* bounding_box;
};

#endif // HITTABLE_HPP

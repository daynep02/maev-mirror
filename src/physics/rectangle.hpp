/**
 * @file Rectangle.cpp
 * @author Dayne Pefley
 * @brief defines the hittable circle
 */
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "hittable.hpp"
#include "aabb.hpp"

/**
 * @brief a collidable rectangle for the physics system
 */
class Rectangle : public Hittable {
public:
  /**
  * @brief creates a rectangle at 0,0, with size 0,0
  */
  Rectangle();


  /**
  * @param position the position at wich the rectangle is to be created
  * @param size the size of the created rectangle
  */
  Rectangle(const sf::Vector2f& position, const sf::Vector2f& size);

  /**
  * @brief destructor for this class, no cleanup needed
  */
  ~Rectangle() override;


  /**
  * @param other the other circle to be check for collisin
  * @return true if the objects collide, false otherwise
  */
  bool CollidesWith(Circle *other) override;

  /**
  * @param other the other rectangle to collide with
  * @return true if the objects collide
  */
  bool CollidesWith(Rectangle *other) override;

private:
  sf::RectangleShape shape;
  sf::Vector2f vertices[4];
  sf::Vector2f edges[4];

};
#endif // CIRCLE_CPP

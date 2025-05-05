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
  * @brief creates a circle at 0,0, with size 1
  */
  Rectangle();


  /**
  * @param position the position at wich the ball is to be created
  * @param radius the radius of the ball
  */
  Rectangle(const sf::Vector2f& position, float radius);

  /**
  * @brief destructor for this class, no cleanup needed
  */
  ~Rectangle() override;


  /**
  * @param other the other object to be check for collisin
  * @return true if the objects collide, false otherwise
  */
  bool CollidesWith(Hittable *other) override;

  /**
  * @param other the other circle to collide with
  * @return true if the objects collide
  */
  bool CollidesWith(Rectangle *other);

private:

  sf::RectangleShape shape;
  Aabb boundingBox;

};
#endif // CIRCLE_CPP

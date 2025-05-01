/**
* @file aabb.hpp
* @author Dayne Pefley
* @brief defines the Aabb class
*/

#ifndef AABB_HPP
#define AABB_HPP
#include "SFML/System/Vector2.hpp"
#include "hittable.hpp"

class Aabb: public Hittable {
  /**
  * @brief constnructs an aabb with nothing in it. It should not collide with anything.
  *
  */
  Aabb();

  /**
  * @brief constructs an Aabb from provided vectors
  * @param min the minimun (top left) point
  * @param max the maximum (bottom right) point
  */
  Aabb(const sf::Vector2f& min, const sf::Vector2f& max);

  /**
   * @brief base destructor for the class. No cleanup needed
   */
 ~Aabb();

  /**
  * @brief test if the object collides with another hittable object
  * @param other the other object
  */
  bool CollidesWith(Hittable *other) override;

  /**
  * @brief test if the object collides with another hittable object
  * @param other the other object
  */
  bool CollidesWith(Aabb *other);
  


private:

  sf::Vector2f min;
  sf::Vector2f max;
};
#endif // !AABB_HPP

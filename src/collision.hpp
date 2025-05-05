/**
 * @file collision.hpp
 * @author Dayne Pefley
 * @brief declares the collision class
 */

#ifndef COLLISION_H
#define COLLISION_H
#include "SFML/System/Vector2.hpp"
#include "rigid_body.h"

/**
 * @class collision
 * @brief a class storing collisions to be solved
 */
class Collision {
public:
  /**
   * @param a A Rigid Body to add to this collision object
   * @param b A Rigid Body to add to this collision object
   * @brief the ONLY constructor for this class
   */
  Collision(RigidBody *a, RigidBody *b);

  /**
   * @brief destructor for the class
   */
  ~Collision();

  /**
   * @brief the function for solving a collision between two bodies
   */
  void Solve();

private:
  /**
   * @brief solve collisions of objects knowing what is top and bottom
   * @param top_min the min value of the abject on top
   * @param top_max the max value of the abject on top
   * @param bot_min the min value of the abject on bottom
   * @param bot_max the max value of the abject on bottom
   */
  sf::Vector2f Solve(const sf::Vector2f &top_min, const sf::Vector2f &top_max,
                     const sf::Vector2f &bot_min,
                     const sf::Vector2f &bot_max) const;

  /**
   * @brief solve collisions of objects knowing one is static
   * @param static_min the min value of the object that is static
   * @param static_max the max value of the abject that is static
   * @param non_static_min the min value of the object that is non_static
   * @param non_static_max the max value of the object thas is non static
   */
  sf::Vector2f SolveStatic(const sf::Vector2f &static_min,
                           const sf::Vector2f &static_max,
                           const sf::Vector2f &non_static_min,
                           const sf::Vector2f &non_static_max) const;

  RigidBody *a;
  RigidBody *b;
};

#endif // COLLISION_H

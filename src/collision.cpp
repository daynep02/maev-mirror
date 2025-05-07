/**
 * @file collision.cpp
 * @author Dayne Pefley
 * @brief Definitions of member functions for the collision class
 */

#ifndef COLLISION_CPP
#define COLLISION_CPP
#include "collision.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "rigid_body.h"
#include <math.h>

Collision::Collision(RigidBody *a, RigidBody *b) : a(a), b(b) {}

Collision::~Collision() {}

void Collision::Solve() {
  sf::RectangleShape *box_a = a->GetBox()->getRect();
  sf::RectangleShape *box_b = b->GetBox()->getRect();

  sf::Vector2f a_min = box_a->getPosition();
  sf::Vector2f b_min = box_b->getPosition();
  sf::Vector2f a_max = box_a->getSize() + a_min;
  sf::Vector2f b_max = box_b->getSize() + b_min;


  sf::Vector2f force_to_apply; 

  if (a->IsStatic()) {
    b->ApplyForce(SolveStatic(a_min, a_max, b_min, b_max));
  }
  else if (b->IsStatic()) {
    a->ApplyForce(SolveStatic(b_min, b_max, a_min, a_max));
  }
  else if (a_max.y < b_min.y) {
    force_to_apply = Solve(a_min, a_max, b_min, b_max) * 0.5f;
    a->ApplyForce(force_to_apply);
    b->ApplyForce(-force_to_apply);
  }
  else {
    force_to_apply = Solve(b_min, b_max, a_min, a_max) * 0.5f;
    a->ApplyForce(-force_to_apply);
    b->ApplyForce(force_to_apply);
  }
}

sf::Vector2f Collision::Solve(const sf::Vector2f &top_min,
                              const sf::Vector2f &top_max,
                              const sf::Vector2f &bot_min,
                              const sf::Vector2f &bot_max) const {

  return sf::Vector2f(0.0, top_max.y - bot_min.y);
}


sf::Vector2f Collision::SolveStatic(const sf::Vector2f &static_min,
                         const sf::Vector2f &static_max,
                         const sf::Vector2f &non_static_min,
                         const sf::Vector2f &non_static_max) const {
  
  float d1x = static_min.x - non_static_max.x ;
  float d1y = static_min.y - non_static_max.y;
  float d2x = non_static_min.x - static_max.x ;
  float d2y = non_static_min.y - static_max.y;
  sf::Vector2f return_force;

  if (d1x <= 0.0f && d1y <= 0.0f){
    return {-d1x, -d1y};
  }
}

#endif // !COLLISION_CPP

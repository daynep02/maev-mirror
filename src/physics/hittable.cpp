/**
 * @file hittable.cpp
 * @author Dayne Pefley
 * @brief defines the functions for the hittable class
 */

#ifndef HITTABLE_CPP
#define HITTABLE_CPP
#include "hittable.hpp"
#include "aabb.hpp"

Hittable::Hittable() : bounding_box() {}

Hittable::Hittable(Aabb *bounding_box) : bounding_box(bounding_box) {}

bool Hittable::HitsBox(Hittable *other) {
  return bounding_box->CollidesWith(other->bounding_box);
}

#endif // !HITTABLE_CPP

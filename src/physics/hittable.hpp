/**
* @file hittable.hpp
* @author Dayne Pefley
* @brief the declarations of the hittable class
*
*/
#ifndef HITTABLE_HPP
#define HITTABLE_HPP

class Aabb;
class Hittable {
public:

  Hittable();

  Hittable(Aabb* boundingBox);

  virtual ~Hittable() = 0;

  virtual bool CollidesWith(Hittable *other) = 0;
  bool HitsBox(Hittable* other);

private:
  Aabb* bounding_box;
};

#endif // HITTABLE_HPP

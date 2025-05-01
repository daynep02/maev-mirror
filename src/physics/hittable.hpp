#ifndef HITTABLE_HPP
#define HITTABLE_HPP

class Hittable {
public:
  Hittable() = default;

  virtual ~Hittable() = 0;

  virtual bool CollidesWith(Hittable *other) = 0;
};

#endif // HITTABLE_HPP

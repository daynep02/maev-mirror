#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include "SFML/System/Vector2.hpp"
#include "box_collider.hpp"

class RigidBody {
public:
  RigidBody(sf::Vector2f new_position, sf::Vector2f new_size);
  RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static);
  RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static,
            bool gravity_);
  ~RigidBody();

  bool IsStatic() const;
  void SetStatic(bool new_static);
  bool IsGravity() const;
  void SetGravity(bool new_gravity);

  CollisionLayer GetCollisionLayer();
  void SetCollisionLayer(CollisionLayer new_layer);

  const sf::Vector2f &GetVelocity() const;
  void SetVelocity(float x, float y);
  void SetVelocity(const sf::Vector2f &new_velocity);
  void ModifyVelocity(float x, float y);
  void ModifyVelocity(const sf::Vector2f &new_velocity);
  void UpdateByVelocity(const sf::Vector2f &gravity, double delta);

  void ApplyForce(const sf::Vector2f &force);
  void ApplyGravity(const sf::Vector2f &gravity);

  sf::Vector2f GetPosition() const;
  void SetPosition(const sf::Vector2f &new_position);

  sf::Vector2f GetSize() const;
  void SetSize(const sf::Vector2f &new_size);

  void DrawOutline(sf::RenderWindow *window, sf::Color color) const;

  bool CollidesWith(RigidBody *other) const;
  bool CollidesWith(BoxCollider *other) const;

  void SetTerminalVelo(const sf::Vector2f &terminalVelo);

  void Collide(RigidBody *other, const sf::Vector2f &gravity, float delta);

  BoxCollider *GetBox() const;

  void ApplyAllForces();

  PyObject *GetCallback();
  void SetCallback(PyObject *new_callback);

  static void StaticCollide(RigidBody *moving, RigidBody *r_static, float delta,
                            const sf::Vector2f &gravity);
  static bool RayVRect(const sf::Vector2f &origin, const sf::Vector2f &dir,
                       const RigidBody *target, sf::Vector2f &point,
                       sf::Vector2f &normal, float &t_hit);
  static bool GetFaceCollisionNormal(const RigidBody *r1, const RigidBody *r2,
                                     sf::Vector2f &normal);

private:
  bool static_ = false;
  bool gravity = true;
  sf::Vector2f velocity = {0, 0};
  float terminalX = 100.f;
  float terminalY = 100.f;

  BoxCollider *box;
  PyObject *callback = NULL;

  sf::Vector2f terminalVelo = {0.0f, 100.0f};

  float weight = 1.0f;
  float frictionCoeff = 0.0f;
  sf::Vector2f previousPosition = {0.0f, 0.0f};

  std::vector<sf::Vector2f> forcesToApply;
};

#endif //_RIGID_BODY_H_

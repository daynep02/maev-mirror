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

  const sf::Vector2f& GetVelocity() const;
  void SetVelocity(float x, float y);
  void SetVelocity(const sf::Vector2f &new_velocity);
  void ModifyVelocity(float x, float y);
  void ModifyVelocity(const sf::Vector2f &new_velocity);
  void UpdateByVelocity(const sf::Vector2f &gravity, double delta);

  void ApplyForce(const sf::Vector2f &force);
  void ApplyGravity(const sf::Vector2f &gravity);

  sf::Vector2f GetPosition() const ;
  void SetPosition(const sf::Vector2f &new_position);

  sf::Vector2f GetSize() const;
  void SetSize(const sf::Vector2f &new_size);

  void DrawOutline(sf::RenderWindow *window, sf::Color color) const;

  bool CollidesWith(RigidBody *other) const;
  bool CollidesWith(BoxCollider *other) const;
  
  void SetTerminalVelo(const sf::Vector2f& terminalVelo);
  
  void Collide(RigidBody* other, const sf::Vector2f& gravity);


private:

  bool static_ = false;
  bool gravity = true;
  sf::Vector2f velocity = {0, 0};
  float terminalX = 100.f;
  float terminalY = 100.f;

  BoxCollider *box;

  sf::Vector2f terminalVelo = {0.0f, 100.0f};

  float weight = 1.0f;
  sf::Vector2f friction = {0.0f, 0.0f};
  sf::Vector2f previousPosition = {0.0f, 0.0f};


};

#endif //_RIGID_BODY_H_

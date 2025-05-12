/**
 * @file rigid_body.cpp
 * @brief definitions for the RigidBody class
 */
#include "rigid_body.h"
#include "SFML/System/Vector2.hpp"
#include "box_collider.hpp"
#include <SFML/System.hpp>
#include <iterator>
#include <stdexcept>

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size)
    : RigidBody(new_position, new_size, false, true) {}

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size,
                     bool new_static)
    : RigidBody(new_position, new_size, new_static, true) {}

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size,
                     bool new_static, bool gravity_)
    : static_(new_static), gravity(gravity_) {
  box = new BoxCollider();
  box->setPosition(new_position.x, new_position.y);
  box->setSize(new_size.x, new_size.y);
}

RigidBody::~RigidBody() { delete box; }

bool RigidBody::IsStatic() const { return static_; }

void RigidBody::SetStatic(bool new_static) { static_ = new_static; };

bool RigidBody::IsGravity() const { return gravity; }

void RigidBody::SetGravity(bool new_gravity) { gravity = new_gravity; }

const sf::Vector2f &RigidBody::GetVelocity() const { return velocity; }

void RigidBody::SetVelocity(float x, float y) { velocity = {x, y}; }

void RigidBody::SetVelocity(const sf::Vector2f &new_velocity) {
  velocity = new_velocity;
}

void RigidBody::ModifyVelocity(float x, float y) { ModifyVelocity({x, y}); }

void RigidBody::ModifyVelocity(const sf::Vector2f &new_velocity) {
  velocity += new_velocity;
}

void RigidBody::ApplyForce(const sf::Vector2f &force) { velocity += force; }

void RigidBody::ApplyGravity(const sf::Vector2f &gravity) {
  if (velocity.x < terminalX)
    ApplyForce({gravity.x, 0});
  if (velocity.y < terminalY)
    ApplyForce({0, gravity.y});

}

void RigidBody::UpdateByVelocity(const sf::Vector2f &gravity_, double delta) {
  previousPosition = box->getPosition();
  if (static_)
    return;
  previousPosition = box->getPosition();

  box->getRect()->move(velocity * (float)delta);
}

sf::Vector2f RigidBody::GetPosition() const { return box->getPosition(); }
void RigidBody::SetPosition(const sf::Vector2f &new_position) {
  box->setPosition(new_position.x, new_position.y);
}

sf::Vector2f RigidBody::GetSize() const { return box->getSize(); }
void RigidBody::SetSize(const sf::Vector2f &new_size) {
  box->setSize(new_size.x, new_size.y);
}

void RigidBody::DrawOutline(sf::RenderWindow *window, sf::Color color) const {
  sf::RectangleShape outline;
  outline.setPosition(GetPosition());
  outline.setSize(GetSize());
  outline.setFillColor(sf::Color::Transparent);
  outline.setOutlineColor(color);
  outline.setOutlineThickness(2);
  window->draw(outline);
}

bool RigidBody::CollidesWith(RigidBody *other) const {
  return box->CollidesWith(other->box);
}

bool RigidBody::CollidesWith(BoxCollider *other) const {
  return box->CollidesWith(other);
}

void RigidBody::SetTerminalVelo(const sf::Vector2f &terminalVelo) {
  terminalX = terminalVelo.x;
  terminalY = terminalVelo.y;
}

void RigidBody::Collide(RigidBody *other, const sf::Vector2f &gravity) {
  const sf::Vector2f &otherVelo = other->velocity;
  const sf::Vector2f &collisionVelo = -(velocity + otherVelo) * 0.5f;
  if (other->static_) {
    SetPosition(previousPosition);
    ApplyGravity(-gravity);
  }
  if (static_) {
    other->SetPosition(other->previousPosition);
    other->ApplyGravity(-gravity);
  }
  velocity += collisionVelo;
  other->velocity += collisionVelo;
}

BoxCollider *RigidBody::GetBox() const { return box; }

PyObject* RigidBody::GetCallback(){return callback;}
void RigidBody::SetCallback(PyObject* new_callback){callback = new_callback;}
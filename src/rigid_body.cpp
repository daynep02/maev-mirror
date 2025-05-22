/**
 * @file rigid_body.cpp
 * @brief definitions for the RigidBody class
 */
#include "rigid_body.h"
#include "SFML/System/Vector2.hpp"
#include "box_collider.hpp"
#include <SFML/System.hpp>
#include <cmath>
#include <iterator>

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

CollisionLayer RigidBody::GetCollisionLayer() { return box->GetCollisionLayer();}

void RigidBody::Free() {box->freed = true;}

void RigidBody::SetCollisionLayer(CollisionLayer new_layer) {box->SetCollisionLayer(new_layer);}

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

bool RigidBody::GetFaceCollisionNormal(const RigidBody* r1, const RigidBody *r2,
                                       sf::Vector2i &normal) {

  const auto &pos = r1->GetPosition();
  const auto &size = r1->GetSize();
  const auto &otherPos = r2->GetPosition();
  const auto &otherSize = r2->GetSize();
  // if (std::isnan(otherPos.x))
  // throw std::logic_error("Somehow you got nan!");

  const float dx = (pos.x + size.x / 2) - (otherPos.x + otherSize.x / 2);
  const float dy = (pos.y + size.y / 2) - (otherPos.y + otherSize.y / 2);
  const float w = (size.x + otherSize.x) / 2;
  const float h = (size.y + otherSize.y) / 2;

  const float crossW = w * dy;
  const float crossH = h * dx;

  if (std::abs(dx) <= w && std::abs(dy) <= h) {
    if (crossW > crossH) {
      normal = crossW > -crossH ? BoxCollider::bottomNormal
                                : BoxCollider::leftNormal;
    } else {
      normal =
          crossW > -crossH ? BoxCollider::rightNormal : BoxCollider::topNormal;
    }
    return true;
  }
  return false;
}

// The following code is sampled from OneLoneCoder and his rectangle engine,
// available here
// github.com/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_Rectangles.cpp

bool RigidBody::RayVRect(const sf::Vector2f &origin, const sf::Vector2f &dir,
                         const RigidBody *target, sf::Vector2f &point,
                         sf::Vector2f &normal, float &t_hit) {
  return false;
  /*
  point = {0.0, 0.0};
  normal = {0.0, 0.0};

  //sf::Vector2f invdir = sf::Vector2f{1.0f / dir.x, 1.0f / dir.y};
  sf::Vector2f invdir = -dir;

  if (dir.x == 0 && dir.y == 0)
    return false;
  else if (dir.x == 0)
    invdir = {dir.x, 1.0f / dir.y};
  else if (dir.y == 0)
    invdir = {1.0f / dir.x, dir.y};
  else
    invdir = sf::Vector2f{1.0f, 1.0f}.componentWiseDiv(dir);

  auto t_near = (target->GetPosition() - origin).componentWiseMul(invdir);
  auto t_far = (target->GetPosition() + target->GetSize() - origin)
                   .componentWiseMul(invdir);

  if (std::isnan(t_far.y) || std::isnan(t_far.x))
    return false;
  if (std::isnan(t_near.y) || std::isnan(t_near.y))
    return false;

  if (t_near.x > t_far.x)
    std::swap(t_near.x, t_far.x);
  if (t_near.y > t_far.y)
    std::swap(t_near.y, t_far.y);

  if (t_near.x > t_far.y || t_near.y > t_far.x)
    return false;

  t_near.x = std::abs(t_near.x);
  t_near.y = std::abs(t_near.y);
  printf("t_near = (%f, %f)\n", t_near.x, t_near.y);

  t_hit = std::max(t_near.x, t_near.y);

  float t_hit_far = std::min(t_far.x, t_far.y);

  if (t_hit_far < 0)
    return false;

  point = origin + t_hit * dir;

  if (t_near.x > t_near.y) {

    if (invdir.x < 0) {
      normal = {1, 0};
    } else {
      normal = {-1, 0};
    }
  } else if (t_near.x < t_near.y) {
    if (invdir.y < 0)
      normal = {0, 1};
    else
      normal = {0, -1};
  }
  return true;
  */
}

void RigidBody::Collide(RigidBody *other, const sf::Vector2f &gravity,
                        float delta) {

  // special thanks to this article
  // https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
  const sf::Vector2f &otherVelo = other->velocity;
  const sf::Vector2f &collisionVelo = -(velocity + otherVelo) * 0.5f;

  if (other->static_) {

    StaticCollide(this, other, delta, gravity);
    return;
  }
  if (static_) {
    StaticCollide(other, this, delta, gravity);
    return;
  }

  sf::Vector2i normal = {0,0};
  if (!GetFaceCollisionNormal(this, other, normal)) return;
  if (normal.y != 0) {
    this->SetPosition({this->GetPosition().x, this->previousPosition.y});
    other->SetPosition({other->GetPosition().x, other->previousPosition.y});
  }

  if (normal.x != 0) {
    this->SetPosition({this->previousPosition.x, this->GetPosition().y});
    other->SetPosition({other->previousPosition.x, other->GetPosition().y});
  }
  return;


}

void RigidBody::StaticCollide(RigidBody *moving, RigidBody *r_static,
                              float delta, const sf::Vector2f& gravity) {
  sf::Vector2i normal = {0,0};
  if (!GetFaceCollisionNormal(moving, r_static, normal)) return;
  // Checking vertical
  if (normal.y == 1) {
    moving->SetPosition({moving->GetPosition().x, r_static->GetPosition().y+r_static->GetSize().y});
  } else if (normal.y == -1) {
    moving->SetPosition({moving->GetPosition().x, r_static->GetPosition().y-moving->GetSize().y});
  }
  // Checking horizontal
  if (normal.x == 1) {
    moving->SetPosition({r_static->GetPosition().x+r_static->GetSize().x, moving->GetPosition().y});
  } else if (normal.x == -1) {
    moving->SetPosition({r_static->GetPosition().x-moving->GetSize().x, moving->GetPosition().y});
  }
  return;

  // Below code is NOT utilized
  /*
  sf::Vector2f point = {0, 0};
  if (moving->velocity.x == 0 && moving->velocity.y == 0)
    return;
  sf::Vector2f r = moving->GetPosition() + moving->GetSize() / 2.0f;
  float time = 0.0f;
  RigidBody temp(r_static->GetPosition() - moving->GetSize() / 2.0f,
                 r_static->GetSize() + moving->GetSize());
  temp.static_ = true;

  if (!RayVRect(moving->GetPosition() + moving->GetSize() * 0.5f,
                moving->GetVelocity().normalized() * delta , r_static, point, normal, time)) {

    return;
  }
  if (time < 0.0f || time >= 1.0f)
    return;
  normal += normal.componentWiseMul(gravity);
  auto force = (1 - delta) * normal.componentWiseMul(sf::Vector2f{
                                         std::abs(moving->velocity.x),
                                         std::abs(moving->velocity.y)});
  printf("force = (%f, %f)\n", force.x, force.y);
  moving->ApplyForce(force);
  */
}

BoxCollider *RigidBody::GetBox() const { return box; }

PyObject *RigidBody::GetCallback() { return callback; }
void RigidBody::SetCallback(PyObject *new_callback) { callback = new_callback; }

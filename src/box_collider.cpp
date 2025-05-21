#include "box_collider.hpp"

BoxCollider::BoxCollider() : BoxCollider({0, 0}, {10, 10}) {}

BoxCollider::BoxCollider(const sf::Vector2f &position,
                         const sf::Vector2f &size) {
  box = new sf::RectangleShape(size);
  box->setPosition(position);

  box->setFillColor(sf::Color::Transparent);
  box->setOutlineColor(sf::Color::Blue);
  box->setOutlineThickness(2);
}

BoxCollider::~BoxCollider() { delete box; }

sf::RectangleShape *BoxCollider::getRect() { return box; }

sf::Vector2f BoxCollider::getPosition() { return box->getPosition(); }

void BoxCollider::setPosition(float x, float y) { box->setPosition({x, y}); }

sf::Vector2f BoxCollider::getSize() { return box->getSize(); }

void BoxCollider::setSize(float w, float h) { box->setSize({w, h}); }

void BoxCollider::Draw(sf::RenderWindow* window) {
  if (isTrigger) {box->setOutlineColor(sf::Color::Blue);}
  else {box->setOutlineColor(sf::Color::Red);}
  window->draw(*box);
}

PyObject* BoxCollider::GetCallback() {return callback;}
void BoxCollider::SetCallback(PyObject *new_callback) { callback = new_callback; }

CollisionLayer BoxCollider::GetCollisionLayer() {return layer;}
void BoxCollider::SetCollisionLayer(CollisionLayer new_layer) {layer = new_layer;}

bool BoxCollider::CollidesWith(BoxCollider *other) {
  if (!GetLayerAt(layer,other->GetCollisionLayer())) {
    return false;
  }
  if (freed || other->freed) {
    return false;
  }

  sf::RectangleShape *other_box = other->getRect();
  sf::Vector2f pos1 = box->getPosition();
  sf::Vector2f pos2 = other_box->getPosition();
  sf::Vector2f size1 = box->getSize();
  sf::Vector2f size2 = other_box->getSize();

  float d1x = pos1.x - pos2.x - size2.x;
  float d1y = pos1.y - pos2.y - size2.y;
  float d2x = pos2.x - pos1.x - size1.x;
  float d2y = pos2.y - pos1.y - size1.y;

  if (d1x > 0.0f || d1y > 0.0f)
    return false;

  if (d2x > 0.0f || d2y > 0.0f)
    return false;

  return true;
}

const sf::Vector2i BoxCollider::topNormal = {0, -1};
const sf::Vector2i BoxCollider::bottomNormal = {0, 1};
const sf::Vector2i BoxCollider::leftNormal = {-1, 0};
const sf::Vector2i BoxCollider::rightNormal = {1, 0};

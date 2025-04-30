#include "box_collider.hpp"

BoxCollider::BoxCollider() 
  : BoxCollider({0,0}, {10, 10}) {
}

BoxCollider::BoxCollider(const sf::Vector2f &position, const sf::Vector2f &size) {
    box = new sf::RectangleShape(size);
    box->setPosition(position);
    box->setFillColor(sf::Color::Red);
}

BoxCollider::~BoxCollider() {
    delete box;
}

sf::RectangleShape* BoxCollider::getRect() {
    return box;
}

sf::Vector2f BoxCollider::getPosition() {return box->getPosition();}

void BoxCollider::setPosition(float x, float y){
    box->setPosition({x,y});
}

sf::Vector2f BoxCollider::getSize() {return box->getSize();}

void BoxCollider::setSize(float w, float h){
    box->setSize({w,h});
}

bool BoxCollider::CollidesWith(BoxCollider* other) {
    sf::RectangleShape* other_box = other->getRect();
    sf::Vector2f pos1 = box->getPosition();
    sf::Vector2f pos2 = other_box->getPosition();
    sf::Vector2f size1 = box->getSize();
    sf::Vector2f size2 = other_box->getSize();

    return (
        pos1.x <= pos2.x + size2.x && 
        pos1.x + size1.x >= pos2.x &&
        pos1.y <= pos2.y + size2.y &&
        pos1.y + size1.y >= pos2.y
    );
}


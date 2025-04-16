#include "box_collider.hpp"

BoxCollider::BoxCollider() {
    box = sf::RectangleShape(sf::Vector2f(0, 0));
    box.setPosition(sf::Vector2f(0, 0));
}

BoxCollider::BoxCollider(sf::Vector2f position, sf::Vector2f size) {
    box = sf::RectangleShape(size);
    box.setPosition(position);
    box.setFillColor(sf::Color::White);
}

BoxCollider::~BoxCollider() {

}

sf::RectangleShape& BoxCollider::getRect() {
    return box;
}

bool BoxCollider::CollidesWith(BoxCollider* other) {
    sf::RectangleShape& other_box = other->getRect();
    sf::Vector2f pos1 = box.getPosition();
    sf::Vector2f pos2 = other_box.getPosition();
    sf::Vector2f size1 = box.getSize();
    sf::Vector2f size2 = other_box.getSize();

    return (
        box.
    );
}


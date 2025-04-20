#ifndef _BOX_COLLIDER_HPP_
#define _BOX_COLLIDER_HPP_

#include <Python.h>
#include <SFML/Graphics.hpp>
#include <vector>

class BoxCollider {
    public:
        BoxCollider();
        BoxCollider(sf::Vector2f position, sf::Vector2f size);
        ~BoxCollider();

        bool CollidesWith(BoxCollider* other);
        sf::RectangleShape* getRect();
        sf::Vector2f getPosition();
        void setPosition(float x, float y);
        sf::Vector2f getSize();
        void setSize(float w, float h);

    private:
        sf::RectangleShape* box;
};

#endif
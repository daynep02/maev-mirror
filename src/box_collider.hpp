#ifndef _BOX_COLLIDER_HPP_
#define _BOX_COLLIDER_HPP_

#include <Python.h>
#include <SFML/Graphics.hpp>

class BoxCollider {
    public:
        BoxCollider();
        BoxCollider(const sf::Vector2f &position, const sf::Vector2f &size);
        ~BoxCollider();

        bool CollidesWith(BoxCollider* other);
        sf::RectangleShape* getRect();
        sf::Vector2f getPosition();
        void setPosition(float x, float y);
        sf::Vector2f getSize();
        void setSize(float w, float h);
        static const sf::Vector2f topNormal, bottomNormal, leftNormal, rightNormal;

    private:
        sf::RectangleShape* box;
};

#endif

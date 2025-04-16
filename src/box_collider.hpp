#ifndef _BOX_COLLIDER_HPP_
#define _BOX_COLLIDER_HPP_

#include <Python.h>
#include <SFML/Graphics.hpp>

class BoxCollider {
    public:
        BoxCollider();
        BoxCollider(sf::Vector2f position, sf::Vector2f size);
        ~BoxCollider();

        bool CollidesWith(BoxCollider* other);
        sf::RectangleShape* getRect();

    private:
        sf::RectangleShape* box;
        long id;
};

#endif
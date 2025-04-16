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

    private:
        static std::vector<BoxCollider*> 
        sf::RectangleShape* box;
};

#endif
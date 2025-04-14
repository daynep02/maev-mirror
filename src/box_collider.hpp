#ifndef _BOX_COLLIDER_HPP_
#define _BOX_COLLIDER_HPP_

#include <Python.h>
#include <SFML/Graphics.hpp>

class BoxCollider {
    public:
        BoxCollider();
        ~BoxCollider();

        bool CollidesWith(BoxCollider* other);

    private:
        sf::RectangleShape box;
        long id;
};

#endif
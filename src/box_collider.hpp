#ifndef _BOX_COLLIDER_HPP_
#define _BOX_COLLIDER_HPP_

#include <Python.h>
#include <SFML/Graphics.hpp>

#include "collision_layers.h"

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

        void Draw(sf::RenderWindow* window);

        CollisionLayer GetCollisionLayer();
        void SetCollisionLayer(CollisionLayer new_layer);

        PyObject* GetCallback();
        void SetCallback(PyObject *new_callback);

        static const sf::Vector2i topNormal, bottomNormal, leftNormal, rightNormal;

        bool isTrigger = true;
        bool freed = false;

    private:
        CollisionLayer layer = DEFAULT;

        PyObject* callback = NULL;
        sf::RectangleShape* box;
};

#endif

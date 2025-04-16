#ifndef _BOX_COLLIDER_HANDLER_HPP_
#define _BOX_COLLIDER_HANDLER_HPP_

#include <Python.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "box_collider.hpp"

class BoxColliderHandler {
    private:
        sf::RenderWindow* _window;
        std::vector<BoxCollider*> box_colliders;

    public:
        BoxColliderHandler(sf::RenderWindow* window);
        ~BoxColliderHandler();

        static PyObject* createBoxCollider(PyObject* self, PyObject* args);
        static PyObject* freeBoxCollider(PyObject* self, PyObject* args);

};

#endif
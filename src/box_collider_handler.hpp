#ifndef _BOX_COLLIDER_HANDLER_HPP_
#define _BOX_COLLIDER_HANDLER_HPP_

#include <Python.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "box_collider.hpp"
#include "common_helpers.h"

class BoxColliderHandler {
    private:
        // static sf::RenderWindow* _window;
        // static std::vector<BoxCollider*> box_colliders;
        // static std::vector<long> free_box_colliders;

    public:
        BoxColliderHandler(sf::RenderWindow* window);
        ~BoxColliderHandler();

        static PyObject* createBoxCollider(PyObject* self, PyObject* args);
        static PyObject* freeBoxCollider(PyObject* self, PyObject* args);

};

PyDoc_STRVAR(
    engine_create_box_collider_doc,
    ".. function:: create_box_collider(tuple (x y), tuple (width, height))\n"
    "\n"
    ""
    "\n"
    ":return: an integer representing the box colliders id"
);

PyDoc_STRVAR(
    engine_free_box_collider_doc,
    ".. function:: free_box_collider(long id)\n"
    "\n"
    ""
    "\n"
    ":return: none"
);

#endif
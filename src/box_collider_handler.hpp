#ifndef _BOX_COLLIDER_HANDLER_HPP_
#define _BOX_COLLIDER_HANDLER_HPP_

#include <Python.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "box_collider.hpp"
#include "common_helpers.h"

class BoxColliderHandler {
    public:
        BoxColliderHandler(sf::RenderWindow* window);
        ~BoxColliderHandler();

        static std::vector<BoxCollider*>* GetBoxVector();

        static PyObject* createBoxCollider(PyObject* self, PyObject* args);
        static PyObject* freeBoxCollider(PyObject* self, PyObject* args);

        static PyObject* GetBoxPosition(PyObject* self, PyObject* args);
        static PyObject* SetBoxPosition(PyObject* self, PyObject* args);

        static PyObject* GetBoxSize(PyObject* self, PyObject* args);
        static PyObject* SetBoxSize(PyObject* self, PyObject* args);

        static PyObject* GetBoxTrigger(PyObject* self, PyObject* args);
        static PyObject* SetBoxTrigger(PyObject* self, PyObject* args);

        static PyObject *GetBoxLayer(PyObject *self, PyObject *args);
        static PyObject *SetBoxLayer(PyObject *self, PyObject *args);

        static PyObject* SetBoxCallback(PyObject* self, PyObject* args);
        static PyObject* DrawBox(PyObject* self, PyObject* args);

        static bool isBoxColliderIDInRange(long id);
        static BoxCollider* getBoxCollider(long id);
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

// corresponding documentation for engine_get_box_position
PyDoc_STRVAR(engine_get_box_position_doc,
             ".. function:: get_box_position(id)\n"
             "\n"
             "  Gets the position of the a box collider with the specified id.\n"
             "\n"
             "  :return: A tuple of floats (x,y).\n");

// corresponding documentation for engine_set_box_position
PyDoc_STRVAR(engine_set_box_position_doc,
             ".. function:: set_box_position(id,(x,y))\n"
             "\n"
             "  Sets the position of the a box collider with the specified id to "
             "the new x and y.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_box_size
PyDoc_STRVAR(engine_get_box_size_doc,
             ".. function:: get_box_size(id)\n"
             "\n"
             "  Gets the size of the a box collider with the specified id.\n"
             "\n"
             "  :return: A tuple of floats (width,height).\n");

// corresponding documentation for engine_set_box_size
PyDoc_STRVAR(engine_set_box_size_doc,
             ".. function:: set_box_size(id,(width,height))\n"
             "\n"
             "  Sets the size of the a box collider with the specified id to the "
             "new width and height.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_get_box_trigger
PyDoc_STRVAR(engine_get_box_trigger_doc,
             ".. function:: get_box_trigger(id)\n"
             "\n"
             "  Checks if the box collider with the specified id is active.\n"
             "\n"
             "  :return: A boolean.\n");

// corresponding documentation for engine_set_box_trigger
PyDoc_STRVAR(engine_set_box_trigger_doc,
             ".. function:: set_box_trigger(id, bool)\n"
             "\n"
             "  Sets the box collider to be active (trigger) or not with the specified "
             "id the passed bool.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_get_box_layer
PyDoc_STRVAR(engine_get_box_layer_doc,
             ".. function:: get_box_layer(id)\n"
             "\n"
             "  Gets and returns the box collider's collision layer.\n"
             "\n"
             "  :return: A long.\n");

// corresponding documentation for engine_set_box_layer
PyDoc_STRVAR(engine_set_box_layer_doc,
             ".. function:: set_box_layer(id, layer)\n"
             "\n"
             "  Sets the box collider to be on the provided collision layer"
             "  , a long in the range 0-7 inclusive.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_box_callback
PyDoc_STRVAR(engine_set_box_callback_doc,
             ".. function:: set_box_callback(id, callback)\n"
             "\n"
             "  Sets a function callback to be called upon the specified box"
             "  colliding with a box collider.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_draw_box
PyDoc_STRVAR(engine_draw_box_doc,
             ".. function:: draw_box(id)\n"
             "\n"
             "  Given an id of a box collider, draw a red box outline of "
             "the box collider\n"
             "\n"
             "  :return: Nothing.\n");

#endif
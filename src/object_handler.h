#ifndef _OBJECT_HANDLER_H_
#define _OBJECT_HANDLER_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

#include "common_helpers.h"

#define MAX_FILENAME_LEN 1024

//// CLASS DEF ////

class ObjectHandler {
    public:
    ObjectHandler(sf::RenderWindow* window);
    ~ObjectHandler();

    // Creates a Sprite object from a given filename, stores it in the sprites vector, and returns it's id (i.e. vector index)
    static PyObject* CreateSprite(PyObject *self, PyObject *args);
    static PyObject* SetSpritePosition(PyObject *self, PyObject *args);
    static PyObject* SetSpriteScale(PyObject *self, PyObject *args);
    // Draws the Sprite with the given vector index
    static PyObject* DrawSprite(PyObject *self, PyObject *args);
    // Frees the Sprite with the given vector index, allowing the memory to be re-used
    static PyObject* FreeSprite(PyObject *self, PyObject *args);

    static PyObject* CreateCircle(PyObject *self, PyObject *args);
    static PyObject* SetCircleFillColor(PyObject *self, PyObject *args);
    static PyObject* SetCirclePosition(PyObject *self, PyObject *args);
    static PyObject* SetCircleScale(PyObject *self, PyObject *args);
    static PyObject* DrawCircle(PyObject *self, PyObject *args);

	///// Physics Engine /////
	static PyObject* CollidesWith(PyObject *self, PyObject *args);
    
    private:
};

//// PYTHON DOCS ////

// corresponding documentation for engine_create_sprite
PyDoc_STRVAR(
	engine_create_sprite_doc,
	".. function:: create_sprite(filename)\n"
	"\n"
	"  Creates a sprite from the given file name.\n"
	"\n"
	"  :return: an integer representing the sprite's id.\n");

// corresponding documentation for set_sprite_position
PyDoc_STRVAR(
	engine_set_sprite_position_doc,
	".. function:: set_sprite_position(id, (x, y))\n"
	"\n"
	"  Sets the position of the sprite with the given id at the x and y provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_sprite_scale
PyDoc_STRVAR(
	engine_set_sprite_scale_doc,
	".. function:: set_sprite_scale(id, (x, y))\n"
	"\n"
	"  Sets the scale of the sprite with the given id at the x and y provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_draw_sprite
PyDoc_STRVAR(
	engine_draw_sprite_doc,
	".. function:: draw_sprite(id)\n"
	"\n"
	"  Draws the sprite with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_draw_sprite
PyDoc_STRVAR(
	engine_free_sprite_doc,
	".. function:: free_sprite(id)\n"
	"\n"
	"  Frees the sprite with the given id, allowing the id to be initialized to something else when calling create_sprite\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_create_circle
PyDoc_STRVAR(
	engine_create_circle_doc,
	".. function:: create_circle(radius)\n"
	"\n"
	"  Creates a circle with the given radius and returns its id.\n"
	"\n"
	"  :return: an integer representing the circle's id.\n");

// corresponding documentation for set_circle_fill_color
PyDoc_STRVAR(
	engine_set_circle_fill_color_doc,
	".. function:: set_circle_fill_color(id, (r,g,b,a))\n"
	"\n"
	"  Sets the fill color of the circle with the given id with the RGBA value in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_circle_position
PyDoc_STRVAR(
	engine_set_circle_position_doc,
	".. function:: set_circle_position(id, (x, y))\n"
	"\n"
	"  Sets the position of the circle with the given id at the x and y provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_circle_scale
PyDoc_STRVAR(
	engine_set_circle_scale_doc,
	".. function:: set_circle_scale(id, (x, y))\n"
	"\n"
	"  Sets the scale of the circle with the given id at the x and y provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_draw_circle
PyDoc_STRVAR(
	engine_draw_circle_doc,
	".. function:: draw_circle(id)\n"
	"\n"
	"  Draws the circle with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

PyDoc_STRVAR(
	engine_collides_with_doc,
	".. function:: collides_with(id1, id2)\n"
	"\n"
	"  Tests whether two shapes collide or not.\n"
	"\n"
	"  :return: bool of whether the two shapes collided.\n");

#endif //_OBJECT_HANDLER_H_
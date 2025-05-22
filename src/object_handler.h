#ifndef _OBJECT_HANDLER_H_
#define _OBJECT_HANDLER_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

#include "common_helpers.h"

#define MAX_FILENAME_LEN 1024

//// CLASS DEF ////

class ObjectHandler {
public:
  ObjectHandler(sf::RenderWindow *window);
  ~ObjectHandler();

  // Creates a Sprite object from a given filename, stores it in the sprites
  // vector, and returns it's id (i.e. vector index)
  static PyObject *CreateSprite(PyObject *self, PyObject *args);
  static PyObject *SetSpritePosition(PyObject *self, PyObject *args);
  static PyObject *SetSpriteScale(PyObject *self, PyObject *args);
  static PyObject *GetSpriteRotation(PyObject *self, PyObject *args);
  static PyObject *SetSpriteRotation(PyObject *self, PyObject *args);
  static PyObject *SpriteRotate(PyObject *self, PyObject *args);
  static PyObject *GetSpriteSize(PyObject *self, PyObject *args);
  // Draws the Sprite with the given vector index
  static PyObject *DrawSprite(PyObject *self, PyObject *args);
  // Frees the Sprite with the given vector index, allowing the memory to be
  // re-used
  static PyObject *FreeSprite(PyObject *self, PyObject *args);

  static PyObject *CreateCircle(PyObject *self, PyObject *args);
  static PyObject *SetCircleFillColor(PyObject *self, PyObject *args);
  static PyObject *SetCirclePosition(PyObject *self, PyObject *args);
  static PyObject *SetCircleScale(PyObject *self, PyObject *args);
  static PyObject *SetCircleRadius(PyObject *self, PyObject *args);
  static PyObject *SetCircleOutlineThickness(PyObject *self, PyObject *args);
  static PyObject *SetCircleOutlineColor(PyObject *self, PyObject *args);
  static PyObject *DrawCircle(PyObject *self, PyObject *args);
  static PyObject *FreeCircle(PyObject *self, PyObject *args);

  static PyObject *CreateRect(PyObject *self, PyObject *args);
  static PyObject *SetRectFillColor(PyObject *self, PyObject *args);
  static PyObject *SetRectPosition(PyObject *self, PyObject *args);
  static PyObject *SetRectScale(PyObject *self, PyObject *args);
  static PyObject *GetRectRotation(PyObject *self, PyObject *args);
  static PyObject *SetRectRotation(PyObject *self, PyObject *args);
  static PyObject *RectRotate(PyObject *self, PyObject *args);
  static PyObject *SetRectSize(PyObject *self, PyObject *args);
  static PyObject *SetRectOutlineThickness(PyObject *self, PyObject *args);
  static PyObject *SetRectOutlineColor(PyObject *self, PyObject *args);
  static PyObject *DrawRect(PyObject *self, PyObject *args);

  ///// Physics Engine /////
  static PyObject *CollidesWith(PyObject *self, PyObject *args);

private:
};

//// PYTHON DOCS ////

// corresponding documentation for engine_create_sprite
PyDoc_STRVAR(engine_create_sprite_doc,
             ".. function:: create_sprite(filename)\n"
             "\n"
             "  Creates a sprite from the given file name.\n"
             "\n"
             "  :return: an integer representing the sprite's id.\n");

// corresponding documentation for set_sprite_position
PyDoc_STRVAR(engine_set_sprite_position_doc,
             ".. function:: set_sprite_position(id, (x, y))\n"
             "\n"
             "  Sets the position of the sprite with the given id at the x and "
             "y provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_sprite_scale
PyDoc_STRVAR(engine_set_sprite_scale_doc,
             ".. function:: set_sprite_scale(id, (x, y))\n"
             "\n"
             "  Sets the scale of the sprite with the given id at the x and y "
             "provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_get_sprite_rotation_doc,
    ".. function:: get_sprite_rotation(id)\n"
    "\n"
    "  Gets the rotation of the sprite with the given id\n"
    "\n"
    "  :return: a float representing the angle in degrees.\n");

PyDoc_STRVAR(engine_set_sprite_rotation_doc,
    ".. function:: set_sprite_rotation(id, angle)\n"
    "\n"
    "  Sets the rotation of the sprite with the given id at the angle in degrees\n"
    "\n"
    "  :return: Nothing.\n");

PyDoc_STRVAR(engine_sprite_rotate_doc,
        ".. function:: sprite_rotate(id, angle)\n"
        "\n"
        "  Sets the rotation of the sprite with the given id by the angle in degrees, relative to its current angle\n"
        "\n"
        "  :return: Nothing.\n");

PyDoc_STRVAR(engine_get_sprite_size_doc,
            ".. function:: get_sprite_size(id1)\n"
            "\n"
            "  Gets the size of a sprite.\n"
            "\n"
            "  :return: a tuple containing the x and "
            "y values of the size of a sprite.\n");

// corresponding documentation for engine_draw_sprite
PyDoc_STRVAR(engine_draw_sprite_doc, ".. function:: draw_sprite(id)\n"
                                     "\n"
                                     "  Draws the sprite with the given id.\n"
                                     "\n"
                                     "  :return: Nothing.\n");

// corresponding documentation for engine_free_sprite
PyDoc_STRVAR(engine_free_sprite_doc,
             ".. function:: free_sprite(id)\n"
             "\n"
             "  Frees the sprite with the given id, allowing the id to be "
             "initialized to something else when calling create_sprite\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_create_circle
PyDoc_STRVAR(engine_create_circle_doc,
             ".. function:: create_circle(radius)\n"
             "\n"
             "  Creates a circle with the given radius and returns its id.\n"
             "\n"
             "  :return: an integer representing the circle's id.\n");

// corresponding documentation for set_circle_fill_color
PyDoc_STRVAR(engine_set_circle_fill_color_doc,
             ".. function:: set_circle_fill_color(id, (r,g,b,a))\n"
             "\n"
             "  Sets the fill color of the circle with the given id with the "
             "RGBA value in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_circle_position
PyDoc_STRVAR(engine_set_circle_position_doc,
             ".. function:: set_circle_position(id, (x, y))\n"
             "\n"
             "  Sets the position of the circle with the given id at the x and "
             "y provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_circle_scale
PyDoc_STRVAR(engine_set_circle_scale_doc,
             ".. function:: set_circle_scale(id, (x, y))\n"
             "\n"
             "  Sets the scale of the circle with the given id at the x and y "
             "provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_draw_circle
PyDoc_STRVAR(engine_draw_circle_doc, ".. function:: draw_circle(id)\n"
                                     "\n"
                                     "  Draws the circle with the given id.\n"
                                     "\n"
                                     "  :return: Nothing.\n");

// corresponding documentation for engine_free_circle
PyDoc_STRVAR(engine_free_circle_doc,
             ".. function:: free_circle(id)\n"
             "\n"
             "  Frees the circle with the given id, allowing the id to be "
             "initialized to something else when calling create_circle\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_collides_with_doc,
             ".. function:: collides_with(id1, id2)\n"
             "\n"
             "  Tests whether two shapes collide or not.\n"
             "\n"
             "  :return: bool of whether the two shapes collided.\n");

// corresponding documentation for engine_create_rect
PyDoc_STRVAR(
    engine_create_rect_doc,
    ".. function:: create_rect( (w,h) )\n"
    "\n"
    "  Creates a rect with the given width and height and returns its id.\n"
    "\n"
    "  :return: an integer representing the rect's id.\n");

// corresponding documentation for set_rect_fill_color
PyDoc_STRVAR(engine_set_rect_fill_color_doc,
             ".. function:: set_rect_fill_color(id, (r,g,b,a))\n"
             "\n"
             "  Sets the fill color of the rect with the given id with the "
             "RGBA value in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_rect_position
PyDoc_STRVAR(engine_set_rect_position_doc,
             ".. function:: set_rect_position(id, (x, y))\n"
             "\n"
             "  Sets the position of the rect with the given id at the x and y "
             "provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_rect_scale
PyDoc_STRVAR(engine_set_rect_scale_doc,
             ".. function:: set_rect_scale(id, (x, y))\n"
             "\n"
             "  Sets the scale of the rect with the given id at the x and y "
             "provided in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_get_rect_rotation_doc,
    ".. function:: get_rect_rotation(id)\n"
    "\n"
    "  Gets the rotation of the rect with the given id\n"
    "\n"
    "  :return: a float representing the angle in degrees.\n");

PyDoc_STRVAR(engine_set_rect_rotation_doc,
    ".. function:: set_rect_rotation(id, angle)\n"
    "\n"
    "  Sets the rotation of the rect with the given id at the angle in degrees\n"
    "\n"
    "  :return: Nothing.\n");

PyDoc_STRVAR(engine_rect_rotate_doc,
    ".. function:: rect_rotate(id, angle)\n"
    "\n"
    "  Sets the rotation of the rect with the given id by the angle in degrees, relative to its current angle\n"
    "\n"
    "  :return: Nothing.\n");

// corresponding documentation for set_rect_size
PyDoc_STRVAR(engine_set_rect_size_doc,
             ".. function:: set_rect_radius(id, (w,h))\n"
             "\n"
             "  Sets the size of the rect with the given id with the provided "
             "width and height (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for set_rect_outline_thickness
PyDoc_STRVAR(
    engine_set_rect_outline_thickness_doc,
    ".. function:: set_rect_outline_thickness(id, thickness)\n"
    "\n"
    "  Sets the outline thickness in pixels of the rect with the given id\n"
    "\n"
    "  :return: Nothing.\n");

// corresponding documentation for set_rect_outline_color
PyDoc_STRVAR(engine_set_rect_outline_color_doc,
             ".. function:: set_rect_outline_color(id, (r,g,b,a))\n"
             "\n"
             "  Sets the outline color of the rect with the given id with the "
             "RGBA value in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_draw_rect
PyDoc_STRVAR(engine_draw_rect_doc, ".. function:: draw_rect(id)\n"
                                   "\n"
                                   "  Draws the rect with the given id.\n"
                                   "\n"
                                   "  :return: Nothing.\n");

// corresponding documentation for set_circle_radius
PyDoc_STRVAR(engine_set_circle_radius_doc,
             ".. function:: set_circle_radius(id, radius)\n"
             "\n"
             "  Sets the radius of the circle with the given id with the "
             "provided float (second arg)\n"
             "\n"
             "  :return: Nothing.\n");
// corresponding documentation for set_circle_outline_thickness
PyDoc_STRVAR(
    engine_set_circle_outline_thickness_doc,
    ".. function:: set_circle_outline_thickness(id, thickness)\n"
    "\n"
    "  Sets the outline thickness in pixels of the circle with the given id\n"
    "\n"
    "  :return: Nothing.\n");

// corresponding documentation for set_circle_outline_color
PyDoc_STRVAR(engine_set_circle_outline_color_doc,
             ".. function:: set_circle_outline_color(id, (r,g,b,a))\n"
             "\n"
             "  Sets the outline color of the circle with the given id with "
             "the RGBA value in the tuple (second arg)\n"
             "\n"
             "  :return: Nothing.\n");




static PyMethodDef Get_Sprite_size = {"get_sprite_size",
                                     ObjectHandler::GetSpriteSize, METH_VARARGS,
                                     engine_get_sprite_size_doc};
#endif //_OBJECT_HANDLER_H_

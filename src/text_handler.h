#ifndef _TEXT_HANDLER_H_
#define _TEXT_HANDLER_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

#include "common_helpers.h"

#define MAX_FILENAME_LEN 1024

//// CLASS DEF ////

class TextHandler {
    public:
    TextHandler(sf::RenderWindow* window);
    ~TextHandler();

    // Creates a sf::Font object from a given filename, stores it in the fonts vector, and returns it's id (i.e. vector index)
    static PyObject* CreateFont(PyObject *self, PyObject *args);
	// Creates a sf::Text object from a given Font id, stores it in the texts vector, and returns it's id (i.e. vector index)
	static PyObject* CreateText(PyObject *self, PyObject *args);
    static PyObject* SetTextPosition(PyObject *self, PyObject *args);
	static PyObject* SetTextSize(PyObject *self, PyObject *args);
	static PyObject* SetTextColor(PyObject *self, PyObject *args);
    static PyObject* SetText(PyObject *self, PyObject *args);

    // Draws the Text with the given vector index
    static PyObject* DrawText(PyObject *self, PyObject *args);

    private:
};

//// PYTHON DOCS ////

// corresponding documentation for engine_create_font
PyDoc_STRVAR(
	engine_create_font_doc,
	".. function:: create_font(filename)\n"
	"\n"
	"  Creates a font from the given file name.\n"
	"\n"
	"  :return: an integer representing the font's id.\n");

// corresponding documentation for engine_create_text
PyDoc_STRVAR(
	engine_create_text_doc,
	".. function:: create_text(font_id)\n"
	"\n"
	"  Creates a text object from the given font id.\n"
	"\n"
	"  :return: an integer representing the text's id.\n");

// corresponding documentation for set_text_position
PyDoc_STRVAR(
	engine_set_text_position_doc,
	".. function:: set_text_position(id, (x, y))\n"
	"\n"
	"  Sets the position of the text with the given id at the x and y provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_text_size
PyDoc_STRVAR(
	engine_set_text_size_doc,
	".. function:: set_text_size(id, size)\n"
	"\n"
	"  Sets the size of the text with the given id\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_text_color
PyDoc_STRVAR(
	engine_set_text_color_doc,
	".. function:: set_text_color(id, (r, g, b, a))\n"
	"\n"
	"  Sets the color of the text with the given id with the RGBA values provided in the tuple (second arg)\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for set_text
PyDoc_STRVAR(
	engine_set_text_doc,
	".. function:: set_text(id, string)\n"
	"\n"
	"  Sets the string of the text object with the given id and the given string\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_draw_text
PyDoc_STRVAR(
	engine_draw_text_doc,
	".. function:: draw_text(id)\n"
	"\n"
	"  Draws the text with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

#endif //_TEXT_HANDLER_H_

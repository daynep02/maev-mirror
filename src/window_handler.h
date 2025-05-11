#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

class WindowHandler {
	public:
	WindowHandler(sf::RenderWindow* window);

	// setters for engine
	static PyObject* SetScreenSize(PyObject* self, PyObject* args);

	// getters for engine
    static sf::RenderWindow* getWindow();
	static PyObject* GetScreenWidth(PyObject* self, PyObject* args);
	static PyObject* GetScreenHeight(PyObject* self, PyObject* args);
    static PyObject* Exit(PyObject* self, PyObject* args);

	private:
};

// Vectorf Docs
PyDoc_STRVAR(
    engine_set_screen_size_doc,
    ".. function:: set_screen_size(w,h)\n"
    "\n"
    "  Modifies the engine's internal screen width and height settings."
    "\n"
    "  :return: Nothing."
);

PyDoc_STRVAR(
    engine_get_screen_width_doc,
    ".. function:: get_screen_width()\n"
    "\n"
    "  Returns the engine's internal screen width setting."
    "\n"
    "  :return: Screen width as a long type."
);

PyDoc_STRVAR(
    engine_get_screen_height_doc,
    ".. function:: get_screen_width()\n"
    "\n"
    "  Returns the engine's internal screen height setting."
	"\n"
    "  :return: Screen height as a long type."
);

PyDoc_STRVAR(
	engine_exit_doc,
	".. function:: exit()\n"
	"\n"
	"  Exits the game window.\n"
	"\n"
	"  :return: Nothing.\n");


#endif // _CONSTS_H_

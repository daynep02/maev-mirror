#include "window_handler.h"

// globals for maintaining / handling values
sf::RenderWindow* r_window;
long w;
long h;

WindowHandler::WindowHandler(sf::RenderWindow* window) {
	r_window = window;
	w = 1024;
	h = 600;
}

// setters for engine
PyObject* WindowHandler::SetScreenSize(PyObject* self, PyObject* args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_screen_width expects two longs as arguments\n");
        PyErr_BadArgument();
    }
    // obtain argument contents
    //PyObject* window_o = PyTuple_GetItem(args, 0);
    PyObject* width_o = PyTuple_GetItem(args, 0);
    PyObject* height_o = PyTuple_GetItem(args, 1);
	
	long width = PyLong_AsLong(width_o);
	long height = PyLong_AsLong(height_o);

    (*r_window).setSize({width, height});
	w = width;
	h = height;

    Py_RETURN_NONE;
}

// getters for engine
PyObject* WindowHandler::GetScreenWidth(PyObject* self, PyObject* args) {
    return PyLong_FromLong(w);
}

PyObject* WindowHandler::GetScreenHeight(PyObject* self, PyObject* args) {
	return PyLong_FromLong(h);
}


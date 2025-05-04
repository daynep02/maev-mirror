#ifndef _CONSTS_H_
#define _CONSTS_H_

short SCREEN_WIDTH = 1024;
short SCREEN_HEIGHT = 600;

class Consts {
	public:

	// setters for engine
	// TODO: these are here, but they don't affect anything: screen size set once at particular time
	static PyObject* SetScreenWidth(PyObject* self, PyObject* args) {
	    Py_ssize_t nargs = PyTuple_GET_SIZE(args);                                                                                          
		if (nargs != 1) {
			printf("engine.SetScreenWidth expects a single long as an argument\n");
  	        PyErr_BadArgument();
	    }
	    // obtain argument contents
	    PyObject* ido = PyTuple_GetItem(args, 0);

	    long id = PyLong_AsLong(ido);

		SCREEN_WIDTH = id;

		Py_RETURN_NONE;
	}
	
	static PyObject* SetScreenHeight(PyObject* self, PyObject* args) {
	    Py_ssize_t nargs = PyTuple_GET_SIZE(args);                                                                                          
		if (nargs != 1) {
			printf("engine.SetScreenWidth expects a single long as an argument\n");
  	        PyErr_BadArgument();
	    }
	    // obtain argument contents
	    PyObject* ido = PyTuple_GetItem(args, 0);

	    long id = PyLong_AsLong(ido);

		SCREEN_HEIGHT = id;

		Py_RETURN_NONE;
	}

	// getters for engine
	static PyObject* GetScreenWidth(PyObject* self, PyObject* args) {
		return PyLong_FromLong(SCREEN_WIDTH);
	}
	
	static PyObject* GetScreenHeight(PyObject* self, PyObject* args) {
		return PyLong_FromLong(SCREEN_HEIGHT);
	}
};

// Vectorf Docs
PyDoc_STRVAR(
    engine_set_screen_width_doc,
    ".. function:: SetScreenWidth\n"
    "\n"
    "  Modifies the engine's internal screen width setting."
    "\n"
    "  :return: Nothing."
);

PyDoc_STRVAR(
    engine_set_screen_height_doc,
    ".. function:: SetScreenHeight\n"
    "\n"
    "  Modifies the engine's internal screen height setting."
	"\n"
    "  :return: Nothing."
);

PyDoc_STRVAR(
    engine_get_screen_width_doc,
    ".. function:: GetScreenWidth\n"
    "\n"
    "  Returns the engine's internal screen width setting."
    "\n"
    "  :return: Screen width as a long type."
);

PyDoc_STRVAR(
    engine_get_screen_height_doc,
    ".. function:: GetScreenHeight\n"
    "\n"
    "  Returns the engine's internal screen height setting."
	"\n"
    "  :return: Screen height as a long type."
);


#endif // consts.h

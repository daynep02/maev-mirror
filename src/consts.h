#ifndef _CONSTS_H_
#define _CONSTS_H_

const short SCREEN_WIDTH = 1024;
const short SCREEN_HEIGHT = 640;

class Consts {
	public:
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

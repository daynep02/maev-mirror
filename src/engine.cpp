#include <Python.h>
#include <SFML/Graphics.hpp>

sf::RenderWindow *window;
sf::CircleShape *circle;

// corresponding documentation for engine_draw_circle
PyDoc_STRVAR(
	engine_draw_circle_doc,
	".. function:: draw_circle(x, y)\n"
	"\n"
	"  Draws a circle centered at (x, y) with radius 10 in th window.\n"
	"\n"
	"  :return: Nothing.\n");

// given (x,y) positions tuple, set & draw a circle
static PyObject *engine_draw_circle(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.draw_circle expects 2 longs as arguments\n");
		PyErr_BadArgument();
	}
	PyObject *pX = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pX)) {
		Py_XDECREF(pX);
		printf("engine.draw_circle expects 2 longs as arguments\n");
		PyErr_BadArgument();
	}
	PyObject *pY = PyTuple_GetItem(args, 1);
	if (!PyLong_Check(pY)) {
		Py_XDECREF(pY);
		printf("engine.draw_circle expects 2 longs as arguments\n");
		PyErr_BadArgument();
	}

	long x = PyLong_AsLong(pX);
	long y = PyLong_AsLong(pY);

	circle->setPosition(sf::Vector2f(x, y));
	window->draw(*circle);

	Py_RETURN_NONE;
}

// Python methods built into engine
static PyMethodDef EngineMethods[] = {
	{"draw_circle", engine_draw_circle, METH_VARARGS, engine_draw_circle_doc},
	{NULL, NULL, 0, NULL}};

// initialization values
static PyModuleDef EngineModule = {PyModuleDef_HEAD_INIT,
                                   "engine",
                                   NULL,
                                   -1,
                                   EngineMethods,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL};

// init function
PyMODINIT_FUNC PyInit_engine(void) { return PyModule_Create(&EngineModule); }

int main(int argc, char *argv[]) {
	// Setup
	PyObject *pName, *pModule, *pFuncInit, *pFuncUpdate, *pFuncDraw;
	PyObject *pArgs, *pValue;
	PyObject *pErr;
	int i;

	if (argc != 2) {
		fprintf(stderr, "Usage: engine pythongame.py\n");
		return 1;
	}

	// Engine initialization
	PyImport_AppendInittab("engine", PyInit_engine);

	// obtain Python game
	Py_Initialize();
	char *pythonfilename = argv[1];
	char *extension = strstr(pythonfilename, ".py\0");

	// normalize filename by removing file extension
	if (extension) {
		strncpy(extension, "\0", 1);
	}
	pName = PyUnicode_DecodeFSDefault(pythonfilename);

	PyRun_SimpleString("import sys\n"
                     "sys.path.insert(0, \".\")");

	// load local instance of pName
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);	// dereferences object, thus no longer using it

	if (pModule == NULL) {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}

	// Look for Key Functions in Python Game
	// Init
	pFuncInit = PyObject_GetAttrString(pModule, "init");
	if (!pFuncInit || !PyCallable_Check(pFuncInit)) {
		if (PyErr_Occurred()) {		// doesn't exist
			PyErr_Print();
		}
		fprintf(stderr, "Cannot find function \"init\"\n");
		return 1;
	}
	
	// Update
	pFuncUpdate = PyObject_GetAttrString(pModule, "update");
	if (!pFuncUpdate || !PyCallable_Check(pFuncUpdate)) {
		if (PyErr_Occurred()) {		// doesn't exist
			PyErr_Print();
		}
		fprintf(stderr, "Cannot find function \"update\"\n");
		return 1;
	}

	// Draw
	pFuncDraw = PyObject_GetAttrString(pModule, "draw");
	if (!pFuncDraw || !PyCallable_Check(pFuncDraw)) {
		if (PyErr_Occurred()) {		// doesn't exist
			PyErr_Print();
		}
		fprintf(stderr, "Cannot find function \"draw\"\n");
		return 1;
	}

	// assign globals
	window = new sf::RenderWindow(sf::VideoMode({400, 400}), "Engine!");
	circle = new sf::CircleShape(10.f);

	circle->setFillColor(sf::Color::Green);

	// loads in the init Key Function of Python Game
	pValue = PyObject_CallNoArgs(pFuncInit);
	Py_DECREF(pValue);

	// SFML loop (ver. 3.0.0)
	while (window->isOpen()) {
		while (std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
				break;
			}
		}

		if (!window->isOpen()) {
			break;
		}

		// loads in update Key Function of Python Game
		pValue = PyObject_CallNoArgs(pFuncUpdate);
		pErr = PyErr_Occurred();
		// catch-all for errors that game causes
		if (pErr) {
			printf("An error occurred!\n");
			window->close();
			break;
		}
		Py_XDECREF(pValue);		// dereferences, but pValue can already be NULL

		window->clear();

		// loads in draw Key Function of Python Game
		pValue = PyObject_CallNoArgs(pFuncDraw);
		pErr = PyErr_Occurred();
		// catch-all for errors that game causes
		if (pErr) {
			printf("An error has occurred\n");
			window->close();
			break;
		}
		Py_XDECREF(pValue);		// dereferences, but pValue can already be NULL
		
		window->display();
	}

	// Teardown
	Py_XDECREF(pFuncDraw);
	Py_XDECREF(pFuncUpdate);
	Py_XDECREF(pFuncInit);
	Py_XDECREF(pModule);

	if (Py_FinalizeEx() < 0) {
		return 120;
	}

	return 0;
}

#include <Python.h>
#include <SFML/Graphics.hpp>

sf::RenderWindow *window;
sf::CircleShape *circle;

PyDoc_STRVAR(
    engine_draw_circle_doc,
    ".. function:: draw_circle(x, y)\n"
    "\n"
    "  Draws a circle centered at (x, y) with radius 10 in th window.\n"
    "\n"
    "  :return: Nothing.\n");
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

static PyMethodDef EngineMethods[] = {
    {"draw_circle", engine_draw_circle, METH_VARARGS, engine_draw_circle_doc},
    {NULL, NULL, 0, NULL}};

static PyModuleDef EngineModule = {PyModuleDef_HEAD_INIT,
                                   "engine",
                                   NULL,
                                   -1,
                                   EngineMethods,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL};

PyMODINIT_FUNC PyInit_engine(void) { return PyModule_Create(&EngineModule); }

int main(int argc, char *argv[]) {
  PyObject *pName, *pModule, *pFuncInit, *pFuncUpdate, *pFuncDraw;
  PyObject *pArgs, *pValue;
  PyObject *pErr;
  int i;

  if (argc != 2) {
    fprintf(stderr, "Usage: engine pythongame.py\n");
    return 1;
  }

  PyImport_AppendInittab("engine", PyInit_engine);

  Py_Initialize();
  char *pythonfilename = argv[1];
  char *extension = strstr(pythonfilename, ".py\0");

  if (extension)
    strncpy(extension, "\0", 1);
  pName = PyUnicode_DecodeFSDefault(pythonfilename);

  PyRun_SimpleString("import sys\n"
                     "sys.path.insert(0, \".\")");

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if (pModule == NULL) {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return 1;
  }

  pFuncInit = PyObject_GetAttrString(pModule, "init");
  if (!pFuncInit || !PyCallable_Check(pFuncInit)) {
    if (PyErr_Occurred())
      PyErr_Print();
    fprintf(stderr, "Cannot find function \"init\"\n");
    return 1;
  }
  pFuncUpdate = PyObject_GetAttrString(pModule, "update");

  if (!pFuncUpdate || !PyCallable_Check(pFuncUpdate)) {
    if (PyErr_Occurred())
      PyErr_Print();

    fprintf(stderr, "Cannot find function \"update\"\n");
    return 1;
  }
  pFuncDraw = PyObject_GetAttrString(pModule, "draw");
  if (!pFuncDraw || !PyCallable_Check(pFuncDraw)) {
    if (PyErr_Occurred())
      PyErr_Print();
    fprintf(stderr, "Cannot find function \"draw\"\n");
    return 1;
  }

  window = new sf::RenderWindow(sf::VideoMode({400, 400}), "Engine!");
  circle = new sf::CircleShape(10.f);

  circle->setFillColor(sf::Color::Green);

  pValue = PyObject_CallNoArgs(pFuncInit);
  Py_DECREF(pValue);

  while (window->isOpen()) {
    while (std::optional event = window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window->close();
        break;
      }
    }

    if (!window->isOpen())
      break;

    pValue = PyObject_CallNoArgs(pFuncUpdate);
    pErr = PyErr_Occurred();
    if (pErr) {
      printf("An error occurred!\n");
      window->close();
      break;
    }

    Py_XDECREF(pValue);

    window->clear();
    pValue = PyObject_CallNoArgs(pFuncDraw);
    pErr = PyErr_Occurred();
    if (pErr) {
      printf("An error has occurred\n");
      window->close();
      break;
    }
    Py_XDECREF(pValue);

    window->display();
  }

  Py_XDECREF(pFuncDraw);
  Py_XDECREF(pFuncUpdate);
  Py_XDECREF(pFuncInit);
  Py_XDECREF(pModule);

  if (Py_FinalizeEx() < 0) {
    return 120;
  }

  return 0;
}

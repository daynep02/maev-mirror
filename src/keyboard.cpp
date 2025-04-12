/**
 * @file keyboard.cpp
 * @author Dayne Pefley
 * @brief the definitions of keyboard.h
 */
#ifndef keyboard_cpp
#define keyboard_cpp
#include "keyboard.h"
#include <SFML/Graphics.hpp>

PyObject *Keyboard::key_is_pressed(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.key_is_pressed expects 1 argument");
    PyErr_BadArgument();
  }
  PyObject *pKey = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pKey)) {
    Py_XDECREF(pKey);
    printf("engine.key_is_pressed expects 1 long as argumen");
    PyErr_BadArgument();
  }

  if (isPressed(PyLong_AsLong(pKey))) {

    printf("Key Pressed!\n");
    return Py_True;
  } else
    return Py_False;
}

bool Keyboard::isPressed(int key) {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
}

#endif // keyboard_cpp

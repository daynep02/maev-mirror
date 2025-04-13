/**
 * @file keyboard.cpp
 * @author Dayne Pefley
 * @brief the definitions of keyboard.h
 */
#ifndef keyboard_cpp
#define keyboard_cpp
#include "keyboard.h"
#include "unicodeobject.h"
#include <SFML/Graphics.hpp>
#include <string.h>

PyObject *Keyboard::key_is_pressed(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.key_is_pressed expects 1 argument");
    PyErr_BadArgument();
  }
  PyObject *pKey = PyTuple_GetItem(args, 0);

  std::string keyStr = PyUnicode_AsUTF8(pKey);

  if (keyStr.size() > 1) {
    Py_XDECREF(pKey);
    printf("engine.key_is_pressed expects 1 char as argument");
    PyErr_BadArgument();
  }
  if (isPressed(keyStr[0])) {

    printf("Key Pressed!\n");
    return Py_True;
  } else
    return Py_False;
}

bool Keyboard::isPressed(int key) {

  return sf::Keyboard::isKeyPressed(UnicodeToSFML(key));
}

sf::Keyboard::Key Keyboard::UnicodeToSFML(char key) {
  if (key >= 'a' && key <= 'z')
    key = 'A' + (key - 'a');
  if (key >= 'A' && key <= 'Z')
    key = key - 'A';
  return sf::Keyboard::Key(key);
}

#endif // keyboard_cpp

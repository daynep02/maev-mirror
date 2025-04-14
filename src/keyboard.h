/**
 * @author Dayne Pefley
 * @file keyboard.h
 * @brief defines the functions for reading input from the keyboard
 */
#ifndef keyboard_h
#define keyboard_h
#include "SFML/Window/Keyboard.hpp"
#include <Python.h>
#include <SFML/Window.hpp>
#include <unordered_map>

class Keyboard {
public:
  static PyObject *key_is_pressed(PyObject *self, PyObject *args);

  static bool isPressed(std::string keyName);

  /*
  typedef struct {
    PyObject_HEAD const char *data;
  } keys;
*/

  using kb = sf::Keyboard::Key;
  static const std::unordered_map<std::string, kb> keys;
};

PyDoc_STRVAR(key_is_pressed_doc,

             ".. function:: key_is_Pressed\n"
             "\n"
             "  Reports if a specific key has been pressed\n"
             "\n"
             ":return: bool.\n");

static PyMethodDef keyPressed = {"key_is_pressed", Keyboard::key_is_pressed,
                                 METH_VARARGS, key_is_pressed_doc};

#endif // keyboard_h

/**
 * @file keyboard.h
 * @author Dayne Pefley
 * @brief defines the functions for reading input from the keyboard
 */

#ifndef keyboard_h
#define keyboard_h
#include "SFML/Window/Keyboard.hpp"
#include <Python.h>
#include <SFML/Window.hpp>
#include <unordered_map>

/**
 * @class Keyboard
 * @brief defines the functions for reading input from the keyboard.
 */
class Keyboard {
public:

  /**
  * @param self required for all python API functions
  * @param args contains args passed from python. Should contain a single string
  * @return Python_TRUE type if the specified key is pressed
  * @brief the API that allows for queries into if a key is pressed
  */
  static PyObject *key_is_pressed(PyObject *self, PyObject *args);


  static PyObject* mouse_button_is_pressed(PyObject *self, PyObject *args);

  /**
  * @param keyName the name of the key we are querying if pressed
  * @return bool
  * @brief a helper function to the python available is_key_pressed
  */
  static bool isPressed(std::string keyName);

  static bool isMousePressed(std::string button);


  /**
   * @brief a simple abstraction so we don't have to type so much
   */
  using kb = sf::Keyboard::Key;

  using mb = sf::Mouse::Button;
  /**
  * @brief An unordered map to hopefully efficiently translate between a string and an SFML keybind
  */
  static const std::unordered_map<std::string, kb> keys;

  static const std::unordered_map<std::string, mb> buttons;
};

PyDoc_STRVAR(key_is_pressed_doc,

             ".. function:: key_is_Pressed\n"
             "\n"
             "  Reports if a specific key has been pressed\n"
             "\n"
             ":return: bool.\n");
/**
  * @brief gives the definiton of the function available in python
  */
static PyMethodDef keyPressed = {"key_is_pressed", Keyboard::key_is_pressed,
                                 METH_VARARGS, key_is_pressed_doc};

static PyMethodDef mousePressed = {"mouse_button_is_pressed", Keyboard::mouse_button_is_pressed,
                                  METH_VARARGS, key_is_pressed_doc};

#endif // keyboard_h

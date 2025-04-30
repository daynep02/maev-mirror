/**
 * @file keyboard.cpp
 * @author Dayne Pefley
 * @brief the declarations of keyboard.h
 */
#ifndef keyboard_cpp
#define keyboard_cpp
#include "keyboard.h"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

PyObject *Keyboard::key_is_pressed(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.key_is_pressed expects 1 argument\n");
    PyErr_BadArgument();
  }

  PyObject *pKey = PyTuple_GetItem(args, 0);

  if(!PyUnicode_Check(pKey)) {
    printf("engine.key_is_pressed expects a string\n");
    PyErr_BadArgument();
  }
  std::string keyStr = PyUnicode_AsUTF8(pKey);

  if (isPressed(keyStr)) {
    Py_RETURN_TRUE;
  }

  Py_RETURN_FALSE;
}

bool Keyboard::isPressed(std::string key) {
  auto sample = keys.find(key);

  if (sample == keys.end())
    return false;
  // printf("Testing %s\n", sample->first.c_str());
  return sf::Keyboard::isKeyPressed(sample->second);
}

using kb = sf::Keyboard::Key;
const std::unordered_map<std::string, kb> Keyboard::keys = {
    {"Unknown", kb::Unknown},
    {"A", kb::A},
    {"B", kb::B},
    {"C", kb::C},
    {"D", kb::D},
    {"E", kb::E},
    {"F", kb::F},
    {"G", kb::G},
    {"H", kb::H},
    {"I", kb::I},
    {"J", kb::J},
    {"K", kb::K},
    {"L", kb::L},
    {"M", kb::M},
    {"O", kb::O},
    {"P", kb::P},
    {"Q", kb::Q},
    {"R", kb::R},
    {"S", kb::S},
    {"T", kb::T},
    {"U", kb::U},
    {"V", kb::V},
    {"W", kb::W},
    {"X", kb::X},
    {"Y", kb::Y},
    {"Z", kb::Z},
    {"NUM0", kb::Num0},
    {"NUM1", kb::Num1},
    {"NUM2", kb::Num2},
    {"NUM3", kb::Num3},
    {"NUM4", kb::Num4},
    {"NUM5", kb::Num5},
    {"NUM6", kb::Num6},
    {"NUM7", kb::Num7},
    {"NUM8", kb::Num8},
    {"NUM9", kb::Num9},
    {"ESCAPE", kb::Escape},
    {"LCONCTROL", kb::LControl},
    {"LSHIFT", kb::LShift},
    {"LALT", kb::LAlt},
    {"LSYSTEM", kb::LSystem},
    {"RCONTROL", kb::RControl},
    {"RSHIFT", kb::RShift},
    {"RALT", kb::RAlt},
    {"RSYSTEM", kb::RSystem},
    {"MENU", kb::Menu},
    {"[", kb::LBracket},
    {"]", kb::RBracket},
    {";", kb::Semicolon},
    {",", kb::Comma},
    {".", kb::Period},
    {"'", kb::Apostrophe},
    {"/", kb::Slash},
    {"\\", kb::Backslash},
    {"`", kb::Grave},
    {"=", kb::Equal},
    {"-", kb::Hyphen},
    {" ", kb::Space},
    {"ENTER", kb::Enter},
    {"BACKSPACE", kb::Backspace},
    {"TAB", kb::Tab},
    {"PAGEUP", kb::PageUp},
    {"PAGEDOWN", kb::PageDown},
    {"END", kb::End},
    {"HOME", kb::Home},
    {"INSERT", kb::Insert},
    {"DELETE", kb::Delete},
    {"Left", kb::Left},
    {"Right", kb::Right},
    {"Up", kb::Up},
    {"Down", kb::Down}};

#endif // keyboard_cpp

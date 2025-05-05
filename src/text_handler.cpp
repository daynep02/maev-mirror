#include "text_handler.h"
#include <algorithm>
#include <cmath>
#include <vector>

sf::RenderWindow* text_window;

// possible bug: vectors could technically change the address of the contents,
// so be careful
std::vector<sf::Font *> fonts;
std::vector<sf::Text *> texts;

// stores the window to be accessible from the static Python functions
TextHandler::TextHandler(sf::RenderWindow *window) { text_window = window; }

TextHandler::~TextHandler() {
  std::for_each(fonts.begin(), fonts.end(), delete_ptr());
  fonts.clear();

  std::for_each(texts.begin(), texts.end(), delete_ptr());
  texts.clear();
}

/*static*/ PyObject *TextHandler::CreateFont(PyObject *self,
  PyObject *args) {

    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
      printf("engine.create_font expects a single string as an argument\n");
      PyErr_BadArgument();
    }
    PyObject *pName = PyTuple_GetItem(args, 0);
  
    //printf("engine.create_font: Creating String\n");
  
    std::string name = PyUnicode_AsUTF8(pName);
  
    printf("engine.create_font: Creating Font from %s\n", name.c_str());
    sf::Font *font = new sf::Font;
    bool res = font->openFromFile(name.c_str());
    if (!res) {
      printf("engine.create_font: Could not load file %s\n", name.c_str());
      PyErr_BadArgument();
    }
  
    long loc;
    fonts.push_back(font);
    loc = fonts.size() - 1;
  
    printf("engine.create_font: Returning ID %ld\n", loc);
  
    //Py_XDECREF(pName);
  
    return PyLong_FromLong(loc);
  }

/*static*/ PyObject *TextHandler::CreateText(PyObject *self,
                                                 PyObject *args) {

  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.create_text expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pFont = PyTuple_GetItem(args, 0);

  long font_id = PyLong_AsLong(pFont);

  if (fonts.size() <= font_id || font_id < 0) {
    Py_XDECREF(pFont);
    printf("engine.create_text got a font id out of range\n");
    PyErr_BadArgument();
  }

  printf("engine.create_text: Creating Text from font %ld\n", font_id);

  long loc;
  sf::Text *text = new sf::Text(*fonts.at(font_id));
  text->setPosition({0, 0});
  texts.push_back(text);
  loc = texts.size() - 1;

  printf("engine.create_text: Returning ID %ld\n", loc);

  //Py_XDECREF(pName);

  return PyLong_FromLong(loc);
}

/*static*/ PyObject *TextHandler::SetTextPosition(PyObject *self,
                                                      PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_text_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_text_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (texts.size() <= id || id < 0) {
    Py_XDECREF(pId);
    printf("engine.set_text_position got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 1);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  printf("engine.set_text_position: setting position\n");

  texts.at(id)->setPosition(sf::Vector2f(x, y));

  printf("engine.set_text_position: done setting position\n");

	// TODO: free() getting invalid pointer somewhere here?
  //Py_XDECREF(pId);
  //Py_XDECREF(pPosition);
  //Py_XDECREF(pX);
  //Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *TextHandler::SetTextSize(PyObject *self,
  PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
      printf("engine.set_text_size expects two longs as "
             "arguments\n");
      PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
      Py_XDECREF(pId);
      printf("engine.set_text_size expects two longs as "
        "arguments\n");
      PyErr_BadArgument();
    }
  
    long id = PyLong_AsLong(pId);
  
    if (texts.size() <= id || id < 0) {
      Py_XDECREF(pId);
      printf("engine.set_text_size got a sprite id out of range\n");
      PyErr_BadArgument();
    }
  
    PyObject *pSize = PyTuple_GetItem(args, 1);
  
    long size = PyLong_AsLong(pSize);
  
    texts.at(id)->setCharacterSize(size);
  
    // TODO: free() getting invalid pointer somewhere here?
    //Py_XDECREF(pId);
    //Py_XDECREF(pPosition);
    //Py_XDECREF(pX);
    //Py_XDECREF(pY);
  
    Py_RETURN_NONE;
  }

/*static*/ PyObject *TextHandler::SetTextColor(PyObject *self,
                                                      PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_text_color expects a long and a 4-tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_text_color expects a long and a 4-tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (texts.size() <= id || id < 0) {
    Py_XDECREF(pId);
    printf("engine.set_text_color got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pColor = PyTuple_GetItem(args, 1);
  PyObject *pR = PyTuple_GetItem(pColor, 0);
  PyObject *pG = PyTuple_GetItem(pColor, 1);
  PyObject *pB = PyTuple_GetItem(pColor, 2);
  PyObject *pA = PyTuple_GetItem(pColor, 3);

  // printf("engine.set_text_color: setting new position\n");

  double r = PyFloat_AsDouble(pR);
  double g = PyFloat_AsDouble(pG);
  double b = PyFloat_AsDouble(pB);
  double a = PyFloat_AsDouble(pA);

  // printf("engine.set_text_color: setting position\n");

  texts.at(id)->setFillColor(sf::Color(r, g, b, a));

  //Py_XDECREF(pId);
  //Py_XDECREF(pPosition);
  //Py_XDECREF(pX);
  //Py_XDECREF(pY);

  Py_RETURN_NONE;
}
  
/*static*/ PyObject *TextHandler::SetText(PyObject *self,
                                                   PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf(
        "engine.set_text expects a long and a string as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.set_text expects a long and a string as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (texts.size() <= id || id < 0) {
    Py_XDECREF(pId);
    printf("engine.set_text got a text id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pText = PyTuple_GetItem(args, 1);
  std::string text = PyUnicode_AsUTF8(pText);

  texts.at(id)->setString(text);

  // Py_XDECREF(pId);
  // Py_XDECREF(pPosition);
  // Py_XDECREF(pX);
  // Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *TextHandler::DrawText(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.draw_sprite expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.draw_sprite expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (texts.size() <= id || id < 0) {
    Py_XDECREF(pId);
    printf("engine.draw_sprite got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  // printf("engine.draw_sprite: Drawing Sprite %lu\n",id);

  text_window->draw(*texts.at(id));

  // Py_XDECREF(pId);
  // printf("engine.draw_sprite: Returning\n");

  Py_RETURN_NONE;
}

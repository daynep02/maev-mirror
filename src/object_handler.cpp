#include "object_handler.h"
#include <algorithm>
#include <cmath>
#include <vector>

sf::RenderWindow* object_window;

// possible bug: vectors could technically change the address of the contents,
// so be careful
std::vector<sf::Texture *> textures;
std::vector<sf::Sprite *> sprites;
std::vector<long> free_sprites;
std::vector<sf::CircleShape *> circles;

// stores the window to be accessible from the static Python functions
ObjectHandler::ObjectHandler(sf::RenderWindow *window) { object_window = window; }

ObjectHandler::~ObjectHandler() {
  std::for_each(textures.begin(), textures.end(), delete_ptr());
  textures.clear();

  std::for_each(sprites.begin(), sprites.end(), delete_ptr());
  sprites.clear();

  std::for_each(circles.begin(), circles.end(), delete_ptr());
  circles.clear();
}

/*static*/ PyObject *ObjectHandler::CreateSprite(PyObject *self,
                                                 PyObject *args) {

  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.create_sprite expects a single string as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pName = PyTuple_GetItem(args, 0);

  printf("engine.create_sprite: Creating String\n");

  std::string name = PyUnicode_AsUTF8(pName);

  printf("engine.create_sprite: Creating Texture from %s\n", name.c_str());
  sf::Texture *texture = new sf::Texture;
  bool res = texture->loadFromFile(name.c_str());
  if (!res) {
    printf("engine.create_sprite: Could not load file %s\n", name.c_str());
    PyErr_BadArgument();
  }

  printf("engine.create_sprite: Checking for Free Sprites\n");
  long loc;
  if (!free_sprites.empty()) {
    printf("engine.create_sprite: Using Free Sprites\n");
    loc = free_sprites.back();
    free_sprites.pop_back();
    printf("engine.create_sprite: Adding to Vector\n");
    delete textures.at(loc);
    textures.at(loc) = texture;
    sf::Sprite *sprite = new sf::Sprite(*textures.at(loc));
    sprite->setPosition({0, 0});
    delete sprites.at(loc);
    sprites.at(loc) = sprite;
  } else {
    textures.push_back(texture);
    loc = textures.size() - 1;
    printf("engine.create_sprite: Adding to Vector\n");
    sf::Sprite *sprite = new sf::Sprite(*textures.at(loc));
    sprite->setPosition({0, 0});
    sprites.push_back(sprite);
    loc = textures.size() - 1;
  }

  printf("engine.create_sprite: Returning ID\n");

  //Py_XDECREF(pName);

  return PyLong_FromLong(loc);
}

/*static*/ PyObject *ObjectHandler::SetSpritePosition(PyObject *self,
                                                      PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_sprite_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_sprite_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (sprites.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.set_sprite_position got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 1);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  printf("engine.set_sprite_position: setting position\n");

  sprites.at(id)->setPosition(sf::Vector2f(x, y));

  printf("engine.set_sprite_position: done setting position\n");

	// TODO: free() getting invalid pointer somewhere here?
  //Py_XDECREF(pId);
  //Py_XDECREF(pPosition);
  //Py_XDECREF(pX);
  //Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetSpriteScale(PyObject *self,
                                                   PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf(
        "engine.set_sprite_scale expects a long and a tuple as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.set_sprite_scale expects a long and a tuple as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (sprites.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.set_sprite_scale got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 0);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  sprites.at(id)->setScale(sf::Vector2f(x, y));

  // Py_XDECREF(pId);
  // Py_XDECREF(pPosition);
  // Py_XDECREF(pX);
  // Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::DrawSprite(PyObject *self, PyObject *args) {
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

  if (sprites.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.draw_sprite got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  // printf("engine.draw_sprite: Drawing Sprite %lu\n",id);

  object_window->draw(*sprites.at(id));

  // Py_XDECREF(pId);
  // printf("engine.draw_sprite: Returning\n");

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::FreeSprite(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.free_sprite expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.free_sprite expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (sprites.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.free_sprite got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  free_sprites.push_back(id);

  // Py_XDECREF(pId);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::CreateCircle(PyObject *self,
                                                 PyObject *args) {

  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.create_circle expects a single float as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pRadius = PyTuple_GetItem(args, 0);

  double radius = PyFloat_AsDouble(pRadius);

  circles.push_back(new sf::CircleShape(radius));
  long id = circles.size() - 1;

  // Py_XDECREF(pRadius);

  return PyLong_FromLong(id);
}

/*static*/ PyObject *ObjectHandler::SetCircleFillColor(PyObject *self,
                                                       PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_circle_fill_color expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_circle_fill_color expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (circles.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.set_circle_fill_color got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pColor = PyTuple_GetItem(args, 1);
  PyObject *pR = PyTuple_GetItem(pColor, 0);
  PyObject *pG = PyTuple_GetItem(pColor, 1);
  PyObject *pB = PyTuple_GetItem(pColor, 2);
  PyObject *pA = PyTuple_GetItem(pColor, 3);

  // printf("engine.set_circle_position: setting new position\n");

  double r = PyFloat_AsDouble(pR);
  double g = PyFloat_AsDouble(pG);
  double b = PyFloat_AsDouble(pB);
  double a = PyFloat_AsDouble(pA);

  // printf("engine.set_sprite_position: setting position\n");

  circles.at(id)->setFillColor(sf::Color(r, g, b, a));

  // printf("engine.set_sprite_position: done setting position\n");

  // Py_XDECREF(pId);
  // Py_XDECREF(pPosition);
  // Py_XDECREF(pX);
  // Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCirclePosition(PyObject *self,
                                                      PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_circle_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_circle_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (circles.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.set_circle_position got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 1);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  // printf("engine.set_circle_position: setting new position\n");

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  // printf("engine.set_sprite_position: setting position\n");

  circles.at(id)->setPosition(sf::Vector2f(x, y));

  // printf("engine.set_sprite_position: done setting position\n");

  // Py_XDECREF(pId);
  // Py_XDECREF(pPosition);
  // Py_XDECREF(pX);
  // Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCircleScale(PyObject *self,
                                                   PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf(
        "engine.set_circle_scale expects a long and a tuple as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.set_circle_scale expects a long and a tuple as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (circles.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.set_circle_scale got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 0);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  circles.at(id)->setScale(sf::Vector2f(x, y));

  // Py_XDECREF(pId);
  // Py_XDECREF(pPosition);
  // Py_XDECREF(pX);
  // Py_XDECREF(pY);

  Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::DrawCircle(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.draw_circle expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.draw_circle expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (circles.size() <= id) {
    Py_XDECREF(pId);
    printf("engine.draw_circle got a sprite id out of range\n");
    PyErr_BadArgument();
  }

  // printf("engine.draw_sprite: Drawing Sprite %lu\n",id);

  object_window->draw(*circles.at(id));

  // Py_XDECREF(pId);
  // printf("engine.draw_sprite: Returning\n");

  Py_RETURN_NONE;
}

PyObject *ObjectHandler::CollidesWith(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.collides_with expects a two ids as arguments\n");
    PyErr_BadArgument();
  }

  PyObject *pId1 = PyTuple_GetItem(args, 0);
  PyObject *pId2 = PyTuple_GetItem(args, 1);

  if (!PyLong_Check(pId1)) {
    Py_XDECREF(pId1);
    printf("engine.collides_with expects a long and a long as an argument\n");
    PyErr_BadArgument();
  }

  if (!PyLong_Check(pId2)) {
    Py_XDECREF(pId2);
    printf("engine.collides_with expects a long and a long as an argument\n");
    PyErr_BadArgument();
  }

  long id1 = PyLong_AsLong(pId1);
  long id2 = PyLong_AsLong(pId2);

  if (circles.size() <= id1) {
    Py_XDECREF(pId1);
    printf("engine.collides_with got a circle id out of range\n");
    PyErr_BadArgument();
  }

  if (circles.size() <= id2) {
    Py_XDECREF(pId2);
    printf("engine.collides_with got a circle id out of range\n");
    PyErr_BadArgument();
  }

  sf::Vector2f center1 = circles[id1]->getPosition();
  sf::Vector2f center2 = circles[id2]->getPosition();

  // printf("%f, %f; %f %f\n", center1.x, center1.y, center2.x, center2.y);
  double distanceBetween = std::sqrt(std::pow(center1.x - center2.x, 2) +
                                     std::pow(center1.y - center2.y, 2));

  double combinedRadius = circles[id1]->getRadius() + circles[id2]->getRadius();

  return PyBool_FromLong(distanceBetween <= combinedRadius);
}

#include "object_handler.h"
#include "floatobject.h"
#include "tupleobject.h"
#include <algorithm>
#include <cmath>
#include <vector>

sf::RenderWindow *object_window;

// possible bug: vectors could technically change the address of the contents,
// so be careful
std::vector<sf::Texture *> textures;
std::vector<sf::Sprite *> sprites;
std::vector<long> free_sprites;
std::vector<sf::CircleShape *> circles;
std::vector<long> free_circles;
std::vector<sf::RectangleShape *> rects;

// stores the window to be accessible from the static Python functions
ObjectHandler::ObjectHandler(sf::RenderWindow *window) { object_window = window; }

ObjectHandler::~ObjectHandler()
{
	std::for_each(textures.begin(), textures.end(), delete_ptr());
	textures.clear();

	std::for_each(sprites.begin(), sprites.end(), delete_ptr());
	sprites.clear();

	std::for_each(circles.begin(), circles.end(), delete_ptr());
	circles.clear();

	std::for_each(rects.begin(), rects.end(), delete_ptr());
	rects.clear();
}

/*static*/ PyObject *ObjectHandler::CreateSprite(PyObject *self,
												 PyObject *args)
{

	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.create_sprite expects a single string as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pName = PyTuple_GetItem(args, 0);

//	printf("engine.create_sprite: Creating String\n");

	std::string name = PyUnicode_AsUTF8(pName);

//	printf("engine.create_sprite: Creating Texture from %s\n", name.c_str());
	sf::Texture *texture = new sf::Texture;
	bool res = texture->loadFromFile(name.c_str());
	if (!res)
	{
		printf("engine.create_sprite: Could not load file %s\n", name.c_str());
		PyErr_BadArgument();
	}

	//printf("engine.create_sprite: Checking for Free Sprites\n");
	long loc;
	if (!free_sprites.empty())
	{
		//printf("engine.create_sprite: Using Free Sprites\n");
		loc = free_sprites.back();
		free_sprites.pop_back();
		//printf("engine.create_sprite: Adding to Vector\n");
		delete textures.at(loc);
		textures.at(loc) = texture;
		sf::Sprite *sprite = new sf::Sprite(*textures.at(loc));
		sprite->setPosition({0, 0});
		delete sprites.at(loc);
		sprites.at(loc) = sprite;
	}
	else
	{
		textures.push_back(texture);
		loc = textures.size() - 1;
		//printf("engine.create_sprite: Adding to Vector\n");
		sf::Sprite *sprite = new sf::Sprite(*textures.at(loc));
		sprite->setPosition({0, 0});
		sprites.push_back(sprite);
		loc = textures.size() - 1;
	}

	//printf("engine.create_sprite: Returning ID\n");

	// Py_XDECREF(pName);

	return PyLong_FromLong(loc);
}

/*static*/ PyObject *ObjectHandler::SetSpritePosition(PyObject *self,
													  PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_sprite_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_sprite_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_sprite_position got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
	PyObject *pX = PyTuple_GetItem(pPosition, 0);
	PyObject *pY = PyTuple_GetItem(pPosition, 1);

	double x = PyFloat_AsDouble(pX);
	double y = PyFloat_AsDouble(pY);

	//printf("engine.set_sprite_position: setting position\n");

	sprites.at(id)->setPosition(sf::Vector2f(x, y));

	//printf("engine.set_sprite_position: done setting position\n");

	// TODO: free() getting invalid pointer somewhere here?
	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetSpriteScale(PyObject *self,
												   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_sprite_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_sprite_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_sprite_scale got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
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

/*static*/ PyObject *ObjectHandler::GetSpriteRotation(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf(
			"engine.get_sprite_rotation expects a long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.get_sprite_rotation expects a long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.get_sprite_rotation got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	double angle = (double)sprites.at(id)->getRotation().asDegrees();

	return PyFloat_FromDouble(angle);
}

/*static*/ PyObject *ObjectHandler::SetSpriteRotation(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_sprite_rotation expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_sprite_rotation expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_sprite_rotation got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pAngle = PyTuple_GetItem(args, 1);

	float angle = PyFloat_AsDouble(pAngle);

	sprites.at(id)->setRotation(sf::Angle(sf::degrees(angle)));

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SpriteRotate(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.sprite_rotate expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.sprite_rotate expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.sprite_rotate got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pAngle = PyTuple_GetItem(args, 1);

	float angle = PyFloat_AsDouble(pAngle);

	sprites.at(id)->rotate(sf::Angle(sf::degrees(angle)));

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::GetSpriteSize(PyObject *self,
												   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf(
			"engine.get_sprite_size expects a long as an argemunt\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.get_sprite_size expects a long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.get_sprite_size got a sprite id out of range\n");
		PyErr_BadArgument();
	}


	auto size = sprites.at(id)->getTextureRect().size;

  PyObject* x = PyFloat_FromDouble(size.x);
  PyObject* y = PyFloat_FromDouble(size.y);

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	return PyTuple_Pack(2, x, y);
}

/*static*/ PyObject *ObjectHandler::DrawSprite(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.draw_sprite expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.draw_sprite expects a single long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
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

/*static*/ PyObject *ObjectHandler::FreeSprite(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.free_sprite expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.free_sprite expects a single long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (sprites.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.free_sprite got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	free_sprites.push_back(id);

	// Py_XDECREF(pId);

	Py_RETURN_NONE;
}

//// CIRCLE ////

/*static*/ PyObject *ObjectHandler::CreateCircle(PyObject *self,
												 PyObject *args)
{

	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.create_circle expects a single float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pRadius = PyTuple_GetItem(args, 0);

	double radius = PyFloat_AsDouble(pRadius);
	long loc; 
	if (!free_circles.empty()) {
		loc = free_circles.back();
		free_circles.pop_back();
		delete circles.at(loc);
		circles.at(loc) = new sf::CircleShape(radius);
	} else {
		circles.push_back(new sf::CircleShape(radius));
		loc = circles.size() - 1;
	}

	return PyLong_FromLong(loc);
}

/*static*/ PyObject *ObjectHandler::SetCircleFillColor(PyObject *self,
													   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_circle_fill_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_fill_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_fill_color got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pColor = PyTuple_GetItem(args, 1);
	PyObject *pR = PyTuple_GetItem(pColor, 0);
	PyObject *pG = PyTuple_GetItem(pColor, 1);
	PyObject *pB = PyTuple_GetItem(pColor, 2);
	PyObject *pA = PyTuple_GetItem(pColor, 3);

	double r = PyFloat_AsDouble(pR);
	double g = PyFloat_AsDouble(pG);
	double b = PyFloat_AsDouble(pB);
	double a = PyFloat_AsDouble(pA);

	circles.at(id)->setFillColor(sf::Color(r, g, b, a));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCirclePosition(PyObject *self,
													  PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_circle_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_position got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
	PyObject *pX = PyTuple_GetItem(pPosition, 0);
	PyObject *pY = PyTuple_GetItem(pPosition, 1);

	double x = PyFloat_AsDouble(pX);
	double y = PyFloat_AsDouble(pY);

	circles.at(id)->setPosition(sf::Vector2f(x, y));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCircleScale(PyObject *self,
												   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_circle_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_circle_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_scale got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
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

/*static*/ PyObject *ObjectHandler::SetCircleRadius(PyObject *self,
													PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_circle_radius expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_circle_radius expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_radius got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pRadius = PyTuple_GetItem(args, 1);

	double x = PyFloat_AsDouble(pRadius);

	circles.at(id)->setRadius(x);

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCircleOutlineThickness(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_circle_outline_thickness expects a long and a float as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_outline_thickness expects a long and a float as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_outline_thickness got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pThickness = PyTuple_GetItem(args, 1);

	double thick = PyFloat_AsDouble(pThickness);

	circles.at(id)->setOutlineThickness((float)thick);

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetCircleOutlineColor(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_circle_outline_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_outline_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_circle_outline_color got a circle id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pColor = PyTuple_GetItem(args, 1);
	PyObject *pR = PyTuple_GetItem(pColor, 0);
	PyObject *pG = PyTuple_GetItem(pColor, 1);
	PyObject *pB = PyTuple_GetItem(pColor, 2);
	PyObject *pA = PyTuple_GetItem(pColor, 3);

	double r = PyFloat_AsDouble(pR);
	double g = PyFloat_AsDouble(pG);
	double b = PyFloat_AsDouble(pB);
	double a = PyFloat_AsDouble(pA);

	circles.at(id)->setOutlineColor(sf::Color(r, g, b, a));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::DrawCircle(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.draw_circle expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.draw_circle expects a single long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (circles.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.draw_circle got a circle id out of range\n");
		PyErr_BadArgument();
	}

	object_window->draw(*circles.at(id));

	// Py_XDECREF(pId);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::FreeCircle(PyObject *self,
                                                     PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.free_circle expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.free_circle expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (circles.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.free_circle got a circle id out of range\n");
    PyErr_BadArgument();
  }

  free_circles.push_back(id);

  // Py_XDECREF(pId);

  Py_RETURN_NONE;
}

//// RECTANGLE ////

/*static*/ PyObject *ObjectHandler::CreateRect(PyObject *self,
												 PyObject *args)
{

	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.create_rect expects a single 2-tuple of floats as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pSize = PyTuple_GetItem(args, 0);
	PyObject *pW = PyTuple_GetItem(pSize, 0);
	PyObject *pH = PyTuple_GetItem(pSize, 1);

	float w = (float)PyFloat_AsDouble(pW);
	float h = (float)PyFloat_AsDouble(pH);

	rects.push_back(new sf::RectangleShape({w,h}));
	long id = rects.size() - 1;

	// Py_XDECREF(pRadius);

	return PyLong_FromLong(id);
}

/*static*/ PyObject *ObjectHandler::SetRectFillColor(PyObject *self,
													   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_rect_fill_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_fill_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_fill_color got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pColor = PyTuple_GetItem(args, 1);
	PyObject *pR = PyTuple_GetItem(pColor, 0);
	PyObject *pG = PyTuple_GetItem(pColor, 1);
	PyObject *pB = PyTuple_GetItem(pColor, 2);
	PyObject *pA = PyTuple_GetItem(pColor, 3);

	double r = PyFloat_AsDouble(pR);
	double g = PyFloat_AsDouble(pG);
	double b = PyFloat_AsDouble(pB);
	double a = PyFloat_AsDouble(pA);

	rects.at(id)->setFillColor(sf::Color(r, g, b, a));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetRectPosition(PyObject *self,
													  PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_rect_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_position expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_position got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
	PyObject *pX = PyTuple_GetItem(pPosition, 0);
	PyObject *pY = PyTuple_GetItem(pPosition, 1);

	double x = PyFloat_AsDouble(pX);
	double y = PyFloat_AsDouble(pY);

	rects.at(id)->setPosition(sf::Vector2f(x, y));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetRectScale(PyObject *self,
												   PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_rect_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_rect_scale expects a long and a tuple as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_scale got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pPosition = PyTuple_GetItem(args, 1);
	PyObject *pX = PyTuple_GetItem(pPosition, 0);
	PyObject *pY = PyTuple_GetItem(pPosition, 1);

	double x = PyFloat_AsDouble(pX);
	double y = PyFloat_AsDouble(pY);

	rects.at(id)->setScale(sf::Vector2f(x, y));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::GetRectRotation(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf(
			"engine.get_rect_rotation expects a long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.get_rect_rotation expects a long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.get_rect_rotation got a rect id out of range\n");
		PyErr_BadArgument();
	}

	double angle = (double)rects.at(id)->getRotation().asDegrees();

	return PyFloat_FromDouble(angle);
}

/*static*/ PyObject *ObjectHandler::SetRectRotation(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_rect_rotation expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_rect_rotation expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_rotation got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pAngle = PyTuple_GetItem(args, 1);

	float angle = PyFloat_AsDouble(pAngle);

	rects.at(id)->setRotation(sf::Angle(sf::degrees(angle)));

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::RectRotate(PyObject *self, PyObject *args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.rect_rotate expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.rect_rotate expects a long and a float as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.rect_rotate got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pAngle = PyTuple_GetItem(args, 1);

	float angle = PyFloat_AsDouble(pAngle);

	rects.at(id)->rotate(sf::Angle(sf::degrees(angle)));

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetRectSize(PyObject *self,
													PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf(
			"engine.set_rect_size expects a long and a 2-tuple of floats as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf(
			"engine.set_rect_size expects a long and a 2-tuple of floats as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_size got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pSize = PyTuple_GetItem(args, 1);
	PyObject *pW = PyTuple_GetItem(pSize, 0);
	PyObject *pH = PyTuple_GetItem(pSize, 1);

	float w = (float)PyFloat_AsDouble(pW);
	float h = (float)PyFloat_AsDouble(pH);

	rects.at(id)->setSize({w,h});

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetRectOutlineThickness(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_rect_outline_thickness expects a long and a float as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_outline_thickness expects a long and a float as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_outline_thickness got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pThickness = PyTuple_GetItem(args, 1);

	double thick = PyFloat_AsDouble(pThickness);

	rects.at(id)->setOutlineThickness((float)thick);

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::SetRectOutlineColor(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_rect_outline_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_outline_color expects a long and a tuple as an "
			   "argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.set_rect_outline_color got a rect id out of range\n");
		PyErr_BadArgument();
	}

	PyObject *pColor = PyTuple_GetItem(args, 1);
	PyObject *pR = PyTuple_GetItem(pColor, 0);
	PyObject *pG = PyTuple_GetItem(pColor, 1);
	PyObject *pB = PyTuple_GetItem(pColor, 2);
	PyObject *pA = PyTuple_GetItem(pColor, 3);

	double r = PyFloat_AsDouble(pR);
	double g = PyFloat_AsDouble(pG);
	double b = PyFloat_AsDouble(pB);
	double a = PyFloat_AsDouble(pA);

	rects.at(id)->setOutlineColor(sf::Color(r, g, b, a));

	// Py_XDECREF(pId);
	// Py_XDECREF(pPosition);
	// Py_XDECREF(pX);
	// Py_XDECREF(pY);

	Py_RETURN_NONE;
}

/*static*/ PyObject *ObjectHandler::DrawRect(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.draw_rect expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	PyObject *pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId))
	{
		Py_XDECREF(pId);
		printf("engine.draw_rect expects a single long as an argument\n");
		PyErr_BadArgument();
	}

	long id = PyLong_AsLong(pId);

	if (rects.size() <= id || id < 0)
	{
		Py_XDECREF(pId);
		printf("engine.draw_rect got a sprite id out of range\n");
		PyErr_BadArgument();
	}

	object_window->draw(*rects.at(id));

	// Py_XDECREF(pId);

	Py_RETURN_NONE;
}

//// PHYSICS? ////

PyObject *ObjectHandler::CollidesWith(PyObject *self, PyObject *args)
{
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.collides_with expects a two ids as arguments\n");
		PyErr_BadArgument();
	}

	PyObject *pId1 = PyTuple_GetItem(args, 0);
	PyObject *pId2 = PyTuple_GetItem(args, 1);

	if (!PyLong_Check(pId1))
	{
		Py_XDECREF(pId1);
		printf("engine.collides_with expects a long and a long as an argument\n");
		PyErr_BadArgument();
	}

	if (!PyLong_Check(pId2))
	{
		Py_XDECREF(pId2);
		printf("engine.collides_with expects a long and a long as an argument\n");
		PyErr_BadArgument();
	}

	long id1 = PyLong_AsLong(pId1);
	long id2 = PyLong_AsLong(pId2);

	if (circles.size() <= id1)
	{
		Py_XDECREF(pId1);
		printf("engine.collides_with got a circle id out of range\n");
		PyErr_BadArgument();
	}

	if (circles.size() <= id2)
	{
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

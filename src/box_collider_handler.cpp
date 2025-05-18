#include "box_collider_handler.hpp"
#include <algorithm>
#include <iostream>

sf::RenderWindow *collider_window;
std::vector<BoxCollider *> box_colliders;
std::vector<long> free_box_colliders;

BoxColliderHandler::BoxColliderHandler(sf::RenderWindow *window)
{
    collider_window = window;
}

BoxColliderHandler::~BoxColliderHandler()
{
    std::for_each(box_colliders.begin(), box_colliders.end(), delete_ptr());
    box_colliders.clear();
}

/*static*/ std::vector<BoxCollider *> *BoxColliderHandler::GetBoxVector()
{
    return &box_colliders;
}

PyObject *BoxColliderHandler::createBoxCollider(PyObject *self, PyObject *args)
{
    long loc; // address in array to store box collider

    // parse python arguments
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2)
    {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }

    PyObject *pPos = PyTuple_GetItem(args, 0);
    Py_ssize_t pPos_nargs = PyTuple_GET_SIZE(pPos);
    if (pPos_nargs != 2)
    {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }

    PyObject *pSize = PyTuple_GetItem(args, 1);
    Py_ssize_t pSize_nargs = PyTuple_GET_SIZE(pSize);
    if (pPos_nargs != 2)
    {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }

    PyObject *pX = PyTuple_GetItem(pPos, 0);
    PyObject *pY = PyTuple_GetItem(pPos, 1);
    PyObject *pWidth = PyTuple_GetItem(pSize, 0);
    PyObject *pHeight = PyTuple_GetItem(pSize, 1);

    double x = PyFloat_AsDouble(pX);
    double y = PyFloat_AsDouble(pY);
    double width = PyFloat_AsDouble(pWidth);
    double height = PyFloat_AsDouble(pHeight);

    BoxCollider *temp_box_collider = new BoxCollider(sf::Vector2f(x, y), sf::Vector2f(width, height));

    if (!free_box_colliders.empty())
    {
        loc = free_box_colliders.back();
        free_box_colliders.pop_back();
        delete box_colliders.at(loc);
        box_colliders.at(loc) = temp_box_collider;
    }
    else
    {
        box_colliders.push_back(temp_box_collider);
        loc = box_colliders.size() - 1;
    }

    // std::clog << "Engine:\n\tcreateBoxCollider:\n\t\tCreating Box Collider at " << x << ", " << y << "\n\t\treturning " << loc << std::endl;
    return PyLong_FromLong(loc);
}

PyObject *BoxColliderHandler::freeBoxCollider(PyObject *self, PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1)
    {
        std::cerr << "engine.free_box_collider expects a single long as an argument\n"
                  << std::endl;
        PyErr_BadArgument();
    }

    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        std::cerr << "engine.free_box_collider expects a long as an argument\n"
                  << std::endl;
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        std::cerr << "engine.free_box_collider got a box id out of range\n"
                  << std::endl;
        PyErr_BadArgument();
    }

    // delete box_colliders[id];
    free_box_colliders.push_back(id);

    Py_RETURN_NONE;
}

/*static*/ PyObject *BoxColliderHandler::GetBoxPosition(PyObject *self,
                                                            PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.get_box_position expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.get_box_position expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (box_colliders.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.get_box_position got a box collider id out of range\n");
    PyErr_BadArgument();
  }

  sf::Vector2f position = box_colliders.at(id)->getPosition();

  PyObject *x = PyFloat_FromDouble(position.x);
  PyObject *y = PyFloat_FromDouble(position.y);

  PyObject *pPos = PyTuple_Pack(2, x, y);

  return pPos;
}

/*static*/ PyObject *BoxColliderHandler::SetBoxPosition(PyObject *self,
                                                            PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_box_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_box_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (box_colliders.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.set_box_position got a box collider id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 1);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  box_colliders.at(id)->setPosition((float)x, (float)y);

  Py_RETURN_NONE;
}

/*static*/ PyObject *BoxColliderHandler::GetBoxSize(PyObject *self,
                                                        PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1)
    {
        printf("engine.get_box_size expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        printf("engine.get_box_size expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        printf("engine.get_box_size got a box collider id out of range\n");
        PyErr_BadArgument();
    }

    sf::Vector2f position = box_colliders.at(id)->getSize();

    PyObject *w = PyFloat_FromDouble(position.x);
    PyObject *h = PyFloat_FromDouble(position.y);

    PyObject *pSize = PyTuple_Pack(2, w, h);

    return pSize;
}

/*static*/ PyObject *BoxColliderHandler::SetBoxSize(PyObject *self,
                                                        PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2)
    {
        printf("engine.set_box_size expects a long and a tuple as an "
               "argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        printf("engine.set_box_size expects a long and a tuple as an "
               "argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        printf("engine.set_box_size got a box collider id out of range\n");
        PyErr_BadArgument();
    }

    PyObject *pPosition = PyTuple_GetItem(args, 0);
    PyObject *pX = PyTuple_GetItem(pPosition, 0);
    PyObject *pY = PyTuple_GetItem(pPosition, 1);

    double x = PyFloat_AsDouble(pX);
    double y = PyFloat_AsDouble(pY);

    box_colliders.at(id)->setSize((float)x, (float)y);

    Py_RETURN_NONE;
}

/*static*/ PyObject *BoxColliderHandler::SetBoxCallback(PyObject *self, PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2)
    {
        printf("engine.set_box_callback expects a long and a function reference as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        printf("engine.set_box_callback expects a long and a function reference as "
               "arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        printf("engine.set_box_callback got a box collider id out of range\n");
        PyErr_BadArgument();
    }

    PyObject *pCallback = PyTuple_GetItem(args, 1);
    if (!PyCallable_Check(pCallback))
    {
        Py_XDECREF(pCallback);
        printf("engine.set_box_callback expects a long and a function reference as "
               "arguments\n");
        PyErr_BadArgument();
    }

    box_colliders.at(id)->SetCallback(pCallback);

    Py_RETURN_NONE;
}

/*static*/ PyObject *BoxColliderHandler::GetBoxTrigger(PyObject *self,
                                                       PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1)
    {
        printf(
            "engine.get_box_trigger expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        printf(
            "engine.get_box_trigger expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        printf("engine.get_box_trigger got a box collider id out of range\n");
        PyErr_BadArgument();
    }

    // Py_XDECREF(pId);

    if (box_colliders.at(id)->isTrigger)
    {
        Py_RETURN_TRUE;
    }

    Py_RETURN_FALSE;
}

/*static*/ PyObject *BoxColliderHandler::SetBoxTrigger(PyObject *self,
                                                       PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2)
    {
        printf("engine.set_box_trigger expects a single long and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId))
    {
        Py_XDECREF(pId);
        printf("engine.set_box_trigger expects a single long and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pB = PyTuple_GetItem(args, 1);
    if (!PyBool_Check(pB))
    {
        Py_XDECREF(pB);
        printf("engine.set_box_trigger expects a single long and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    long b = PyLong_AsLong(pB);

    if (box_colliders.size() <= id || 0 > id)
    {
        Py_XDECREF(pId);
        Py_XDECREF(pB);
        printf("engine.set_box_trigger got a box collider id out of range\n");
        PyErr_BadArgument();
    }

    box_colliders.at(id)->isTrigger = (bool)b;

    Py_RETURN_NONE;
}

/*static*/ PyObject *BoxColliderHandler::DrawBox(PyObject *self,
                                                             PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.draw_box expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.draw_box expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (box_colliders.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf(
        "engine.draw_box got a box collider id out of range\n");
    PyErr_BadArgument();
  }

  box_colliders.at(id)->Draw(collider_window);

  Py_RETURN_NONE;
}

bool BoxColliderHandler::isBoxColliderIDInRange(long id)
{
    return 0 <= id && id < box_colliders.size();
}

BoxCollider *BoxColliderHandler::getBoxCollider(long id)
{
    return box_colliders.at(id);
}

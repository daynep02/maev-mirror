#include "camera_handler.hpp"

#include <iostream>

sf::View* g_camera;
sf::RenderWindow* camera_window;

CameraHandler::CameraHandler(sf::RenderWindow* window) {
    g_camera = new sf::View(sf::Vector2f(400.f, 250.f), sf::Vector2f(1024.f, 640.f));
    camera_window = window;
}

CameraHandler::~CameraHandler() {
    delete g_camera;
}

PyObject* CameraHandler::SetPosition(PyObject* self, PyObject* args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        std::cerr << "engine.set_camera_position expects a tuple of size 2 as an argument - no enough arguments\n" << std::endl;
        PyErr_BadArgument();
    }

    PyObject* pCPos = PyTuple_GetItem(args, 0);
    Py_ssize_t pCPos_nargs = PyTuple_GET_SIZE(pCPos);
    if (pCPos_nargs != 2) {
        std::cerr << "engine.set_camera_position expects a tuple of size 2 as an argument - tuple doesn;t have the right length\n" << std::endl;
        PyErr_BadArgument();
    }

    PyObject* pX = PyTuple_GetItem(pCPos, 0);
    PyObject* pY = PyTuple_GetItem(pCPos, 1);

    if (!PyFloat_Check(pX) && !PyLong_Check(pX)) {
        Py_XDECREF(pX);
        std::cerr << "engine.set_camera_position expects a tuple of size 2 as an argument - x isn't a float\n" << std::endl;
        PyErr_BadArgument();
    }

    if (!PyFloat_Check(pY) && !PyLong_Check(pY)) {
        Py_XDECREF(pY);
        std::cerr << "engine.set_camera_position expects a tuple of size 2 as an argument - y isn't a float\n" << std::endl;
        PyErr_BadArgument();
    }

    float x = (float)PyFloat_AsDouble(pX);
    float y = (float)PyFloat_AsDouble(pY);

    // std::cout << x << " " << y << std::endl;
    g_camera->setCenter({x, y});
    camera_window->setView(*g_camera);
      // g_camera = new sf::View(sf::Vector2f(400.f, 250.f), sf::Vector2f(1024.f, 640.f));

    Py_RETURN_NONE;
}

PyObject* CameraHandler::SetSize(PyObject* self, PyObject* args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        std::cerr << "engine.set_camera_size expects a tuple of size 2 as an argument - no enough arguments\n" << std::endl;
        PyErr_BadArgument();
    }

    PyObject* pCPos = PyTuple_GetItem(args, 0);
    Py_ssize_t pCPos_nargs = PyTuple_GET_SIZE(pCPos);
    if (pCPos_nargs != 2) {
        std::cerr << "engine.set_camera_size expects a tuple of size 2 as an argument - tuple doesn;t have the right length\n" << std::endl;
        PyErr_BadArgument();
    }

    PyObject* pX = PyTuple_GetItem(pCPos, 0);
    PyObject* pY = PyTuple_GetItem(pCPos, 1);

    if (!PyFloat_Check(pX) && !PyLong_Check(pX)) {
        Py_XDECREF(pX);
        std::cerr << "engine.set_camera_size expects a tuple of size 2 as an argument - x isn't a float\n" << std::endl;
        PyErr_BadArgument();
    }

    if (!PyFloat_Check(pY) && !PyLong_Check(pY)) {
        Py_XDECREF(pY);
        std::cerr << "engine.set_camera_size expects a tuple of size 2 as an argument - y isn't a float\n" << std::endl;
        PyErr_BadArgument();
    }

    float x = (float)PyFloat_AsDouble(pX);
    float y = (float)PyFloat_AsDouble(pY);

    g_camera->setSize({x, y});
    camera_window->setView(*g_camera);

    Py_RETURN_NONE;
}
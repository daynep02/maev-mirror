#include "box_collider_handler.hpp"
#include <algorithm>
#include <iostream>

sf::RenderWindow* _window;
std::vector<BoxCollider*> box_colliders;
std::vector<long> free_box_colliders;

BoxColliderHandler::BoxColliderHandler(sf::RenderWindow* window) {
    _window = window;
}

BoxColliderHandler::~BoxColliderHandler() {
    std::for_each(box_colliders.begin(), box_colliders.end(), delete_ptr());
    box_colliders.clear();
}

PyObject* BoxColliderHandler::createBoxCollider(PyObject* self, PyObject* args) {
    long loc; // address in array to store box collider

    //parse python arguments
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }

    PyObject* pPos = PyTuple_GetItem(args, 0);
    Py_ssize_t pPos_nargs = PyTuple_GET_SIZE(pPos);
    if (pPos_nargs != 2) {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }
    
    PyObject* pSize = PyTuple_GetItem(args, 1);
    Py_ssize_t pSize_nargs = PyTuple_GET_SIZE(pSize);
    if (pPos_nargs != 2) {
        printf("engine.create_box_collider expects a two tuples of size 2 as an argument\n");
        PyErr_BadArgument();
    }

    PyObject* pX = PyTuple_GetItem(pPos, 0);
    PyObject* pY = PyTuple_GetItem(pPos, 1);
    PyObject* pWidth = PyTuple_GetItem(pSize, 0);
    PyObject* pHeight = PyTuple_GetItem(pSize, 1);

    double x = PyFloat_AsDouble(pX);
    double y = PyFloat_AsDouble(pY);
    double width = PyFloat_AsDouble(pWidth);
    double height = PyFloat_AsDouble(pHeight);

    BoxCollider* temp_box_collider = new BoxCollider(sf::Vector2f(x, y), sf::Vector2f(width, height));

    if (!free_box_colliders.empty()) {
        loc = free_box_colliders.back();
        free_box_colliders.pop_back();
        box_colliders[loc] = temp_box_collider;
    } else {
        loc = box_colliders.size();
        box_colliders.push_back(temp_box_collider);
    }


    std::clog << "Engine:\n\tcreateBoxCollider:\n\t\tCreating Box Collider at " << x << ", " << y << "\n\t\treturning " << loc << std::endl;
    return PyLong_FromLong(loc);
}

PyObject* BoxColliderHandler::freeBoxCollider(PyObject* self, PyObject* args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
		std::cerr << "engine.free_box_collider expects a single long as an argument\n" << std::endl;
		PyErr_BadArgument();
	}

    PyObject* pId = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pId)) {
		Py_XDECREF(pId);
		std::cerr << "engine.free_box_collider expects a long as an argument\n" << std::endl;
		PyErr_BadArgument();
	}

    long id = PyLong_AsLong(pId);

    if(box_colliders.size()<=id) {
        Py_XDECREF(pId);
		std::cerr << "engine.free_sprite got a sprite id out of range\n" << std::endl;
		PyErr_BadArgument();
    }

    delete box_colliders[id];
    free_box_colliders.push_back(id);

    Py_RETURN_NONE;
}
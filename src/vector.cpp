#include "vector.h"
#include <vector>
#include <cmath>

std::vector<sf::Vector2<float>*> vectors;

// Makes either empty or x, y Vector based on whether or not arguments are given
PyObject* Vector::create_vector(PyObject* self, PyObject* args) {
	long id = -1;
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs == 0) {
		printf("engine.create_vector: Creating Vector of 0 0\n");
		vectors.push_back(new sf::Vector2f());
		id = vectors.size() - 1;
	}
	else if (nargs == 2) {
		// obtain argument contents
		PyObject* xo = PyTuple_GetItem(args, 0);
		PyObject* yo = PyTuple_GetItem(args, 1);

		float x = PyFloat_AsDouble(xo);
		float y = PyFloat_AsDouble(yo);
		
		printf("engine.create_vector: Creating Vector of %f %f\n", x, y);
		vectors.push_back(new sf::Vector2f(x, y));
		id = vectors.size() - 1;
	}
	else {
		printf("engine.create_vector expects either two ints/floats or no arguments");
		PyErr_BadArgument();
	}

	return PyLong_FromLong(id);
}

// Returns length of vector
PyObject* Vector::length(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1) {
		printf("engine.length expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);

	long id = PyLong_AsLong(ido);
	
	// return length
	sf::Vector2<float> v = *(vectors.at(id));

	printf("engine.length: returning length\n");
	return PyFloat_FromDouble((v.length()));
}

// Returns normalized version of vector
PyObject* Vector::normalize(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1) {
		printf("engine.length expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);

	long id = PyLong_AsLong(ido);
	
	// obtain new normalized vector
	sf::Vector2<float> v = ((*(vectors.at(id))).normalized());
	
	vectors.push_back(new sf::Vector2f(v.x, v.y));
	id = vectors.size() - 1;

	printf("engine.normalize: returning normalized Vector\n");
	return PyLong_FromLong(id);
}


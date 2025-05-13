#include "vector.h"
#include <vector>
#include <cmath>

std::vector<sf::Vector2<float>*> vectors;

// Makes either empty or x, y Vector based on whether or not arguments are given
PyObject* Vector::create_vector(PyObject* self, PyObject* args) {
	long id = -1;
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs == 0) {
		//printf("engine.create_vector: Creating Vector of 0 0\n");
		vectors.push_back(new sf::Vector2f());
		id = vectors.size() - 1;
	}
	else if (nargs == 2) {
		// obtain argument contents
		PyObject* xo = PyTuple_GetItem(args, 0);
		PyObject* yo = PyTuple_GetItem(args, 1);

		float x = PyFloat_AsDouble(xo);
		float y = PyFloat_AsDouble(yo);
		
		//printf("engine.create_vector: Creating Vector of %f %f\n", x, y);
		vectors.push_back(new sf::Vector2f(x, y));
		id = vectors.size() - 1;
	}
	else {
		printf("engine.create_vector expects either two ints/floats or no arguments");
		PyErr_BadArgument();
	}

	return PyLong_FromLong(id);
}

// Destroys Vector of given id so as to not infinitely hold onto every Vector that literally ever existed
PyObject* Vector::destroy_vector(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1) {
		printf("engine.destroy_vector expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);

	long id = PyLong_AsLong(ido);

	vectors.erase(vectors.begin() + id);
	Py_RETURN_NONE;
}

// Destroys all Vectors currently being held so as to not infinitely hold onto every Vector that literally ever existed
PyObject* Vector::cleanse_vectors(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 0) {
		printf("engine.cleanse_vectors takes no arguments\n");
		PyErr_BadArgument();
	}

	std::vector<sf::Vector2<float>*>().swap(vectors);   // like vectors.clear(), but guarantees reallocating
	Py_RETURN_NONE;
}

// converts a vector found or made elsewhere in engine to Vector2f and places into the vector of Vectors
long Vector::convert_vector(sf::Vector2i vec) {
	long id = -1;
	vectors.push_back(new sf::Vector2f(vec.x, vec.y));
	id = vectors.size() - 1;
	return id;
}

long Vector::convert_vector(sf::Vector2u vec) {
	long id = -1;
	vectors.push_back(new sf::Vector2f(vec.x, vec.y));
	id = vectors.size() - 1;
	return id;
}

// Returns current x value of vector
PyObject* Vector::x(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1) {
		printf("engine.length expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);

	long id = PyLong_AsLong(ido);

	return PyFloat_FromDouble((*(vectors.at(id))).x);
}

// Returns current y value of vector
PyObject* Vector::y(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1) {
		printf("engine.length expects a single long as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);

	long id = PyLong_AsLong(ido);
	
	return PyFloat_FromDouble((*(vectors.at(id))).y);
}

// Adds scalar value to Vector
PyObject* Vector::scaAdd(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects a single long and a single float as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);
	PyObject* so = PyTuple_GetItem(args, 1);

	long id = PyLong_AsLong(ido);
	float s = PyFloat_AsDouble(so);
	
	(*(vectors.at(id))).x += s; 
	(*(vectors.at(id))).y += s;

	return PyLong_FromLong(id);
}

// Subtracts scalar value to Vector
PyObject* Vector::scaSub(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects a single long and a single float as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);
	PyObject* so = PyTuple_GetItem(args, 1);

	long id = PyLong_AsLong(ido);
	float s = PyFloat_AsDouble(so);
	
	(*(vectors.at(id))).x -= s; 
	(*(vectors.at(id))).y -= s;

	return PyLong_FromLong(id);
}

// Multiplies scalar value to Vector
PyObject* Vector::scaMul(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects a single long and a single float as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);
	PyObject* so = PyTuple_GetItem(args, 1);

	long id = PyLong_AsLong(ido);
	float s = PyFloat_AsDouble(so);
	
	(*(vectors.at(id))).x *= s; 
	(*(vectors.at(id))).y *= s;

	return PyLong_FromLong(id);
}

// Divides scalar value to Vector
PyObject* Vector::scaDiv(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects a single long and a single float as an argument\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* ido = PyTuple_GetItem(args, 0);
	PyObject* so = PyTuple_GetItem(args, 1);

	long id = PyLong_AsLong(ido);
	float s = PyFloat_AsDouble(so);
	
	(*(vectors.at(id))).x /= s; 
	(*(vectors.at(id))).y /= s;

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

	//printf("engine.length: returning length\n");
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

	//printf("engine.normalize: returning normalized Vector\n");
	return PyLong_FromLong(id);
}

// Adds Vector to Vector
PyObject* Vector::vecAdd(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects two longs as arguments\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* id1o = PyTuple_GetItem(args, 0);
	PyObject* id2o = PyTuple_GetItem(args, 1);

	long id1 = PyLong_AsLong(id1o);
	float id2 = PyFloat_AsDouble(id2o);
	
	(*(vectors.at(id1))) += (*(vectors.at(id2)));

	return PyLong_FromLong(id1);
}

// Subtracts Vector to Vector
PyObject* Vector::vecSub(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.vec_add expects two longs as arguments\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* id1o = PyTuple_GetItem(args, 0);
	PyObject* id2o = PyTuple_GetItem(args, 1);

	long id1 = PyLong_AsLong(id1o);
	float id2 = PyFloat_AsDouble(id2o);
	
	(*(vectors.at(id1))) -= (*(vectors.at(id2)));

	return PyLong_FromLong(id1);
}

// Returns dot product of two vectors
PyObject* Vector::dot(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.dot expects two longs as arguments\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* id1o = PyTuple_GetItem(args, 0);
	PyObject* id2o = PyTuple_GetItem(args, 1);
	
	long id1 = PyLong_AsLong(id1o);
	long id2 = PyLong_AsLong(id2o);

	// calculate dot product
	float d = (*(vectors.at(id1))).dot((*(vectors.at(id2))));

	//printf("engine.dot: returning dot product of two Vectors\n");
	return PyFloat_FromDouble(d);
}

PyObject* Vector::cross(PyObject* self, PyObject* args) {
	Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2) {
		printf("engine.cross expects two longs as arguments\n");
		PyErr_BadArgument();
	}
	// obtain argument contents
	PyObject* id1o = PyTuple_GetItem(args, 0);
	PyObject* id2o = PyTuple_GetItem(args, 1);
	
	long id1 = PyLong_AsLong(id1o);
	long id2 = PyLong_AsLong(id2o);

	// calculate dot product
	float d = (*(vectors.at(id1))).cross((*(vectors.at(id2))));

	//printf("engine.cross: returning cross product of two Vectors\n");
	return PyFloat_FromDouble(d);
}


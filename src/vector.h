#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

class Vector {
	public:
	// Constructor
	static PyObject* create_vector(PyObject* self, PyObject* args);

	// Attributes
	static PyObject* x(PyObject* self, PyObject* args);
	static PyObject* y(PyObject* self, PyObject* args);

	// Intra-Vector methods
	static PyObject* length(PyObject* self, PyObject* args);
	static PyObject* normalize(PyObject* self, PyObject* args);

	// Extra-Vector methods
	static PyObject* dot(PyObject* self, PyObject* args);
	static PyObject* cross(PyObject* self, PyObject* args);
};


// Vectorf Docs
PyDoc_STRVAR(
	create_vector_doc,
	".. function:: create_vector()\n"
	"\n"
	"  Creates a linear algebra vector that handles integer and floating point types."
	"\n"
	"  :return: Nothing."
);

PyDoc_STRVAR(
	length_doc,
	".. function:: length(long id)\n"
	"\n"
	"  Calculates and returns the magnitude of a Vector given its id. Can be seen as a given Vector's absolute length."
	"\n"
	"  :return: A given Vector's magnitude as a double type."
);

PyDoc_STRVAR(
	normalize_doc,
	".. function:: normalize(long id)\n"
	"\n"
	"  Calculates and returns the normalized version of a Vector given its id."
	"\n"
	"  :return: a new Vector."
);

PyDoc_STRVAR(
	dot_doc,
	".. function:: dot(long id, long id)\n"
	"\n"
	"  Calculates and returns the dot product of two Vectors given their ids."
	"\n"
	"  :return: two given Vector's dot product result as a double type."
);

PyDoc_STRVAR(
	cross_doc,
	".. function:: cross(long id, long id)\n"
	"\n"
	"  Calculates and returns the cross product of two Vectors given their ids."
	"\n"
	"  :return: two given Vector's cross product result as a double type."
);

static PyMethodDef createVector = {"create_vector", Vector::create_vector, METH_VARARGS, create_vector_doc};
static PyMethodDef x = {"x", Vector::x, METH_VARARGS, length_doc};
static PyMethodDef y = {"y", Vector::y, METH_VARARGS, length_doc};
static PyMethodDef length = {"length", Vector::length, METH_VARARGS, length_doc};
static PyMethodDef normalize = {"normalize", Vector::normalize, METH_VARARGS, normalize_doc};
static PyMethodDef dot = {"dot", Vector::dot, METH_VARARGS, dot_doc};
static PyMethodDef cross = {"cross", Vector::cross, METH_VARARGS, cross_doc};

#endif // _VECTOR_H_

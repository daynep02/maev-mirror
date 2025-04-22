#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

class Vector {
	public:
	// Constructors / Destructors
	static PyObject* create_vector(PyObject* self, PyObject* args);
	static PyObject* length(PyObject* self, PyObject* args);
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
	".. function:: length()\n"
	"\n"
	"  Calculates and returns the magnitude of a given Vector. Can be seen as a given Vector's absolute length."
	"\n"
	"  :return: A given Vector's magnitude as a double type."
);

PyDoc_STRVAR(
	engine_get_normalize_doc,
	".. function:: normalize(Vectorf& v)\n"
	"\n"
	"  Calculates and return's the normalized version of a given Vectorf."
	"\n"
	"  :return: a new Vectorf."
);

static PyMethodDef createVector = {"create_vector", Vector::create_vector, METH_VARARGS, create_vector_doc};
static PyMethodDef length = {"length", Vector::length, METH_VARARGS, length_doc};
//static PyMethodDef createVector = {"create_vector", Vectorf::create_vector, METH_VARARGS, create_vector_doc};

#endif // _VECTOR_H_

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

class Vector {
	public:
	// Constructors, destructors, etc.
	static PyObject* create_vector(PyObject* self, PyObject* args);
	static PyObject* destroy_vector(PyObject* self, PyObject* args);
	static PyObject* cleanse_vectors(PyObject* self, PyObject* args);

	static long convert_vector(sf::Vector2i vector);
	static long convert_vector(sf::Vector2u vector);

	// Attributes
	static PyObject* x(PyObject* self, PyObject* args);
	static PyObject* y(PyObject* self, PyObject* args);

	// Intra-Vector methods
	// TODO: add draw?
	static PyObject* scaAdd(PyObject* self, PyObject* args);
	static PyObject* scaSub(PyObject* self, PyObject* args);
	static PyObject* scaMul(PyObject* self, PyObject* args);
	static PyObject* scaDiv(PyObject* self, PyObject* args);
	
	static PyObject* length(PyObject* self, PyObject* args);
	static PyObject* normalize(PyObject* self, PyObject* args);

	// Inter-Vector methods
	// TODO: add intersection
	static PyObject* vecAdd(PyObject* self, PyObject* args);
	static PyObject* vecSub(PyObject* self, PyObject* args);
	
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
	"  :return: a single long, the id of the created Vector."
);

PyDoc_STRVAR(
	destroy_vector_doc,
	".. function:: destroy_vector()\n"
	"\n"
	"  Destroys a singular Vector that has already been created."
	"\n"
	"  :return: Nothing."
);

PyDoc_STRVAR(
	cleanse_vectors_doc,
	".. function:: cleanse_vectors()\n"
	"\n"
	"  Destroys all Vectors that have been created."
	"\n"
	"  :return: Nothing."
);

PyDoc_STRVAR(
	x_doc,
	".. function:: x(long id)\n"
	"\n"
	"  Returns the x value of the Vector of a given id."
	"\n"
	"  :return: a single float, the x value of the Vector."
);

PyDoc_STRVAR(
	y_doc,
	".. function:: y(long id)\n"
	"\n"
	"  Returns the y value of the Vector of a given id."
	"\n"
	"  :return: a single float, the y value of the Vector."
);

PyDoc_STRVAR(
	add_doc,
	".. function:: scaAdd(long id, float s)\n"
	"\n"
	"  Performs addition of scalar value s to the Vector of a given id."
	"\n"
	"  :return: The id of the resulting Vector after the operation."
);

PyDoc_STRVAR(
	sub_doc,
	".. function:: scaSub(long id, float s)\n"
	"\n"
	"  Performs subtraction of scalar value s to the Vector of a given id."
	"\n"
	"  :return: The id of the resulting Vector after the operation."
);

PyDoc_STRVAR(
	mul_doc,
	".. function:: scaMul(long id, float s)\n"
	"\n"
	"  Performs multiplication of scalar value s to the Vector of a given id."
	"\n"
	"  :return: The id of the resulting Vector after the operation."
);

PyDoc_STRVAR(
	div_doc,
	".. function:: scaDiv(long id, float s)\n"
	"\n"
	"  Performs division of scalar value s to the Vector of a given id."
	"\n"
	"  :return: The id of the resulting Vector after the operation."
);

PyDoc_STRVAR(
	length_doc,
	".. function:: length(long id)\n"
	"\n"
	"  Calculates and returns the magnitude of a Vector given its id. Can be seen as a given Vector's absolute length."
	"\n"
	"  :return: A single float, the Vector of a given id's magnitude."
);

PyDoc_STRVAR(
	normalize_doc,
	".. function:: normalize(long id)\n"
	"\n"
	"  Calculates and returns the normalized version of a Vector given its id."
	"\n"
	"  :return: the id of the resulting Vector."
);

PyDoc_STRVAR(
	vec_add_doc,
	".. function:: vecAdd(long id, float s)\n"
	"\n"
	"  Performs addition of a Vector of a given id to another Vector of a given id."
	"\n"
	"  :return: The id of the first given Vector after the operation."
);

PyDoc_STRVAR(
	vec_sub_doc,
	".. function:: vecSub(long id, float s)\n"
	"\n"
	"  Performs subtraction of a Vector of a given id to another Vector of a given id."
	"\n"
	"  :return: The id of the first given Vector after the operation."
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
static PyMethodDef destroyVector = {"destroy_vector", Vector::destroy_vector, METH_VARARGS, destroy_vector_doc};
static PyMethodDef cleanseVectors = {"cleanse_vectors", Vector::cleanse_vectors, METH_VARARGS, cleanse_vectors_doc};
static PyMethodDef x = {"x", Vector::x, METH_VARARGS, x_doc};
static PyMethodDef y = {"y", Vector::y, METH_VARARGS, y_doc};
static PyMethodDef sca_add = {"sca_add", Vector::scaAdd, METH_VARARGS, add_doc};
static PyMethodDef sca_sub = {"sca_sub", Vector::scaSub, METH_VARARGS, sub_doc};
static PyMethodDef sca_mul = {"sca_mul", Vector::scaMul, METH_VARARGS, mul_doc};
static PyMethodDef sca_div = {"sca_div", Vector::scaDiv, METH_VARARGS, div_doc};
static PyMethodDef length = {"length", Vector::length, METH_VARARGS, length_doc};
static PyMethodDef normalize = {"normalize", Vector::normalize, METH_VARARGS, normalize_doc};
static PyMethodDef vec_add = {"vec_add", Vector::vecAdd, METH_VARARGS, vec_add_doc};
static PyMethodDef vec_sub = {"vec_sub", Vector::vecSub, METH_VARARGS, vec_sub_doc};
static PyMethodDef dot = {"dot", Vector::dot, METH_VARARGS, dot_doc};
static PyMethodDef cross = {"cross", Vector::cross, METH_VARARGS, cross_doc};

#endif // _VECTOR_H_

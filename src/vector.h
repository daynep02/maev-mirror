#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

// Class Definition
class Vectori {
	public:
	// Constructors / Destructors
	explicit Vectori();
	explicit Vectori(int x, int y);
	~Vectori();

	// Magnitude
	Vectori& operator *= (int s);
	Vectori& operator /= (int s);
	inline Vectori operator * (int s);
	inline Vectori operator / (int s);
	inline Vectori operator - ();
	inline float magnitude(const Vectori& v) const;
	inline Vectori normalize(Vectori& v);

	private:
	int x;
	int y;
};

class Vectorf {
	public:
	// Constructors / Destructors
	static PyObject* create_vector(PyObject* self, PyObject* args);
	explicit Vectorf();
	explicit Vectorf(float x, float y);
	~Vectorf();

	// Accessors
	//float& operator [] (int i);
	//const float& operator [] (int i) const;

	// Magnitude
	Vectorf& operator *= (float s);
	Vectorf& operator /= (float s);
	inline Vectorf operator * (float s);
	inline Vectorf operator / (float s);
	inline Vectorf operator - ();
	inline float magnitude(const Vectorf& v) const;
	inline Vectorf normalize(Vectorf& v);
	
	private:
	float x;
	float y;
};


// Vectorf Docs
PyDoc_STRVAR(
	create_vector_doc,
	".. function:: create_vectorf()\n"
	"\n"
	"  Creates a linear algebra vector that handles floating point types."
	"\n"
	"  :return: Nothing."
);

PyDoc_STRVAR(
	engine_get_magnitude_doc,
	".. function:: magnitude(const Vectorf& v) const\n"
	"\n"
	"  Calculates and returns the magnitude of a given Vectorf. Can be seen as a given Vectorf's absolute length."
	"\n"
	"  :return: A given Vectorf's magnitude as a floating point type."
);

PyDoc_STRVAR(
	engine_get_normalize_doc,
	".. function:: normalize(Vectorf& v)\n"
	"\n"
	"  Calculates and return's the normalized version of a given Vectorf."
	"\n"
	"  :return: a new Vectorf."
);

static PyMethodDef createVector = {"create_vector", Vectorf::create_vector,
				METH_VARARGS, create_vector_doc};

#endif // _VECTOR_H_

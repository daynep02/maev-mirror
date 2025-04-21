#include <cmath>
#include "vector.h"

///////////////////////////////////////////
// Constructors
Vectori::Vectori() = default;

Vectori::Vectori(int x, int y) {
	this->x = x;
	this->y = y;
}

// Destructor
Vectori::~Vectori() = default;

// Magnitude
Vectori& Vectori::operator *= (int s) {
	this->x *= s;
	this->y *= s;
	return *this;
}

Vectori& Vectori::operator /= (int s) {
	s = 1.0F / s;
	this->x *= s;
	this->y *= s;
	return *this;
}

Vectori Vectori::operator * (int s) {
	return (Vectori(this->x * s, this->y * s));
}

Vectori Vectori::operator / (int s) {
	s = 1.0F / s;
	return (Vectori(this->x * s, this->y * s));
}

// negative
Vectori Vectori::operator - () {
	return (Vectori(-this->x, -this->y));
}

float Vectori::magnitude(const Vectori& v) const {
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

Vectori Vectori::normalize(Vectori& v) {
	return (v / magnitude(v));
}

///////////////////////////////////////////
// Constructors
PyObject* Vectorf::createVector(PyObject* self, PyObject* args) {
	Py_RETURN_NONE;
}

Vectorf::Vectorf() = default;

Vectorf::Vectorf(float x, float y) {
	this->x = x;
	this->y = y;
}

// Destructor
Vectorf::~Vectorf() = default;

// Accessors
//float& operator [] (int i) {
//	return ((this->x) [i]);
//}

//const float& operator [] (int i) const {
//	return ((this->x) [i]);
//}

// Magnitude
Vectorf& Vectorf::operator *= (float s) {
	this->x *= s;
	this->y *= s;
	return *this;
}

Vectorf& Vectorf::operator /= (float s) {
	s = 1.0F / s;
	this->x *= s;
	this->y *= s;
	return *this;
}

Vectorf Vectorf::operator * (float s) {
	return (Vectorf(this->x * s, this->y * s));
}

Vectorf Vectorf::operator / (float s) {
	s = 1.0F / s;
	return (Vectorf(this->x * s, this->y * s));
}

// negative
Vectorf Vectorf::operator - () {
	return (Vectorf(-this->x, -this->y));
}

float Vectorf::magnitude(const Vectorf& v) const {
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

Vectorf Vectorf::normalize(Vectorf& v) {
	return (v / magnitude(v));
}

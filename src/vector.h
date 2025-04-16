#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

// Class Definition
class Vector {
	public:
	// Constructors / Destructors
	explicit Vector();
	explicit Vector(int x, int y);
	~Vector();

	private:
	int x;
	int y;
};

//PyDoc_STRVAR(
//	engine_
//);

#endif // _VECTOR_H_

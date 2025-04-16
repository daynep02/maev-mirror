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



//PyDoc_STRVAR(
//	engine_
//);

#endif // _VECTOR_H_

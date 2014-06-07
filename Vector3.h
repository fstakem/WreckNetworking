#ifndef VECTOR3_H
#define VECTOR3_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Vector3
	|||||  By:			Fred Stakem
	|||||  Date:		12.16.09
*/

#include <string>
#include "Core.h"

class Vector3
{
public:
	real x;
	real y;
	real z;

private:
	real pad;

public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

	void invert();
	real magnitude() const;
	real squareMagnitude() const;
	void normalize();
	void operator *=(const real value);
	Vector3 operator *(const real value) const;
	void operator +=(const Vector3& otherVector);
	Vector3 operator +(const Vector3& otherVector)const;
	void operator -=(const Vector3& otherVector);
	Vector3 operator -(const Vector3& otherVector) const;
	void addScaledVector(const Vector3& otherVector, real scale);
	void componentProductUpdate(const Vector3& otherVector);
	Vector3 componentProduct(const Vector3& otherVector) const;
	real dotProduct(const Vector3& otherVector) const;
	real operator *(const Vector3& otherVector) const;
	void operator %=(const Vector3& otherVector);
	Vector3 operator %(const Vector3& otherVector) const;
	Vector3 crossProduct(const Vector3& otherVector) const;
	std::string toString() const;
	std::string toString(const std::string delimiter) const;
};

#endif
#include "Vector3.h"
#include <sstream>

void Vector3::invert()
{
	this->x = -x;
	this->y = -y;
	this->z = -z;
}

real Vector3::magnitude() const
{
	return real_sqrt(this->x * this->x + 
					 this->y * this->y +
					 this->z * this->z);
}

real Vector3::squareMagnitude() const
{
	return this->x * this->x +
		   this->y * this->y +
		   this->z * this->z;
}

void Vector3::normalize()
{
	real mag = this->magnitude();
	if(mag > 0)
	{
		(*this) *= ((real)1) / mag;
	}
}

void Vector3::operator *=(const real value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
}

Vector3 Vector3::operator *(const real value) const
{
	return Vector3(this->x * value, this->y * value, this->z * value);
}

void Vector3::operator +=(const Vector3& otherVector)
{
	this->x += otherVector.x;
	this->y += otherVector.y;
	this->z += otherVector.z;
}

Vector3 Vector3::operator +(const Vector3& otherVector) const
{
	return Vector3(this->x + otherVector.x, 
				   this->y + otherVector.y, 
				   this->z + otherVector.z);
}

void Vector3::operator -=(const Vector3& otherVector)
{
	this->x -= otherVector.x;
	this->y -= otherVector.y;
	this->z -= otherVector.z;
}

Vector3 Vector3::operator -(const Vector3& otherVector) const
{
	return Vector3(this->x - otherVector.x,
				   this->y - otherVector.y,
				   this->z - otherVector.z);
}

void Vector3::addScaledVector(const Vector3& otherVector, real scale)
{
	this->x += otherVector.x * scale;
	this->y += otherVector.y * scale;
	this->z += otherVector.z * scale;
}

void Vector3::componentProductUpdate(const Vector3& otherVector)
{
	this->x *= otherVector.x;
	this->y *= otherVector.y;
	this->z *= otherVector.z;
}

Vector3 Vector3::componentProduct(const Vector3& otherVector) const
{
	return Vector3(this->x * otherVector.x, 
				   this->y * otherVector.y,
				   this->z * otherVector.z);
}

real Vector3::dotProduct(const Vector3& otherVector) const
{
	return this->x * otherVector.x + 
		   this->y * otherVector.y +
		   this->z * otherVector.z;
}

real Vector3::operator *(const Vector3& otherVector) const
{
	return this->x * otherVector.x + 
		   this->y * otherVector.y +
		   this->z * otherVector.z;
}

void Vector3::operator %=(const Vector3& otherVector)
{
	*this = this->crossProduct(otherVector);
}

Vector3 Vector3::operator %(const Vector3& otherVector) const
{
	return Vector3(this->y * otherVector.z - this->z * otherVector.y,
				   this->z * otherVector.x - this->x * otherVector.z,
				   this->x * otherVector.y - this->y * otherVector.x);
}

Vector3 Vector3::crossProduct(const Vector3& otherVector) const
{
	return Vector3(this->y * otherVector.z - this->z * otherVector.y,
				   this->z * otherVector.x - this->x * otherVector.z,
				   this->x * otherVector.y - this->y * otherVector.x);
}

std::string Vector3::toString() const
{
	std::stringstream stream;
	stream << this->x << " " << this->y << " " << this->z;
	return stream.str();
}

std::string Vector3::toString(const std::string delimiter) const
{
	std::stringstream stream;
	stream << this->x << delimiter << this->y << delimiter << this->z;
	return stream.str();
}
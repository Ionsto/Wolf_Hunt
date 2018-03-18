#pragma once
#include <math.h>
namespace Sim {
	template<class type>
	class Vector
	{
	public:
		type X, Y, Z;
		Vector(type x = 0, type y = 0, type z = 0);
		~Vector();
		inline Vector operator+(const Vector& other);
		inline void operator+=(const Vector&  other);
		inline void operator-=(const Vector&  other);
		inline Vector operator-(const Vector&  other);
		inline Vector operator*(float val);
		inline Vector operator/(float val);
		inline float Dot(const Vector& other);
		inline float DotXY(const Vector& other);
		inline Vector Normalise();
		//Strict equality
		inline bool operator!=(const Vector&  check);
		inline bool operator==(const Vector&  check);
	};
};
template<class type>
Sim::Vector<type>::Vector(type x, type y, type z)
{
	X = x;
	Y = y;
	Z = z;
}


template<class type>
Sim::Vector<type>::~Vector()
{
}

template<class type>
float Sim::Vector<type>::Dot(const Vector<type> & other)
{
	return (X * other.X) + (Y * other.Y) + (Z * other.Z);
}

template<class type>
float Sim::Vector<type>::DotXY(const Vector<type> & other)
{
	return (X * other.X) + (Y * other.Y);
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::Normalise()
{
	float mag = sqrtf(this->Dot(*this));
	return *this / mag;
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::operator+(const Vector<type> & other)
{
	return Vector(X + other.X, Y + other.Y, Z + other.Z);
}

template<class type>
void Sim::Vector<type>::operator+=(const Vector<type> & other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
}
template<class type>
void Sim::Vector<type>::operator-=(const Vector<type> & other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::operator-(const Vector<type> & other)
{
return Vector(X - other.X, Y - other.Y, Z - other.Z);
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::operator*(float val)
{
	return Vector(X * val, Y * val, Z * val);
}
template<class type>
Sim::Vector<type> Sim::Vector<type>::operator/(float val)
{
	if (val == 0)
	{
		return Vector<type>();
	}
	return Vector(X / val, Y / val, Z / val);
}

template<class type>
bool Sim::Vector<type>::operator==(const Vector<type> & other)
{
return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

template<class type>
bool Sim::Vector<type>::operator!=(const Vector<type> & other)
{
	return (X != other.X) || (Y != other.Y) || (Z != other.Z);
}
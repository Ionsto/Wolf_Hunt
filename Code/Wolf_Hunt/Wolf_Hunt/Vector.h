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
		Vector operator+(Vector other);
		void operator+=(Vector other);
		void operator-=(Vector other);
		Vector operator-(Vector other);
		Vector operator*(float val);
		Vector operator/(float val);
		float Dot(Vector other);
		Vector Normalise();
		//Strict equality
		bool operator!=(Vector check);
		bool operator==(Vector check);
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
float Sim::Vector<type>::Dot(Vector<type> other)
{
	return (X * other.X) + (Y * other.Y) + (Z * other.Z);
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::Normalise()
{
	float mag = sqrtf(this->Dot(*this));
	return *this / mag;
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::operator+(Vector<type> other)
{
return Vector(X + other.X, Y + other.Y, Z + other.Z);
}

template<class type>
void Sim::Vector<type>::operator+=(Vector<type> other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
}
template<class type>
void Sim::Vector<type>::operator-=(Vector<type> other)
{
	X -= other.X;
	Y -= other.Y;
}

template<class type>
Sim::Vector<type> Sim::Vector<type>::operator-(Vector<type> other)
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
bool Sim::Vector<type>::operator==(Vector other)
{
return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

template<class type>
bool Sim::Vector<type>::operator!=(Vector other)
{
	return (X != other.X) || (Y != other.Y) || (Z != other.Z);
}
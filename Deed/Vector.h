#pragma once

#include <array>

//Common vector types
#define Vector2i Vector<int, 2>
#define Vector2f Vector<float, 2>
#define Vector2d Vector<double, 2>

#define Vector3i Vector<int, 3>
#define Vector3f Vector<float, 3>
#define Vector3d Vector<double, 3>

//A column vector in the mathematical sense
//Size must be >= 1 else undefined behaviour
template<typename T, size_t Size> class Vector
{
	public:
	//Declaration of a vector without values set
	Vector() {  }
	//Initialise a vector with a single value
	Vector(const T initialiser) { ar = { initialiser }; }
	//Initialise a vector with an array
	Vector(std::array<T, Size> const args) : ar(args) {  }

	T& operator[](size_t index) 
	{ 
		return ar[index];
	}

	const T& operator[](size_t index) const
	{
		return ar[index];
	}

	Vector operator+(const Vector& other) const
	{
		Vector result;
		for (size_t i = 0; i < Size; i++) { result[i] = ar[i] + other[i]; }
		return result;
	}

	Vector operator-(const Vector& other) const
	{
		Vector result;
		for (size_t i = 0; i < Size; i++) { result[i] = ar[i] - other[i]; }
		return result;
	}

	Vector operator*(const T multiplier) const
	{
		Vector result;
		for (size_t i = 0; i < Size; i++) { result[i] = ar[i] * multiplier; }
		return result;
	}

	Vector operator/(const T divisor) const
	{
		Vector result;
		for (size_t i = 0; i < Size; i++) { result[i] = ar[i] / divisor; }
		return result;
	}

	void scale(const T multiplier)
	{
		for (size_t i = 0; i < Size; i++) { ar[i] *= multiplier; }
	}

	T dot(const Vector& other) const
	{
		T value = T();
		for (size_t i = 0; i < Size; i++) { value += ar[i] * other[i]; }
		return value;
	}

	T squareMag() const { return dot(*this); }

	double mag() const { return sqrt(squareMag()); }

	private:
	std::array<T, Size> ar;

};

//Common vector size constructions
template<typename T> Vector<T, 1> makeVector(T x) { return Vector<T, 1>(std::array<T, 1> { x }); }
template<typename T> Vector<T, 2> makeVector(T x, T y) { return Vector<T, 2>(std::array<T, 2> { x, y }); }
template<typename T> Vector<T, 3> makeVector(T x, T y, T z) { return Vector<T, 3>(std::array<T, 3> { x, y, z }); }
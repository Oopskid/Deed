#pragma once

#include <array>

//A column vector in the mathematical sense
template<typename T, size_t Size> class Vector
{
	public:
	//Declaration of a vector without values set
	Vector() : ar() {  }
	//Initialise a vector with a single value
	Vector(const T initialiser) { ar.fill(initialiser); }
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

	Vector& operator=(const Vector& other)
	{
		ar = other.ar;
		return *this;
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
	
	Vector<T, Size + 1> getHomogeneous(const T append) const
	{  
		std::array<T, Size + 1> newAr;
		for (size_t i = 0; i < Size; i++) { newAr[i] = ar[i]; } //Copy
		newAr[Size] = append; //The extra on the end
		return Vector<T, Size + 1>(newAr);
	}

	Vector<T, Size - 1> fromHomogeneous() const
	{
		std::array<T, Size - 1> newAr;
		T divisor = ar[newAr.size()];
		for (size_t i = 0; i < newAr.size(); i++) { newAr[i] = ar[i] / divisor; } //Copy and apply scale
		return Vector<T, newAr.size()>(newAr);
	}

	Vector normalised() const
	{
		return *this / mag();
	}

	size_t getSize() const { return ar.size(); }
	T const* getData() const { return ar.data(); }
	T* getData() { return ar.data(); }

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

//Common vector types
typedef Vector<int, 2> Vector2i;
typedef Vector<float, 2> Vector2f;
typedef Vector<double, 2> Vector2d;

typedef Vector<int, 3> Vector3i;
typedef Vector<float, 3> Vector3f;
typedef Vector<double, 3> Vector3d;

typedef Vector<int, 4> Vector4i;
typedef Vector<float, 4> Vector4f;
typedef Vector<double, 4> Vector4d;

//Common vector size constructions
template<typename T> Vector<T, 1> makeVector(const T x) { return Vector<T, 1>(std::array<T, 1> { x }); }
template<typename T> Vector<T, 2> makeVector(const T x, const T y) { return Vector<T, 2>(std::array<T, 2> { x, y }); }
template<typename T> Vector<T, 3> makeVector(const T x, const T y, const T z) { return Vector<T, 3>(std::array<T, 3> { x, y, z }); }
template<typename T> Vector<T, 4> makeVector(const T x, const T y, const T z, const T w) { return Vector<T, 4>(std::array<T, 4> { x, y, z, w }); }

//Change underlying vector type
template<typename T, typename S, size_t Size> Vector<T, Size> cast(const Vector<S, Size>& from)
{
	Vector<T, Size> returning;
	for (size_t i = 0; i < Size; i++) { returning[i] = (T)from[i]; }
	return returning;
}
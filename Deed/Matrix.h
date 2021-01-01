#pragma once

#include "Vector.h"

//A matrix in the mathematical sense
//Stored and used as a vector to utilise cache of concurrent memory (1d array)
//Size must be >= 1 else undefined behaviour
template<typename T, size_t nRows, size_t nColumns> class Matrix
{
	//Vector that is being used
	typedef Vector<T, nRows* nColumns> baseV;

	public:
	//Declaration of a matrix without values set
	Matrix() { elements = baseV(); }
	//Initialise a matrix with a single value
	Matrix(const T initialiser) { elements = baseV(initialiser); }
	//Initialise the matrix with an array
	Matrix(std::array<T, nRows* nColumns> const args) { elements = baseV(args); }

	T& operator[](size_t linearI)
	{
		return elements[linearI];
	}

	const T& operator[](size_t linearI) const
	{
		return elements[linearI];
	}

	T& get(size_t row, size_t column)
	{
		//Columns are concurrent, rows are packed sequentially
		return elements[column + (row * nColumns)];
	}

	const T& get(size_t row, size_t column) const
	{
		//Columns are concurrent, rows are packed sequentially
		return elements[column + (row * nColumns)];
	}

	Matrix operator+(const Matrix& other) const
	{
		Matrix result;
		result.elements = elements + other.elements;
		return result;
	}

	Matrix operator-(const Matrix& other) const
	{
		Matrix result;
		result.elements = elements - other.elements;
		return result;
	}

	Matrix operator*(const T multiplier) const
	{
		Matrix result;
		result.elements = elements * multiplier;
		return result;
	}

	Matrix operator/(const T divisor) const
	{
		Matrix result;
		result.elements = elements / divisor;
		return result;
	}

	void scale(const T multiplier)
	{
		elements.scale(multiplier);
	}

	private:
	baseV elements;
};
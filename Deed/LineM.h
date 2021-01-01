#pragma once

#include "Vector.h"
#include "Matrix.h"

//Linear algebra
namespace LineM
{
	//Returns an identity matrix multiplied by some constant
	template<typename T, size_t Size> Matrix<T, Size, Size> identity(T multiplier)
	{
		auto result = Matrix<T, Size, Size>(T());
		
		size_t elIndex = 0; //Keeps track of actual position
		for (size_t i = 0; i < Size; i++) 
		{ 
			result[elIndex] = multiplier; 
			
			elIndex++; //Move column
			elIndex += Size; //Move down a row
		}
		return result;
	}

	template<typename T> T det2x2(T a1, T a2, T b1, T b2)
	{
		return (a1 * b2) - (a2 * b1);
	}

	template<typename T> T det2x2(const Matrix<T, 2, 2>& mat)
	{
		return det2x2(mat[0], mat[1], mat[2], mat[3]);
	}

	template<typename T> T det3x3(const Matrix<T, 3, 3>& mat)
	{
		T result = det2x2(mat[4], mat[5], mat[7], mat[8]) * mat[0]; //i
		result -= det2x2(mat[3], mat[5], mat[6], mat[8]) * mat[1]; //j
		result += det2x2(mat[3], mat[4], mat[6], mat[7]) * mat[2]; //k
		return result;
	}

	template<typename T> Vector<T, 3> cross(const Vector<T, 3>& first, const Vector<T, 3>& second)
	{
		Vector<T, 3> result;

		result[0] = det2x2(first[1], first[2], second[1], second[2]); //i
		result[1] = -det2x2(first[0], first[2], second[0], second[2]); //-j
		result[2] = det2x2(first[0], first[1], second[0], second[1]); //k

		return result;
	}

	template<typename T, size_t rowN, size_t columnN, size_t other> Matrix<T, rowN, columnN> multiply(const Matrix<T, rowN, other>& first, const Matrix<T, other, columnN>& second)
	{
		Matrix<T, rowN, columnN> result;

		size_t curElm = 0; //Go through the result sequentially
		for (size_t r = 0; r < rowN; r++)
		{
			for (size_t c = 0; c < columnN; c++)
			{
				T element = T();

				size_t firstElm = other * r;
				size_t secElm = c;
				for (size_t i = 0; i < other; i++)
				{
					element += first[firstElm] * second[secElm]; //Add to element
					
					firstElm++; //Go across row
					secElm += columnN; //Go down column
				}

				result[curElm] = element;
				curElm++;
			}
		}

		return result;
	}

}


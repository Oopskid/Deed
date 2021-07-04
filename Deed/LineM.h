#pragma once

#include <vector>

#include "Vector.h"
#include "Matrix.h"

//Linear algebra
namespace LineM
{
	template<typename T, size_t Size> Matrix<T, 1, Size> asRow(const Vector<T, Size> vec)
	{
		return Matrix<T, 1, Size>(vec);
	}

	template<typename T, size_t Size> Matrix<T, Size, 1> asColumn(const Vector<T, Size> vec)
	{
		return Matrix<T, Size, 1>(vec);
	}

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

	//Determinant from values
	template<typename T> T det2x2(T a1, T a2, T b1, T b2)
	{
		return (a1 * b2) - (a2 * b1);
	}

	//Determinant of a 2x2
	template<typename T> T det2x2(const Matrix<T, 2, 2>& mat)
	{
		return det2x2(mat[0], mat[1], mat[2], mat[3]);
	}

	//Determinant of a 3x3
	template<typename T> T det3x3(const Matrix<T, 3, 3>& mat)
	{
		T result = det2x2(mat[4], mat[5], mat[7], mat[8]) * mat[0]; //i
		result -= det2x2(mat[3], mat[5], mat[6], mat[8]) * mat[1]; //j
		result += det2x2(mat[3], mat[4], mat[6], mat[7]) * mat[2]; //k
		return result;
	}

	//Determinant of NxN matrix (array) using cofactor expansion
	template<typename T>  T det(const size_t squareSize, const T* mat)
	{
		//Return the only value at one!
		if (squareSize == 1) { return mat[0]; }

		T determinant = 0;

		const size_t matElementCount = squareSize * squareSize;
		const size_t pieceSize = squareSize - 1;
		
		//Use top row
		for (size_t co = 0; co < squareSize; co++)
		{
			std::vector<T> piece(pieceSize * pieceSize);

			size_t mapFrom = squareSize;
			size_t mapTo = 0;
			for (; mapFrom < matElementCount; mapFrom++)
			{
				if ((mapFrom - co) % squareSize != 0)
				{
					piece[mapTo] = mat[mapFrom];
					mapTo++;
				}
			}

			if (co % 2 == 0) { determinant += mat[co] * det(pieceSize, piece.data()); }
			else { determinant -= mat[co] * det(pieceSize, piece.data()); }
		}

		return determinant;
	}

	//Determinant of NxN matrix using cofactor expansion
	template<typename T, size_t squareSize> T det(const Matrix<T, squareSize, squareSize>& mat)
	{
		return det(squareSize, mat.getData());
	}

	template<typename T, size_t squareSize> Matrix<T, squareSize, squareSize> adjugate(const Matrix<T, squareSize, squareSize>& mat)
	{
		Matrix<T, squareSize, squareSize> adjRet;

		const size_t pieceSize = squareSize - 1;
		for (size_t i = 0; i < mat.asVector().getSize(); i++)
		{
			//Better unpacking than multiple loops
			size_t x = i % squareSize;
			size_t y = i / squareSize;

			size_t adjTo = 0;
			T piece[pieceSize * pieceSize];
			for (size_t matFrom = 0; matFrom < mat.asVector().getSize(); matFrom++)
			{
				size_t fromX = matFrom % squareSize;
				size_t fromY = matFrom / squareSize;

				//If same row then skip entire row
				if (fromY == y) { matFrom += pieceSize; continue; }
				//If same column then skip
				if (fromX == x) { continue; }

				piece[adjTo] = mat[matFrom];
				adjTo++;
			}

			//Transpose
			if (i % 2 == 0) { adjRet.get(x, y) = det(pieceSize, piece); }
			else { adjRet.get(x, y) = -det(pieceSize, piece); }
		}

		return adjRet;
	}

	template<typename T, size_t squareSize> Matrix<T, squareSize, squareSize> inverse(const Matrix<T, squareSize, squareSize>& mat)
	{
		return adjugate(mat) / det(mat);
	}

	//Cross product of two vectors
	template<typename T> Vector<T, 3> cross(const Vector<T, 3>& first, const Vector<T, 3>& second)
	{
		Vector<T, 3> result;

		result[0] = det2x2(first[1], first[2], second[1], second[2]); //i
		result[1] = -det2x2(first[0], first[2], second[0], second[2]); //-j
		result[2] = det2x2(first[0], first[1], second[0], second[1]); //k

		return result;
	}

	//Multiply two matrices
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

	//Multiply a matrix and vector
	template<typename T, size_t rowN, size_t columnN> Vector<T, rowN> multiply(const Matrix<T, rowN, columnN>& first, const Vector<T, columnN>& second)
	{
		return (multiply(first, asColumn(second))).asVector();
	}

	//Multiply a matrix and vector
	template<typename T, size_t rowN, size_t columnN> Vector<T, columnN> multiply(const Vector<T, rowN>& first, const Matrix<T, rowN, columnN>& second)
	{
		return (multiply(asRow(first), second)).asVector();
	}



	//Premultiply translation
	template<typename T, size_t squareSize> void translate(Vector<T, squareSize - 1> translation, Matrix<T, squareSize, squareSize>& matrix)
	{
		const size_t vecSize = squareSize - 1;

		size_t elemLoc = vecSize * squareSize;
		for (size_t i = 0; i < vecSize; i++)
		{
			size_t multElm = i;
			for (size_t i2 = 0; i2 < vecSize; i2++) 
			{
				matrix[elemLoc] += matrix[multElm] * translation[i2]; 
				multElm += squareSize;
			}
			elemLoc++; //Next matrix element
		}
	}

	//Postmultiply translation
	template<typename T, size_t squareSize> void translate(Matrix<T, squareSize, squareSize>& matrix, Vector<T, squareSize - 1> translation)
	{
		const size_t vecSize = squareSize - 1;

		size_t elemLoc = 0;
		
		for (size_t i = 0; i < squareSize; i++)
		{
			size_t multElm = elemLoc + vecSize;
			for (size_t i2 = 0; i2 < vecSize; i2++)
			{
				matrix[elemLoc] += matrix[multElm] * translation[i2];
				elemLoc++;
			}

			elemLoc++;
		}
	}
}


#pragma once

#include <vector>

//Inverse mathematics
namespace Solve
{
	template<typename T> T determinant(const T a, const T b, const T c) { return b * b - 4 * a * c; }

	template<typename T> std::vector<double> quadratic(const T a, const T b, const T c)
	{
		T det = determinant(a, b, c);

		if (det < 0) { return std::vector<double>(); } //No real roots
		if (a == 0) { return { -c/b }; } //Linear

		a *= 2; //Slight optimisation for 2a
		return { -(b + det) / a, (det - b) / a };
	}

	template<typename T> T triangular(T n)
	{
		return (n * n + n) / 2;
	}
	
}
#pragma once

#include "Matrix.h"
#include "Functions/LineM.h"

//Quaternion of s, xi, yj, zk
template<typename T> class Quaternion
{
	typedef Matrix<T, 4, 4> Matrix;

	public:
	Quaternion() { data = makeVector<T>(1, 0, 0, 0); }
	Quaternion(const Vector<T, 4> newData) : data(newData) {  }
	Quaternion(T angle, Vector<T, 3> axis)
	{
		angle /= 2;
		axis = axis * sin(angle);
		data = makeVector<T>(cos(angle), axis[0], axis[1], axis[2]);
	}

	static Quaternion fromEuler(Vector<T, 3> eulers)
	{
		Quaternion returning;

		eulers = eulers / 2;
		Vector<T, 3> sins = makeVector<T>(sin(eulers[0]), sin(eulers[1]), sin(eulers[0]));
		Vector<T, 3> cose = makeVector<T>(cos(eulers[0]), cos(eulers[1]), cos(eulers[0]));

		returning.w() = sins[0] * sins[1] * sins[2] + cose[0] * cose[1] * cose[2];
		returning.x() = cose[0] * sins[1] * sins[2] - sins[0] * cose[1] * cose[2];
		returning.y() = sins[0] * cose[1] * sins[2] + cose[0] * sins[1] * cose[2];
		returning.z() = sins[0] * sins[1] * cose[2] - cose[0] * cose[1] * sins[2];

		return returning;
	}

	Quaternion operator+(const Quaternion second) const
	{
		return Quaternion(makeVector(x() + second.x(), y() + second.y(), z() + second.z(), w() + second.w()));
	}

	Quaternion operator*(const Quaternion second) const
	{
		return Quaternion(LineM::multiply(data, Matrix({
			second.w(), second.x(), second.y(), second.z(),
			-second.x(), second.w(), -second.z(), second.y(),
			-second.y(), second.z(), second.w(), -second.x(),
			-second.z(), -second.y(), second.x(), second.w()
			})));
	}

	Vector<T, 3> operator*(const Vector<T, 3> vec)
	{
		return LineM::multiply(getTransform(), vec.getHomogeneous(1)).fromHomogeneous();
	}

	Vector<T, 4> operator*(const Vector<T, 4> vec)
	{
		return LineM::multiply(getTransform(), vec);
	}

	void reverse()
	{
		x() = -x();
		y() = -y();
		z() = -z();
	}

	Quaternion reversed() const
	{
		Quaternion returning = *this;
		returning.reverse();
		return returning;
	}

	inline Quaternion asConjugate() const { return reversed(); }

	static Quaternion displacement(Quaternion from, Quaternion to)
	{
		return to * from.reversed();
	}

	Matrix getTransform()
	{
		return LineM::multiply(Matrix({ 
			w(), z(), -y(), x(),
			-z(), w(), x(), y(),
			y(), -x(), w(), z(),
			-x(), -y(), -z(), w()}),
			Matrix({
			w(), z(), -y(), -x(),
			-z(), w(), x(), -y(),
			y(), -x(), w(), -z(),
			x(), y(), z(), w()}));
	}

	//Returns the forward vector (z/k) under this transformation assuming unit quaternion
	Vector<T, 3> getForward() const
	{
		return makeVector(2 * (x() * z() + w() * y()), 2 * (y() * z() - w() * x()), w() * w() + z() * z() - x() * x() - y() * y());
	}

	//Returns the right vector (x/i) under this transformation assuming unit quaternion
	Vector<T, 3> getRight() const
	{
		return makeVector(w() * w() + x() * x() - y() * y() - z() * z(), 2 * (x() * y() + w() * z()), 2 * (x() * z() - w() * y()));
	}

	//Returns the up vector (y/j) under this transformation assuming unit quaternion
	Vector<T, 3> getUp() const
	{
		return makeVector(2 * (x() * y() - w() * z()), w() * w() + y() * y() - x() * x() - z() * z(), 2 * (y() * z() + w() * x()));
	}

	protected:
	inline T& w() { return data[0]; }
	inline T& x() { return data[1]; }
	inline T& y() { return data[2]; }
	inline T& z() { return data[3]; }

	inline const T w() const { return data[0]; }
	inline const T x() const { return data[1]; }
	inline const T y() const { return data[2]; }
	inline const T z() const { return data[3]; }

	private:
	Vector<T, 4> data;
};
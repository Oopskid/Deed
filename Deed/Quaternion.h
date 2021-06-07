#pragma once

#include "Matrix.h"
#include "LineM.h"

//Quaternion of s, xi, yj, zk
template<typename T> class Quaternion
{
	typedef Matrix<T, 4, 4> Matrix;

	public:
	Quaternion() { data = makeVector<T>(1, 0, 0, 0); }
	Quaternion(const Vector<T, 4> newData) : data(newData) {  }
	Quaternion(T angle, Vector<T, 3> axis)
	{
		axis = axis * sin(angle);
		data = makeVector<T>(cos(angle), axis[0], axis[1], axis[2]);
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
	Vector<T, 3> getForward()
	{
		return makeVector(2 * (x() * z() + w() * y()), 2 * (y() * z() - w() * x()), w() * w() + z() * z() - x() * x() - y() * y());
	}

	//Returns the right vector (x/i) under this transformation assuming unit quaternion
	Vector<T, 3> getRight()
	{
		return makeVector(w() * w() + x() * x() - y() * y() - z() * z(), 2 * (x() * y() + w() * z()), 2 * (x() * z() - w() * y()));
	}

	//Returns the up vector (y/j) under this transformation assuming unit quaternion
	Vector<T, 3> getUp()
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
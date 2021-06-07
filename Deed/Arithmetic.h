#pragma once

#include <string>
#include <cmath>

class Arithmetic
{
	public:
	enum class Operation
	{
		NONE, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, POWER, LOGARITHM
	};

	Arithmetic();
	Arithmetic(Arithmetic::Operation operation);

	void setRule(Arithmetic::Operation newOp);
	Operation getRule();

	template<typename T> T calculate(T first, T second)
	{
		switch (rule)
		{
			case Arithmetic::Operation::ADDITION:
				return first + second;
			case Arithmetic::Operation::SUBTRACTION:
				return first - second;
			case Arithmetic::Operation::MULTIPLICATION:
				return first * second;
			case Arithmetic::Operation::DIVISION:
				return first / second;
			case Arithmetic::Operation::POWER:
				return pow(first, second);
			case Arithmetic::Operation::LOGARITHM:
				return log(first) / log(second);
			default:
				return first;
		}
	}

	template<typename T> T calculateReversal(T first, T second)
	{
		switch (rule)
		{
			case Arithmetic::Operation::ADDITION:
				return first - second;
			case Arithmetic::Operation::SUBTRACTION:
				return first + second;
			case Arithmetic::Operation::MULTIPLICATION:
				return first / second;
			case Arithmetic::Operation::DIVISION:
				return first * second;
			case Arithmetic::Operation::POWER:
				return log(first) / log(second);
			case Arithmetic::Operation::LOGARITHM:
				return pow(first, second);
			default:
				return first;
		}
	}

	private:
	Operation rule;
};


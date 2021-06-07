#include "pch.h"

#include "Arithmetic.h"

Arithmetic::Arithmetic()
{
	rule = Operation::NONE;
}

Arithmetic::Arithmetic(Arithmetic::Operation operation)
{
	rule = operation;
}

void Arithmetic::setRule(Arithmetic::Operation newOp)
{
	rule = newOp;
}

Arithmetic::Operation Arithmetic::getRule()
{
	return rule;
}

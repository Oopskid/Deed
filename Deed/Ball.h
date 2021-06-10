#pragma once

#include "Kinetic.h"

#include "Circle.h"
template<typename T, size_t Dims> class Ball :
public Circle<T, Dims>, public Kinetic<T>
{

};


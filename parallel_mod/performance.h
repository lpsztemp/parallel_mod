#pragma once
#include <chrono>
#include <vector>
#include "config.h"

struct measurement
{
	IntegerWord result;
	std::chrono::milliseconds time;
};

std::vector<measurement> run_experiments();
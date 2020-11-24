
#pragma once

#include "config.h"
#include <climits>

struct test_datum
{
	const IntegerWord* dividend;
	std::size_t dividend_size;
	IntegerWord divisor;
	IntegerWord result;
};

extern const test_datum test_data[];

constexpr std::size_t test_data_count = 10;


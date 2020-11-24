#pragma once
#include <cstdint>
#include <cstdlib>

typedef std::uintptr_t IntegerWord;

#define INTWORD_MAX UINTPTR_MAX

#ifdef _MSC_VER
#pragma warning (disable: 4146)
#endif //_MSC_VER

#ifdef __cplusplus
#define EXTERN_C extern "C"
#include <cstdio>
using std::fprintf;
#else
#define EXTERN_C
#include <stdio.h>
#endif

#define verify(bool_expr) if (!(bool_expr)) {fprintf(stderr, "Error in %s (%d)\n", __FILE__, __LINE__); abort();}

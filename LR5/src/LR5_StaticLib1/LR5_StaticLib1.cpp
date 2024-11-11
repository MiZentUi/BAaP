// LR5_StaticLib1.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "LR5_StaticLib1.h"

bool calculate_matrix(long double** a, long double** b, long double** c, long long n)
{
	for (long long i = 0; i < n; i++)
		for (long long j = 0; j < n; j++)
		{
			if (b[i][j] > c[i][j])
				a[i][j] = b[i][j];
			else
				a[i][j] = c[i][j];
		}
	return true;
}
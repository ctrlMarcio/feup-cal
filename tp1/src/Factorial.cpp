/*
 * Factorial.cpp
 */
#include "Factorial.h"

int factorialRecurs(int n) {
	if (n <= 1)
		n = 1;
	else
		n = n * factorialRecurs(n - 1);

	return n;
}

int factorialDinam(int n) {
	int res = 1;

	for (int i = 2; i <= n; ++i)
		res *= i;

	return res;
}

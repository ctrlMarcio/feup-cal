/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <fstream>

string &fillFirstIteration(const int *sequence, int size, int **values, string &res);

void updateValues(int *const *values, int iteration, int qtNumbers, int &bestIndex, int &bestSum);

void freeValues(int size, int *const *values);

/*
 * Creates an array of arrays of values that sums all the values from the bottom up, saving the best index and best sum.
 *
 * Example, for sequence = {4, 7, 2, 8, 1},
 * 	index =		0	1	2	3	4 |	ind, sum
 *				---------------------------------------
 *  values = 	4	7	2	8	1 |	4, 1
 *  			11	9	10	9	  | 1, 9
 *  			13	17	11		  | 2, 11
 *  			21	18			  | 1, 18
 *  			22				  | 0, 22
 *
 * It fills the first line with the exact same values of the sequence vector.
 * From then on, fills summing the value immediately above with the basic value right after.
 * The value 	11 in the second line is the sum of 4 and 7.
 * 				13 = 11 + 2 (2 is after 7, the last value of 11)
 * 				21 = 13 + 8 and so on.
 *
 * ⚠ Big BIG documentation so I don't forget what I've done when I come back to study lmao ⚠
 */
string calcSum(int *sequence, int size) {
	int *values[size]; // array of arrays that hold the sum of all the values
	string res;

	res = fillFirstIteration(sequence, size, values, res);

	for (int iteration = 1; iteration < size; iteration++) {
		int bestIndex = 0;
		int bestSum = std::numeric_limits<int>::max();

		int qtNumbers = size - iteration;
		values[iteration] = (int*)malloc(sizeof(int) * qtNumbers);

		updateValues(values, iteration, qtNumbers, bestIndex, bestSum);

		res += to_string(bestSum) + "," + to_string(bestIndex) + ";";
	}

	freeValues(size, values);

	return res;
}

void benchmark(string name, int maxSize, int qtMeasurements) {
	const int INCREMENTAL = 10;

	ofstream file;
	file.open(name);
	file << "Size,Average (millis)\n";

	srand (time(NULL));

	int sum;
	double avg;
	for (int size = INCREMENTAL; size < maxSize; size += INCREMENTAL) {
		sum = 0;
		for (int i = 0; i < qtMeasurements; ++i) {
			int *arr = (int*)malloc(sizeof(int) * size);

			for (int j = 0; j < size; j++)
				arr[j] = rand() % size + 1;

			auto start = std::chrono::high_resolution_clock::now();
			calcSum(arr, size);
			auto finish = std::chrono::high_resolution_clock::now();
			sum += chrono::duration_cast<chrono::milliseconds>(finish - start).count();

			free(arr);
		}
		avg = (double) sum / qtMeasurements;
		file << size << "," << avg << "\n";
	}

	file.close();
}

void freeValues(int size, int *const *values) {
	for (int i = 0; i < size; ++i)
		free(values[i]);
}

void updateValues(int *const *values, int iteration, int qtNumbers, int &bestIndex, int &bestSum) {
	for (int i = 0; i < qtNumbers; i++) {
		values[iteration][i] = values[iteration - 1][i] + values[0][iteration + i];

		if (i == 0 || values[iteration][i] < bestSum) {
			bestIndex = i;
			bestSum = values[iteration][i];
		}
	}
}

string &fillFirstIteration(const int *sequence, int size, int **values, string &res) {
	values[0] = (int*)malloc(sizeof(int) * size);
	int bestIndex = 0;
	int bestSum = numeric_limits<int>::max();

	for (int i = 0; i < size; ++i) {
		values[0][i] = sequence[i];
		if (sequence[i] < bestSum) {
			bestIndex = i;
			bestSum = sequence[i];
		}
	}

	res += to_string(bestSum) + "," + to_string(bestIndex) + ";";
	return res;
}


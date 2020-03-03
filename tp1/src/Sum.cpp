/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <fstream>

string &fillFirstIteration(const int *sequence, int size, int *values, string &res);

void updateValues(int *values, int iteration, int qtNumbers, int &bestIndex, int &bestSum);

void freeValues(int size, int *const *values);

int getSum(const int *sequence, int iteration, int amount);

string buildResString(int size, const int *bestSums, const int *bestIndexes);

/*
 * ALTERNATIVE METHOD: less efficient spatially.
 *
 * Creates an array of arrays of values that sums all the values from the bottom up, saving the best index and best sum.
 *
 * Example, for sequence = {4, 7, 2, 8, 1},
 * 	index =		0	1	2	3	4 | ind, sum
 *			-----------------------------------------------
 *	values = 	4	7	2	8	1 | 4, 1
 *  			11	9	10	9	  | 1, 9
 *  			13	17	11		  | 2, 11
 *  			21	18			  | 1, 18
 *  			22				  | 0, 22
 *
 * It fills the first line with the exact same values of the sequence vector.
 * From then on, fills summing the value immediately above with the basic value right after.
 * The value 	11 in the second line is the sum of 4 and 7.
 * 		13 = 11 + 2 (2 is after 7, the last value of 11)
 * 		21 = 13 + 8 and so on.
 *
 * ⚠ Big BIG documentation so I don't forget what I've done when I come back to study lmao ⚠
 */
string calcSum2(int *sequence, int size) {
	int values[size];
	string res;

	res = fillFirstIteration(sequence, size, values, res);

	for (int iteration = 1; iteration < size; iteration++) {
		int bestIndex = 0;
		int bestSum = std::numeric_limits<int>::max();

		int qtNumbers = size - iteration;

		updateValues(values, iteration, qtNumbers, bestIndex, bestSum);

		res += to_string(bestSum) + "," + to_string(bestIndex) + ";";
	}

	return res;
}

string calcSum(int *sequence, int size) {
    int bestSums[size];
    int bestIndexes[size];

    for (int iteration = 0; iteration < size; ++iteration) {
        int bestIndex = 0;
        int bestSum = std::numeric_limits<int>::max();

        for (int i = 0; i < size - iteration; ++i) {
            int sum = getSum(sequence, iteration, i);

            if (sum < bestSum) {
                bestSum = sum;
                bestIndex = i;
            }
        }

        bestSums[iteration] = bestSum;
        bestIndexes[iteration] = bestIndex;
    }

    return buildResString(size, bestSums, bestIndexes);
}

string buildResString(int size, const int *bestSums, const int *bestIndexes) {
    string res = "";
    for (int i = 0; i < size; ++i)
        res += to_string(bestSums[i]) + "," + to_string(bestIndexes[i]) + ";";
    return res;
}

int getSum(const int *sequence, int iteration, int amount) {
    int sum = 0;
    for (int j = 0; j <= iteration; ++j)
        sum += sequence[amount + j];
    return sum;
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

void updateValues(int *values, int iteration, int qtNumbers, int &bestIndex, int &bestSum) {
	for (int i = 0; i < qtNumbers; i++) {
		values[i] = values[i] + values[iteration + i];

		if (i == 0 || values[i] < bestSum) {
			bestIndex = i;
			bestSum = values[i];
		}
	}
}

string &fillFirstIteration(const int *sequence, int size, int *values, string &res) {
	int bestIndex = 0;
	int bestSum = numeric_limits<int>::max();

	for (int i = 0; i < size; ++i) {
		values[i] = sequence[i];
		if (sequence[i] < bestSum) {
			bestIndex = i;
			bestSum = sequence[i];
		}
	}

	res += to_string(bestSum) + "," + to_string(bestIndex) + ";";
	return res;
}


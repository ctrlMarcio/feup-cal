/*
 * Change.cpp
 */

#include <vector>
#include "Change.h"

void clearVectors(int size, int minCoins[], int lastCoin[]);

string getDescriptiveString(int m, int *coinValues, int *lastCoin);

string calcChange(int m, int numCoins, int *coinValues) {
	int minCoins[m + 1];
    int lastCoin[m + 1];

    int *currentValue = coinValues;

	clearVectors(m+1, minCoins, lastCoin);

	for (int i = 1; i <= numCoins; ++i) {
		for (int j = 0; j <= m; j++) {

			if (j < *currentValue)
				continue;

			if (minCoins[j - *currentValue] + 1 < minCoins[j] || minCoins[j] == 0) {
				minCoins[j] = minCoins[j - *currentValue] + 1;
				lastCoin[j] = i;
			}
		}

		currentValue++;
	}

	vector<int> selectedCoinValues;

	int index = m;

	while (index > 0) {
		int selectedCoinIndex = lastCoin[index];

		if (selectedCoinIndex <= 0) // It is impossible
			return "-";

		int value = coinValues[selectedCoinIndex - 1];
		selectedCoinValues.push_back(value);
		index -= value;
	}

	string res;
	for (int v : selectedCoinValues)
		res = res + to_string(v) + ";";

	return res;
}

// TODO not working?, all code in the big function instead
string getDescriptiveString(int m, int *coinValues, int *lastCoin) {
	vector<int> selectedCoinValues;

	int index = m;

	while (index > 0) {
		int selectedCoinIndex = lastCoin[index];

		if (selectedCoinIndex <= 0) // It is impossible
			return "-";

		int value = coinValues[selectedCoinIndex - 1];
		selectedCoinValues.push_back(value);
		index -= value;
	}

	string res;
	for (int v : selectedCoinValues)
		res = res + to_string(v) + ";";

	return res;
}

void clearVectors(int size, int minCoins[], int lastCoin[]) {
	for (int i = 0; i <= size; i++) {
		minCoins[i] = 0;
		lastCoin[i] = 0;
	}
}



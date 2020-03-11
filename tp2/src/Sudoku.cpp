/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
	this->initialize();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (nums[i][j] != 0) {
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int n = 0; n < 10; n++) {
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int **Sudoku::getNumbers() {
	int **ret = new int *[9];

	for (int i = 0; i < 9; i++) {
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete() {
	return countFilled == 9 * 9;
}


/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve() {
	std::set<int> possibilities;
	std::pair<int, int> bestCell = getBestCell(possibilities); // coordinates, ie, X and Y

	for (int n : possibilities) {
		numbers[bestCell.first][bestCell.second] = n;
		lineHasNumber[bestCell.first][n] = true;
		columnHasNumber[bestCell.second][n] = true;
		block3x3HasNumber[bestCell.first / 3][bestCell.second / 3][n] = true;
		countFilled++;
		if (solve()) {
			return isComplete();
		} else {
			numbers[bestCell.first][bestCell.second] = 0;
			lineHasNumber[bestCell.first][n] = false;
			columnHasNumber[bestCell.second][n] = false;
			block3x3HasNumber[bestCell.first / 3][bestCell.second / 3][n] = false;
			countFilled--;
		}
	}

	return isComplete();
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print() {
	for (int i = 0; i < 9; i++) {
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}

std::set<int> Sudoku::getPossibilities(int i, int j) {
	set<int> a;

	if (numbers[i][j])
		return a;

	for (int n = 1; n <= 9; n++)
		if (!lineHasNumber[i][n] && !columnHasNumber[j][n] && !block3x3HasNumber[i / 3][j / 3][n])
			a.insert(n);
	return a;
}

std::pair<int, int> Sudoku::getBestCell(std::set<int> &possibilities) {
	std::set<int> tmp;
	std::pair<int, int> result = {0, 0};
	int bestAmount = 10;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (!numbers[i][j]) {
				tmp = getPossibilities(i, j);

				if (tmp.size() < bestAmount) {
					bestAmount = tmp.size();
					possibilities = std::set<int>(tmp);
					result = {i, j};

					if (bestAmount == 1)
						return result;
				}
			}

		}
	}

	return result;
}

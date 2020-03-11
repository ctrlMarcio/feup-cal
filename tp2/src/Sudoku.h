/*
 * Sudoku.h
 *
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

#define IllegalArgumentException -1

class Sudoku
{
	/**
	 * numbers[i][j] - número que ocupa a linha i, coluna j (de 0 a 8)
	 * 0 quer dizer não preenchido.
	 */
	int numbers[9][9];

	/**
	 * Informação derivada da anterior, para acelerar processamento (número de 1 a 9, nao usa 0)
	 */
	int countFilled;
	bool columnHasNumber[9][10];
	bool lineHasNumber[9][10];
	bool block3x3HasNumber[3][3][10];

	/**
	 * Gets the possible solutions for the cell in the position i, j
	 * @param i
	 * @param j
	 * @return the possible solutions
	 */
	std::set<int> getPossibilities(int i, int j);

	void initialize();

	/**
	 * Gets the best cell to fill, "greedly", filling as well a set of possibilities to that cell.
	 *
	 * @param possibilities the set of possibilities
	 * @return the pair of the best cell {x, y}
	 */
	std::pair<int, int> getBestCell(std::set<int> &possibilities);

public:
	/** Inicia um Sudoku vazio.
	 */
	Sudoku();

	/**
	 * Inicia um Sudoku com um conteúdo inicial.
	 * Lança excepção IllegalArgumentException se os valores
	 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
	 * por linha, coluna ou bloc 3x3.
	 *
	 * @param nums matriz com os valores iniciais (0 significa por preencher)
	 */
	Sudoku(int nums[9][9]);

	/**
	 * Obtem o conteúdo actual (só para leitura!).
	 */
	int** getNumbers();


	/**
	 * Verifica se o Sudoku já está completamente resolvido
	 */
	bool isComplete();


	/**
	 * Resolve o Sudoku.
	 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
	 */
	bool solve();

	bool solve2();


	/**
	 * Imprime o Sudoku.
	 */
	void print();
};

#endif /* SUDOKU_H_ */

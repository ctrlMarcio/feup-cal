/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>

using namespace std;


Labirinth::Labirinth(int values[10][10]) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];

	initializeVisited();
}


void Labirinth::initializeVisited() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}


void Labirinth::printLabirinth() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y) {
	if (labirinth[x][y] == 2)
		return true;
	if (labirinth[x][y] == 0 || visited[x][y])
		return false;

	visited[x][y] = true;

	if (x + 1 <= 9 && findGoal(x + 1, y)) // down
		return true;
	if (y + 1 <= 9 && findGoal(x, y + 1)) // right
		return true;
	if (x - 1 >= 0 && findGoal(x - 1, y)) // up
		return true;
	if (y - 1 >= 0 && findGoal(x, y - 1)) // left
		return true;

	visited[x][y] = false;
	return false;
}



#include "util.h"

vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string token;

	vector<string> elems;
	while (getline(ss, token, delim))
		elems.push_back(move(token));
	return elems;
}
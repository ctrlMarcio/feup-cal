/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template<class T>
class Vertex {
	T info;                        // content of the vertex
	vector<Edge<T> > adj;        // outgoing edges

	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0;        // required by MutablePriorityQueue

	bool visited = false;        // auxiliary field
	bool processing = false;    // auxiliary field

	void addEdge(Vertex<T> *dest, double w);

	double weightTo(Vertex<T> *dest);

public:
	Vertex(T in);

	T getInfo() const;

	double getDist() const;

	Vertex *getPath() const;

	bool operator<(Vertex<T> &vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;

	friend class MutablePriorityQueue<Vertex<T>>;
};


template<class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const {
	return this->dist < vertex.dist;
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template<class T>
double Vertex<T>::weightTo(Vertex<T> *dest) {
	for (Edge<T> edge : this->adj)
		if (edge.dest == dest)
			return edge.weight;

	if (this == dest)
		return 0;

	return INF;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
	Vertex<T> *dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);

	friend class Graph<T>;

	friend class Vertex<T>;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<double>> distancesMatrix;
	vector<vector<int>> pathMatrix;

public:
	Vertex<T> *findVertex(const T &in) const;
	int findVertexIndex(Vertex<T> *vertex) const;

	bool addVertex(const T &in);

	bool addEdge(const T &sourc, const T &dest, double w);

	int getNumVertex() const;

	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);

	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 *
 * returns null if the vertex does not exist
 */
template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 * Auxiliary function to find a vertex index.
 *
 * returns -1 if the vertex does not exist
 */
template<class T>
int Graph<T>::findVertexIndex(Vertex<T> *vertex) const {
	for (int i = 0; i < vertexSet.size(); ++i)
		if (vertexSet[i] == vertex)
			return i;
	return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	Vertex<T> *current = findVertex(orig);
	if (!current)
		return;

	for (Vertex<T> *v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	current->dist = 0;
	queue<Vertex<T> *> queue;
	queue.push(current);

	while (!queue.empty()) {
		Vertex<T> *v = queue.front();
		queue.pop();

		for (Edge<T> &edge : v->adj) {
			if (edge.dest->dist == INF) {
				queue.push(edge.dest);
				edge.dest->dist = v->dist + 1;
				edge.dest->path = v;
			}
		}
	}
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	Vertex<T> *current = findVertex(origin);
	if (!current)
		return;

	for (Vertex<T> *v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	current->dist = 0;

	MutablePriorityQueue<Vertex<T> > priority_queue;
	priority_queue.insert(current);

	while (!priority_queue.empty()) {
		Vertex<T> *v = priority_queue.extractMin();

		for (Edge<T> &edge : v->adj) {
			Vertex<T> *w = edge.dest;
			if (w->dist > v->dist + edge.weight) {
				double oldDistance = w->dist;
				w->dist = v->dist + edge.weight;
				w->path = v;

				if (oldDistance == INF)
					priority_queue.insert(w);
				else
					priority_queue.decreaseKey(w);
			}
		}
	}
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	Vertex<T> *start = findVertex(orig);
	if (start == NULL)
		return;

	for (Vertex<T> *v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	start->dist = 0;

	for (int i = 0; i < vertexSet.size() - 1; ++i) {
		for (Vertex<T> *vertex : vertexSet) {
			for (Edge<T> edge : vertex->adj) {
				if (edge.dest->dist > vertex->dist + edge.weight) {
					edge.dest->dist = vertex->dist + edge.weight;
					edge.dest->path = vertex;
				}
			}
		}
	}

	for (Vertex<T> *vertex : vertexSet) {
		for (Edge<T> edge : vertex->adj) {
			if (vertex->dist + edge.weight < edge.dest->dist)
				cerr << "The graph has negative weights" << endl;
		}
	}
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const {
	vector<T> res;

	Vertex<T> *current = findVertex(dest);
	if (!current)
		return res;

	stack<Vertex<T> *> stack;
	stack.push(current);

	Vertex<T> *previous;
	while ((previous = current->getPath())) {
		stack.push(previous);
		current = previous;
	}

	while (!stack.empty()) {
		res.push_back(stack.top()->getInfo());
		stack.pop();
	}

	return res;
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// prepares the matrices, k = 0 if you will
	distancesMatrix.clear();
	pathMatrix.clear();

	for (int i = 0; i < vertexSet.size(); ++i) {
		vector<double> distances;
		vector<int> paths;

		for (Vertex<T> *dst : vertexSet) {
			double weight = (vertexSet[i]->weightTo(dst));
			distances.push_back(weight);

			if (weight != INF)
				paths.push_back(i);
			else
				paths.push_back(-1);
		}

		distancesMatrix.push_back(distances);
		pathMatrix.push_back(paths);
	}

	for (int k = 0; k < vertexSet.size(); ++k) {
		for (int i = 0; i < vertexSet.size(); ++i) { // for each line

			if (distancesMatrix[i][k] == INF)
				continue;

			for (int j = 0; j < vertexSet.size(); ++j) { // for each column
				if (distancesMatrix[k][j] != INF && distancesMatrix[i][k] + distancesMatrix[k][j] < distancesMatrix[i][j]) {
					distancesMatrix[i][j] = distancesMatrix[i][k] + distancesMatrix[k][j];
					pathMatrix[i][j] = pathMatrix[k][j];
				}
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const {
	vector<T> res;
	Vertex<T> *begin = findVertex(orig);
	Vertex<T> *end = findVertex(dest);

	int beginIdx = findVertexIndex(begin);
	if (beginIdx == -1)
		return res;

	int endIdx = findVertexIndex(end);
	if (endIdx == -1)
		return res;

	if (distancesMatrix[beginIdx][endIdx] == INF)
		return res;

	while(endIdx != beginIdx) {
		res.insert(res.begin(), vertexSet[endIdx]->info);
		endIdx = pathMatrix[beginIdx][endIdx];
	}
	res.insert(res.begin(), vertexSet[endIdx]->info); // end == begin

	return res;
}


#endif /* GRAPH_H_ */

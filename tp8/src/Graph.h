/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template<class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;

	Edge<T> *addEdge(Vertex<T> *dest, double c, double f);

	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;

	vector<Edge<T> *> getAdj() const;

	friend class Graph<T>;
};


template<class T>
Vertex<T>::Vertex(T in): info(in) {
}

template<class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> *e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template<class T>
class Edge {
	Vertex<T> *orig;
	Vertex<T> *dest;
	double capacity;
	double flow;

	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f = 0);

public:
	double getFlow() const;

	Vertex<T> *getDest() const;

	friend class Graph<T>;

	friend class Vertex<T>;
};

template<class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f) {}

template<class T>
double Edge<T>::getFlow() const {
	return flow;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;

	Vertex<T> *findVertex(const T &inf) const;

	void resetFlows();

	bool foundAugmentationPath(Vertex<T> *src, Vertex<T> *dst);

	void testAndVisit(queue<Vertex<T> *> &queue, Edge<T> *edge, Vertex<T> *vertex, double residual);

	double findMinResidualLength(Vertex<T> *src, Vertex<T> *dst);

	void augmentFlowAlongPath(Vertex<T> *src, Vertex<T> *dst, double minResidualLength);

public:
	vector<Vertex<T> *> getVertexSet() const;

	Vertex<T> *addVertex(const T &in);

	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f = 0);

	double fordFulkerson(T source, T target);

};

template<class T>
Vertex<T> *Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template<class T>
Edge<T> *Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template<class T>
Vertex<T> *Graph<T>::findVertex(const T &inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template<class T>
double Graph<T>::fordFulkerson(T source, T target) {
	// gets the vertexes
	Vertex<T> *src = this->findVertex(source);
	Vertex<T> *dst = this->findVertex(target);
	if (!src || !dst)
		return -1;

	this->resetFlows();

	double total = 0;

	while (foundAugmentationPath(src, dst)) {
		double minResidualLength = findMinResidualLength(src, dst);
		augmentFlowAlongPath(src, dst, minResidualLength);
		total += minResidualLength;
	}

	return total;
}

template<class T>
void Graph<T>::resetFlows() {
	for (Vertex<T> *v : this->vertexSet)
		for (Edge<T> *e : v->getAdj())
			e->flow = 0;
}

template<class T>
void Graph<T>::testAndVisit(queue<Vertex<T> *> &queue, Edge<T> *edge, Vertex<T> *vertex, double residual) {
	if (!vertex->visited && residual > 0) {
		vertex->visited = true;
		vertex->path = edge;
		queue.push(vertex);
	}
}

template<class T>
bool Graph<T>::foundAugmentationPath(Vertex<T> *src, Vertex<T> *dst) {
	for (Vertex<T> *v : this->vertexSet) v->visited = false;

	src->visited = true;
	queue<Vertex<T> *> queue;
	queue.push(src);

	while (!queue.empty() && !dst->visited) {
		Vertex<T> *current = queue.front();
		queue.pop();

		for (Edge<T> *e : current->outgoing)
			this->testAndVisit(queue, e, e->dest, e->capacity - e->flow);

		for (Edge<T> *e : current->incoming)
			this->testAndVisit(queue, e, e->orig, e->flow);
	}

	return dst->visited;
}

template<class T>
double Graph<T>::findMinResidualLength(Vertex<T> *src, Vertex<T> *dst) {
	double res = INF;
	Vertex<T> *current = dst;

	while (current != src) {
		Edge<T> *edge = current->path;

		if (edge->dest == current) {
			res = min(res, edge->capacity - edge->flow);
			current = edge->orig;
		} else {
			res = min(res, edge->flow);
			current = edge->dest;
		}
	}

	return res;
}

template<class T>
void Graph<T>::augmentFlowAlongPath(Vertex<T> *src, Vertex<T> *dst, double minResidualLength) {
	Vertex<T> *current = dst;

	while (current != src) {
		Edge<T> *edge = current->path;

		if (edge->dest == current) {
			edge->flow += minResidualLength;
			current = edge->orig;
		} else {
			edge->flow -= minResidualLength;
			current = edge->dest;
		}
	}
}

#endif /* GRAPH_H_ */

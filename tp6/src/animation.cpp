#include "animation.h"

#include <algorithm>

void
animateLegs(GraphViewer *gv, int node1id, int x1i, int x1f, int y1, int node2id, int x2i, int x2f, int y2, int parentNode, int minEdgeid,
			int minIdAvailable, int msDelay) {
	gv->removeNode(node1id);
	gv->removeNode(node2id);

	gv->addNode(minIdAvailable, x1i, y1);
	gv->addEdge(minEdgeid++, parentNode, minIdAvailable++, EdgeType::UNDIRECTED);

	gv->addNode(minIdAvailable, x2i, y2);
	gv->addEdge(minEdgeid++, parentNode, minIdAvailable++, EdgeType::UNDIRECTED);

	int difference1 = x1f - x1i;
	int difference2 = x2f - x2i;

	int max = std::max(difference1, difference2);

	int u1 = difference1 / max;
	int u2 = difference2 / max;

	Sleep(msDelay);

	int i = x1i, j = x2i;

	while (1) {
		while (i != x1f) {
			gv->removeNode(minIdAvailable - 2);
			gv->removeEdge(minEdgeid - 2);
			gv->removeNode(minIdAvailable - 1);
			gv->removeEdge(minEdgeid - 1);

			i += u1;
			j += u2;

			gv->addNode(minIdAvailable, i, y1);
			gv->addEdge(minEdgeid++, parentNode, minIdAvailable++, EdgeType::UNDIRECTED);

			gv->addNode(minIdAvailable, j, y2);
			gv->addEdge(minEdgeid++, parentNode, minIdAvailable++, EdgeType::UNDIRECTED);
			gv->rearrange();
			Sleep(msDelay);
		}

		minIdAvailable -= 3;
		minEdgeid -= 3;

		while (i != x1i) {
			gv->removeNode(minIdAvailable + 2);
			gv->removeEdge(minEdgeid + 2);
			gv->removeNode(minIdAvailable + 1);
			gv->removeEdge(minEdgeid + 1);

			i -= u1;
			j -= u2;

			gv->addNode(minIdAvailable, i, y1);
			gv->addEdge(minEdgeid--, parentNode, minIdAvailable--, EdgeType::UNDIRECTED);
			gv->addNode(minIdAvailable, j, y2);
			gv->addEdge(minEdgeid--, parentNode, minIdAvailable--, EdgeType::UNDIRECTED);
			gv->rearrange();
			Sleep(msDelay);
		}

		minIdAvailable += 3;
		minEdgeid += 3;
	}
}
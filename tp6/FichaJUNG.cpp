#include <cstdio>
#include "graphviewer.h"
#include "src/animation.h"
#include "src/util.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	// creates the graph viewer
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	// adds nodes
	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
	gv->removeNode(1);
	gv->addNode(2);
	gv->setVertexLabel(2, "2");
	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	gv->setEdgeLabel(1, "edge");
	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");
	gv->rearrange();
}

void exercicio2()
{
	// creates the graph viewer
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	// adds the nodes
	gv->addNode(0, 300, 50);
	gv->addNode(1, 318, 58);
	gv->addNode(2, 325, 75);
	gv->addNode(3, 318, 93);
	gv->addNode(4, 300, 100);
	gv->addNode(5, 282, 93);
	gv->addNode(6, 275, 75);
	gv->addNode(7, 282, 58);
	gv->addNode(8, 150, 200);
	gv->addNode(9, 300, 200);
	gv->addNode(10, 450, 200);
	gv->addNode(11, 300, 400);
	gv->addNode(12, 200, 550);
	gv->addNode(13, 400, 550);

	// adds the edges
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);
	gv->rearrange();

	// animation
	animateLegs(gv, 12, 200, 250, 550, 13, 400, 350, 550, 11, 14, 14, 1);

	// 2c:
	/*int sleepms = 1000;

	Sleep(sleepms);
	gv->removeNode(12);
	gv->removeNode(13);
	gv->rearrange();

	Sleep(sleepms);
	gv->addNode(14, 250, 550);
	gv->addNode(15, 350, 550);
	gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
	gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
	gv->rearrange();
	 */
}

void exercicio3()
{
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"

	// creates the graph viewer
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	// reads the nodes
	ifstream nodes("../resources/mapa1/nos.txt");
	string line;
	while (getline(nodes, line))
	{
		vector<string> elems = split(line, ';');

		int id = stoi(elems[0]);
		int x = stoi(elems[1]);
		int y = stoi(elems[2]);

		gv->addNode(id, x, y);
	}

	// reads the edges
	ifstream edges("../resources/mapa1/arestas.txt");
	while (getline(edges, line))
	{
		vector<string> elems = split(line, ';');

		int id = stoi(elems[0]);
		int src = stoi(elems[1]);
		int dst = stoi(elems[2]);

		gv->addEdge(id, src, dst, EdgeType::UNDIRECTED);
	}

	gv->rearrange();
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
	return 0;
}

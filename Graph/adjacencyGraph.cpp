//无权无向图的邻接矩阵表示测试

#include <iostream>
#include "adjacencyGraph.h"
#include "unweightedEdge.h"

using namespace std;

void main(void)
{
	adjacencyGraph g(4);
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << endl;

	g.insertEdge(new unweightedEdge(2, 4));
	g.insertEdge(new unweightedEdge(1, 3));
	g.insertEdge(new unweightedEdge(2, 1));
	g.insertEdge(new unweightedEdge(1, 4));
	g.insertEdge(new unweightedEdge(4, 2));
	cout << "The graph is" << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << g << endl;
	cout << endl;

	g.eraseEdge(2, 1);
	cout << "The graph after deleting (2,1) is" << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << g << endl;

	cout << "existsEdge(3,1) = " << g.existsEdge(3, 1) << endl;
	cout << "existsEdge(1,3) = " << g.existsEdge(1, 3) << endl;
	cout << "inDegree(3) = " << g.inDegree(3) << endl;
	cout << "outDegree(1) = " << g.outDegree(1) << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << endl;

	system("pause");
}
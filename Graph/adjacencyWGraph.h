//加权无向图的邻接矩阵表示

#ifndef adjacencyWGraph_
#define adjacencyWGraph_

#include "adjacencyWDigraph.h"

using namespace std;

template <class T>
class adjacencyWGraph :public adjacencyWDigraph<T>
{
public:
	adjacencyWGraph(int numberOfVertices = 0, T theNoEdge = 0)
		: adjacencyWDigraph<T>(numberOfVertices, theNoEdge) {}

	void insertEdge(edge<T>* theEdge)
	{
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();
		if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
		{
			ostringstream s;
			s << "(" << v1 << "," << v2 << ") is not a permissible edge";
			throw illegalParameterValue(s.str());
		}
		if (a[v1][v2] == noEdge)
			e++;
		a[v1][v2] = theEdge->weight();
		a[v2][v1] = theEdge->weight();
	}

	bool directed() const { return false; }

	void eraseEdge(int i, int j)
	{
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			a[j][i] = noEdge;
			e--;
		}
	}

	int degree(int theVertex) const
	{
		checkVertex(theVertex);

		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[theVertex][j] != noEdge)
				sum++;
		return sum;
	}

	int outDegree(int theVertex) const
	{
		return degree(theVertex);
	}

	int inDegree(int theVertex) const
	{
		return degree(theVertex);
	}
};


#endif // !adjacencyWGraph_

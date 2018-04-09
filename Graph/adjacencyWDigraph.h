//加权有向图的邻接矩阵

#ifndef adjacencyWDigraph_
#define adjacencyWDigraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"
#include "myExceptions.h"
#include "arrayQueue.h"
#include "graphChain.h"
#include "minHeap.h"

using namespace std;

template<class T>
class adjacencyWDigraph :public graph<T>
{
protected:
	int n;			//vertex的数量
	int e;			//edge的数量
	T** a;			//邻接数组
	T noEdge;		//表示没有边

public:
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
	{
		if (numberOfVertices < 0)
			throw illegalParameterValue("number of vertices must be >= 0");

		n = numberOfVertices;
		e = 0;
		noEdge = theNoEdge;
		make2dArray(a, n + 1, n + 1);
		for (int i = 1; i <= n; i++)
			fill(a[i], a[i] + n + 1, noEdge);
	}

	~adjacencyWDigraph() { delete2dArray(a, n + 1); }

	int numberOfVertices() const { return n; }

	int numberOfEdges() const { return e; }

	bool directed() const { return true; }

	bool weighted() const { return true; }

	bool existsEdge(int i, int j) const
	{
		if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
			return false;
		else return true;
	}

	void insertEdge(edge<T>* theEdge)
	{//插入边；如果已经存在，则用theEdge->weight()修改边的权
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
	}

	void eraseEdge(int i, int j)
	{
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			e--;
		}
	}

	void checkVertex(int theVertex) const
	{
		if (theVertex < 1 || theVertex > n)
		{
			ostringstream s;
			s << "not vertex " << theVertex;
			throw illegalParameterValue(s.str());
		}
	}

	int degree(int theVertex) const
	{
		throw undefinedMethod("degree() undefined");
	}

	int outDegree(int theVertex) const
	{
		checkVertex(theVertex);

		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[theVertex][j] != noEdge)
				sum++;
		return sum;
	}

	int inDegree(int theVertex) const
	{
		checkVertex(theVertex);

		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[j][theVertex] != noEdge)
				sum++;
		return sum;
	}

	class myIterator :public vertexIterator<T>
	{
	public:
		myIterator(T* theRow, T theNoEdge, int numberOfVertices)
		{
			row = theRow;
			noEdge = theNoEdge;
			n = numberOfVertices;
			currentVertex = 1;
		}

		~myIterator() {}

		int next()
		{
			for (int j = currentVertex; j <= n; j++)
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					return j;
				}
			currentVertex = n + 1;
			return 0;
		}

		int next(T& theWeight)
		{//没有next vertex返回0
			for (int j = currentVertex; j <= n; j++)
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					theWeight = row[j];
					return j;
				}
			currentVertex = n + 1;
			return 0;
		}

	protected:
		T* row;
		T noEdge;
		int n;
		int currentVertex;
	};

	myIterator* iterator(int theVertex)
	{
		checkVertex(theVertex);
		return new myIterator(a[theVertex], noEdge, n);
	}

	void output(ostream& out) const
	{
		for (int i = 1; i <= n; i++)
		{
			copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, " "));
			out << endl;
		}
	}

	void bfs(int v, int reach[], int label)
	{
		arrayQueue<int> q(10);
		reach[v] = label;
		q.push(v);
		while (!q.empty())
		{
			int w = q.front();
			q.pop();

			for (int u = 1; u <= n; u++)
				if (a[w][u] != noEdge && reach[u] == 0)
				{//如果边存在并且未被标记
					q.push(u);
					reach[u] = label;
				}
		}
	}

	//从sourceVertex寻找最短路径
	void shortestPaths(int sourceVertex, T* distanceFromSource, int* predecessor)
	{
		if (sourceVertex < 1 || sourceVertex > n)
			throw illegalParameterValue("Invalid source vertex");
		if (!weighted())
			throw undefinedMethod("adjacencyWDigraph::shortestPaths() not defined for unweighted graphs");

		graphChain<int> newReachableVertices;

		//distanceFromSource[i] 初始化为sourceVertex->i的直接距离，没有过度点
		for (int i = 1; i <= n; i++)
		{
			distanceFromSource[i] = a[sourceVertex][i];
			if (distanceFromSource[i] == noEdge)
				predecessor[i] = -1;
			else
			{
				//若sourceVertex->i连通，i的前驱为sourceVertex
				//将i添加到可到达的graphChain中
				predecessor[i] = sourceVertex;
				newReachableVertices.insert(0, i);
			}
		}
		//源节点本身，距离为0，没有前驱
		distanceFromSource[sourceVertex] = 0;
		predecessor[sourceVertex] = 0;

		//更新distanceFromSource和predecessor
		while (!newReachableVertices.empty())
		{
			//进入while，则还存在更多可到达的点，有可能构成更短的路径
			//寻找distanceFromVertex值最小的，未到达顶点v
			chain<int>::iterator iNewReachableVertices = newReachableVertices.begin();
			chain<int>::iterator theEnd = newReachableVertices.end();
			int v = *iNewReachableVertices;
			iNewReachableVertices++;
			while (iNewReachableVertices != theEnd)
			{
				int w = *iNewReachableVertices;
				iNewReachableVertices++;
				if (distanceFromSource[w] < distanceFromSource[v])
					//若更短则更新并记录
					v = w;
			}

			//下一条最短路径是到达顶点v
			//删除顶点v，更新distanceFromVertex
			newReachableVertices.eraseElement(v);
			for (int j = 1; j <= n; j++)
			{
				//若从v->j的顶点有边
				//并且
				//满足从sourceVertex->j没有边，即前驱为-1
				//或者sourceVertex->j的直接距离大于sourceVertex->i->j的距离和
				//两条件之一
				if (a[v][j] != noEdge &&
					(predecessor[j] == -1 || distanceFromSource[j] > distanceFromSource[v] + a[v][j]))
				{
					//更新source->j的距离，中间经过v
					distanceFromSource[j] = distanceFromSource[v] + a[v][j];
					if (predecessor[j] == -1)
						//若sourceVertex不能直接到达j，即predecessor[j] == -1
						//将j加入sourceVertex可到达的集合
						newReachableVertices.insert(0, j);

					//保证j的前驱v是最短路径的前驱
					predecessor[j] = v;
				}
			}
		}
	}

	template <class T>
	void allPairs(T** c, int **kay)
	{
		//最短路径动态规划
		//对所有i和j计算c[i][j]和kay[i][j]
		if (!weighted())
			throw undefinedMethod
			("adjacncyWDigraph::allParis() not defined for unweighted graphs");

		//初始化c[i][j] = c(i,j,0)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				c[i][j] = a[i][j];
				kay[i][j] = 0;
			}
		for (int i = 1; i <= n; i++)
			c[i][i] = 0;

		//计算 c[i][j] = c(i,j,k)
		//k为中介点
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (c[i][k] != noEdge && c[k][j] != noedge &&
						(c[i][j] == noEdge || c[i][j] > c[i][k] + c[k][j]))
					{
						//若i->k有边
						//且k->j有边
						//且满足
						//i->j无边 或者 i->j > i->k + k->j 两者其中至少一个条件
						c[i][j] = c[i][k] + c[k][j];
						kay[i][j] = k;
					}
	}

	T btSalesperson(int* bestTour)
	{
		if (!weighted())
			throw undefinedMethod
			("adjacencyWDigraph::btSalesperson() not defined for unweighted graphs");
		// set partialTour to identity permutation
		partialTour = new int[n + 1];
		for (int i = 1; i <= n; i++)
			partialTour[i] = i;

		costOfBestTourSoFar = noEdge;
		bestTourSoFar = bestTour;
		costOfPartialTour = 0;

		// search permutations of partialTour[2:n]
		rTSP(2);

		return costOfBestTourSoFar;
	}

	struct heapNode
	{
		T lowerCost;
		T costOfPartialTour;
		T minAdditionalCost;
		int sizeOfPartialTour;
		int* partialTour;
		heapNode() {}

		heapNode(T lC, T cOPT, T mAC, int sOPT, int* pT)
		{
			lowerCost = lC;
			costOfPartialTour = cOPT;
			minAdditionalCost = mAC;
			sizeOfPartialTour = sOPT;
			partialTour = pT;
		}

		operator int() { return lowerCost; }

		bool operator>(const heapNode right)
		{
			return lowerCost > right.lowerCost;
		}
	};

	T leastCostBBSalesperson(int *bestTour)
	{// least-cost branch-and-bound code to find a shortest tour
	 // bestTour[i] set to i'th vertex on shortest tour
	 // Return cost of shortest tour.
		if (!weighted())
			throw undefinedMethod
			("adjacencyWDigraph::leastCostBBSalesperson() not defined for unweighted graphs");

		minHeap<heapNode> liveNodeMinHeap;

		// costOfMinOutEdge[i] = cost of least-cost edge leaving vertex i
		T *costOfMinOutEdge = new T[n + 1];
		T sumOfMinCostOutEdges = 0;
		for (int i = 1; i <= n; i++)
		{// compute costOfMinOutEdge[i] and sumOfMinCostOutEdges
			T minCost = noEdge;
			for (int j = 1; j <= n; j++)
				if (a[i][j] != noEdge && (minCost == noEdge ||
					minCost > a[i][j]))
					minCost = a[i][j];

			if (minCost == noEdge) return noEdge; // no route
			costOfMinOutEdge[i] = minCost;
			sumOfMinCostOutEdges += minCost;
		}

		// initial E-node is tree root
		heapNode eNode(0, 0, sumOfMinCostOutEdges, 0, new int[n]);
		for (int i = 0; i < n; i++)
			eNode.partialTour[i] = i + 1;
		T costOfBestTourSoFar = noEdge;            // no tour found so far
		int *partialTour = eNode.partialTour;      // shorthand for
												   // eNode.partialTour
												   // search permutation tree
		while (eNode.sizeOfPartialTour < n - 1)
		{// not at leaf
			partialTour = eNode.partialTour;
			if (eNode.sizeOfPartialTour == n - 2)
			{// parent of leaf
			 // complete tour by adding two edges
			 // see whether new tour is better
				if (a[partialTour[n - 2]][partialTour[n - 1]] != noEdge
					&& a[partialTour[n - 1]][1] != noEdge
					&& (costOfBestTourSoFar == noEdge ||
						eNode.costOfPartialTour
						+ a[partialTour[n - 2]][partialTour[n - 1]]
						+ a[partialTour[n - 1]][1]
						< costOfBestTourSoFar))
				{// better tour found
					costOfBestTourSoFar = eNode.costOfPartialTour
						+ a[partialTour[n - 2]][partialTour[n - 1]]
						+ a[partialTour[n - 1]][1];
					eNode.costOfPartialTour = costOfBestTourSoFar;
					eNode.lowerCost = costOfBestTourSoFar;
					eNode.sizeOfPartialTour++;
					liveNodeMinHeap.push(eNode);
				}
			}
			else
			{// generate children
				for (int i = eNode.sizeOfPartialTour + 1; i < n; i++)
					if (a[partialTour[eNode.sizeOfPartialTour]]
						[partialTour[i]] != noEdge)
					{
						// feasible child, bound path cost
						T costOfPartialTour = eNode.costOfPartialTour
							+ a[partialTour[eNode.sizeOfPartialTour]]
							[partialTour[i]];
						T minAdditionalCost = eNode.minAdditionalCost
							- costOfMinOutEdge[partialTour
							[eNode.sizeOfPartialTour]];
						T leastCostPossible = costOfPartialTour
							+ minAdditionalCost;
						if (costOfBestTourSoFar == noEdge ||
							leastCostPossible < costOfBestTourSoFar)
						{// subtree may have better leaf, put root in min heap
							heapNode hNode(leastCostPossible,
								costOfPartialTour,
								minAdditionalCost,
								eNode.sizeOfPartialTour + 1,
								new int[n]);
							for (int j = 0; j < n; j++)
								hNode.partialTour[j] = partialTour[j];
							hNode.partialTour[eNode.sizeOfPartialTour + 1] =
								partialTour[i];
							hNode.partialTour[i] =
								partialTour[eNode.sizeOfPartialTour + 1];
							liveNodeMinHeap.push(hNode);
						}
					}
			}

			// get next E-node
			delete[] eNode.partialTour;
			if (liveNodeMinHeap.empty()) break;
			eNode = liveNodeMinHeap.top();
			liveNodeMinHeap.pop();
		}

		if (costOfBestTourSoFar == noEdge)
			return NULL; // no route

						 // copy best route into bestTour[1:n]
		for (int i = 0; i < n; i++)
			bestTour[i + 1] = partialTour[i];

		return costOfBestTourSoFar;
	}

protected:
	void rTSP(int currentLevel)
	{
		if (currentLevel == n)
		{// at parent of a leaf
		 // complete tour by adding last two edges
			if (a[partialTour[n - 1]][partialTour[n]] != noEdge &&
				a[partialTour[n]][1] != noEdge &&
				(costOfBestTourSoFar == noEdge ||
					costOfPartialTour + a[partialTour[n - 1]][partialTour[n]]
					+ a[partialTour[n]][1] < costOfBestTourSoFar))
			{// better tour found
				copy(partialTour + 1, partialTour + n + 1, bestTourSoFar + 1);
				costOfBestTourSoFar = costOfPartialTour
					+ a[partialTour[n - 1]][partialTour[n]]
					+ a[partialTour[n]][1];
			}
		}
		else
		{// try out subtrees
			for (int j = currentLevel; j <= n; j++)
				// is move to subtree labeled partialTour[j] possible?
				if (a[partialTour[currentLevel - 1]][partialTour[j]] != noEdge
					&& (costOfBestTourSoFar == noEdge ||
						costOfPartialTour +
						a[partialTour[currentLevel - 1]][partialTour[j]]
						< costOfBestTourSoFar))
				{// search this subtree
					swap(partialTour[currentLevel], partialTour[j]);
					costOfPartialTour += a[partialTour[currentLevel - 1]]
						[partialTour[currentLevel]];
					rTSP(currentLevel + 1);
					costOfPartialTour -= a[partialTour[currentLevel - 1]]
						[partialTour[currentLevel]];
					swap(partialTour[currentLevel], partialTour[j]);
				}
		}
	}

	static int* partialTour;
	static int* bestTourSoFar;
	static T costOfBestTourSoFar;
	static T costOfPartialTour;
};

int* adjacencyWDigraph<int>::partialTour;
int* adjacencyWDigraph<int>::bestTourSoFar;
int adjacencyWDigraph<int>::costOfBestTourSoFar;
int adjacencyWDigraph<int>::costOfPartialTour;
int* adjacencyWDigraph<float>::partialTour;
int* adjacencyWDigraph<float>::bestTourSoFar;
float adjacencyWDigraph<float>::costOfBestTourSoFar;
float adjacencyWDigraph<float>::costOfPartialTour;
int* adjacencyWDigraph<double>::partialTour;
int* adjacencyWDigraph<double>::bestTourSoFar;
double adjacencyWDigraph<double>::costOfBestTourSoFar;
double adjacencyWDigraph<double>::costOfPartialTour;

template<class T>
ostream& operator<<(ostream& out, const adjacencyWDigraph<T>& x)
{
	x.output(out);
	return out;
}

#endif // !adjacencyWDigraph_


//抽象类graph

#ifndef graph_
#define graph_

#include "edge.h"
#include "vertexIterator.h"
#include "arrayQueue.h"
#include "arrayStack.h"
#include "myExceptions.h"
#include "binNode.h"
#include "weightedEdge.h"
#include "minHeap.h"
#include "fastUnionFind.h"
#include "arrayListWithIterator.h"

using namespace std;

template<class T>
class graph
{
public:
	virtual ~graph() {}
	virtual int numberOfVertices() const = 0;
	virtual int numberOfEdges() const = 0;
	virtual bool existsEdge(int, int) const = 0;
	virtual void insertEdge(edge<T>*) = 0;
	virtual void eraseEdge(int, int) = 0;
	virtual int degree(int) const = 0;
	virtual int inDegree(int) const = 0;
	virtual int outDegree(int) const = 0;
	virtual bool directed() const = 0;
	virtual bool weighted() const = 0;
	virtual vertexIterator<T>* iterator(int) = 0;
	virtual void output(ostream&) const = 0;

	//广度遍历
	//reach用来标记从顶点v可到达的所有顶点
	virtual void bfs(int v, int reach[], int label)
	{
		//q初始时仅包含顶点v
		arrayQueue<int> q(10);
		reach[v] = label;
		q.push(v);
		while (!q.empty())
		{
			//从队列中删除一个标记过的点
			int w = q.front();
			q.pop();

			//标记所有没有到达的邻接于顶点w的顶点
			vertexIterator<T>* iw = iterator(w);
			int u;
			while ((u = iw->next()) != 0)
				if (reach[u] == 0)
				{//如果未被标记过
					q.push(u);
					reach[u] = label;
				}
			delete iw;
		}
	}

	void dfs(int v, int reach[], int label)
	{
		graph<T>::reach = reach;
		graph<T>::label = label;
		rDfs(v);
	}

	//寻找从theSource到theDestination的路径
	//返回一个数组path,从索引1开始表示路径。path[0]表示路径长度
	int* findPath(int theSource, int theDestination)
	{
		int n = numberOfVertices();
		path = new int[n + 1];
		path[1] = theSource;
		length = 1;
		destination = theDestination;
		reach = new int[n + 1];
		for (int i = 1; i <= n; i++)
			reach[i] = 0;

		if (theSource == theDestination || rFindPath(theSource))
			path[0] = length - 1;
		else
		{
			delete[] path;
			path = NULL;
		}
		delete[] reach;
	}

	//确定一个无向图是否连通
	bool connected()
	{
		if (directed())
			throw undefinedMethod("graph::connected() not defined for directed graphs");

		int n = numberOfVertices();

		reach = new int[n + 1];

		dfs(1, reach, 1);

		for (int i = 1; i <= n; i++)
			if (reach[i] == 0)
				return false;
		return true;
	}

	//给无向图的构件做标记，返回构件的个数，c[i]是顶点i的构件号
	int labelComponents(int c[])
	{
		if (directed())
			throw undefinedMethod("graph::labelComponents() not defined for directed graphs");
		int n = numberOfVertices();

		for (int i = 1; i <= n; i++)
			c[i] = 0;

		label = 0;

		for(int i=1;i<=n;i++)
			if (c[i] == 0)
			{
				label++;
				bfs(i, c, label);
			}
		return label;
	}
	
	bool topologicalOrder(int* theOrder)
	{
		if (!directed())
			throw undefinedMethod("graph::tolopogicalOrder() not defined for undirected graphs");

		int n = numberOfVertices();

		int* inDegree = new int[n + 1];
		fill(inDegree + 1, inDegree + n + 1, 0);
		for (int i = 1; i <n n; i++)
		{
			vertexIterator<T>* ii = iterator(i);
			int u;
			while ((u=ii->next())!=0)
			{
				inDegree[u]++;
			}
			arrayStack<int> stackl
				for (int i = 1; i <= n; i++)
					if (inDegree[i] == 0)
						stack.push(i);
			int j = 0;
			while (!stack.empty())
			{
				int nextVertex = stack.top();
				stack.pop();
				theOrder[j++] = nextVertex;
				
				vertexIterator<T>* iNextVertex = iterator(nextVertex);
				int u;
				while ((u = iNextVertex->next()) != 0)
				{
					inDegree[u]--;
					if (inDegree[u] == 0)
						stack.push(u);
				}
			}
			return (j == n);
		}
	}

	int bipartiteCover(int *theLabel, int *theCover)
	{// Return -1 if the bipartite graph has no cover.
	 // Return cover size if there is a cover.
	 // theLabel is bipartite labeling, theLabel[i] = 1 iff i is in A.
	 // theCover[i], i >= 0 is set to the cover (if there is one).
		int n = numberOfVertices();

		// create structures
		int sizeOfA = 0;
		for (int i = 1; i <= n; i++) // find size of set A
			if (theLabel[i] == 1)
				sizeOfA++;
		int sizeOfB = n - sizeOfA;
		createBins(sizeOfB, n);
		int *newVerticesCovered = new int[n + 1];
		// vertex i covers newVerticesCovered[i] uncovered vertices of B
		bool *changed = new bool[n + 1];
		// changed[i] is true iff newVerticesCovered[i] has changed
		fill(changed + 1, changed + n + 1, false);
		bool *covered = new bool[n + 1];
		// covered[i] is true iff vertex i is covered
		fill(covered + 1, covered + n + 1, false);
		arrayStack<int> stack;

		// initialize
		for (int i = 1; i <= n; i++)
			if (theLabel[i] == 1)
			{// i is in A
				newVerticesCovered[i] = degree(i); // i covers this many
				insertBins(newVerticesCovered[i], i);
			}

		// construct cover
		int numberCovered = 0, // # of B vertices covered
			maxBin = sizeOfB;  // max bin that may be nonempty
		int coverSize = 0;     // number of A vertices in cover
		while (maxBin > 0)     // search all bins
			if (bin[maxBin] != 0)            // bin maxBin is not empty
			{
				int v = bin[maxBin];          // first vertex
				theCover[coverSize++] = v;    // add v to cover
											  // label newly covered vertices
				vertexIterator<T> *iv = iterator(v);
				int j;
				while ((j = iv->next()) != 0)
				{
					if (!covered[j])          // j not covered yet
					{
						covered[j] = true;
						numberCovered++;
						// update newVerticesCovered
						vertexIterator<T> *ij = iterator(j);
						int k;
						while ((k = ij->next()) != 0)
						{
							newVerticesCovered[k]--;        // j does not count
							if (!changed[k])
							{
								stack.push(k);  // stack once only
								changed[k] = true;
							}
						}
					}
				}
				// update bins
				while (!stack.empty())
				{
					int k = stack.top();
					stack.pop();
					changed[k] = false;
					moveBins(sizeOfB, newVerticesCovered[k], k);
				}
			}
			else maxBin--; // go to next bin

			return (numberCovered == sizeOfB) ? coverSize : -1;
	}

	bool kruskal(weightedEdge<T> *spanningTreeEdges)
	{// Find a min cost spanning tree using Kruskal's method.
	 // Return false iff the weighted undirected graph is not connected.
	 // spanningTreeEdges[0:n-2] has the min-cost-tree edges when done.
		if (directed() || !weighted())
			throw undefinedMethod
			("graph::kruskal() not defined for unweighted and directed graphs");

		int n = numberOfVertices();
		int e = numberOfEdges();
		// set up array of graph edges
		weightedEdge<T> *edge = new weightedEdge<T>[e + 1];
		int k = 0;        // cursor for edge[]
		for (int i = 1; i <= n; i++)
		{// get all edges incident to i
			vertexIterator<T> *ii = iterator(i);
			int j;
			T w;
			while ((j = ii->next(w)) != 0)
				if (i < j)  // add to edge array
					edge[++k] = weightedEdge<int>(i, j, w);
		}
		// put edges in min heap
		minHeap<weightedEdge<T> > heap(1);
		heap.initialize(edge, e);

		fastUnionFind uf(n); // union/find structure

							 // extract edges in cost order and select/reject
		k = 0;  // use as cursor for t now
		while (e > 0 && k < n - 1)
		{// spanning tree not complete & edges remain
			weightedEdge<T> x = heap.top();
			heap.pop();
			e--;
			int a = uf.find(x.vertex1());
			int b = uf.find(x.vertex2());
			if (a != b)
			{// select edge x
				spanningTreeEdges[k++] = x;
				uf.unite(a, b);
			}
		}
		return (k == n - 1);
	}

	void bellmanFord(int s, T *d, int *p)
	{// Bellman and Ford algorithm to find the shortest paths from vertex s.
	 // Graph may have edges with negative cost but should not have a
	 // cycle with negative cost.
	 // Shortest distances from s are returned in d.
	 // Predecessor info in returned p.
		if (!weighted())
			throw undefinedMethod
			("graph::bellmanFord() not defined for unweighted graphs");

		int n = numberOfVertices();
		if (s < 1 || s > n)
			throw illegalParameterValue("illegal source vertex");

		// define two lists for vertices whose d has changed
		arrayList<int> *list1 = new arrayList<int>;
		arrayList<int> *list2 = new arrayList<int>;

		// define an array to record vertices that are in list2
		bool *inList2 = new bool[n + 1];

		// initialize p[1:n] = 0 and inList2[1:n] = false
		fill(p + 1, p + n + 1, 0);
		fill(inList2 + 1, inList2 + n + 1, false);

		// set d[s] = d^0(s) = 0
		d[s] = 0;
		p[s] = s;  // p[i] != 0 means vertex i has been reached
				   // will later reset p[s] = 0

				   // initialize list1
		list1->insert(0, s);

		// do n - 1 rounds of updating d
		for (int k = 1; k < n; k++)
		{
			if (list1->empty())
				break;  // no more changes possible
						// process vertices on list1
			for (arrayList<int>::iterator iList1 = list1->begin();
				iList1 != list1->end(); ++iList1)
			{// update d for the neighbors v of vertex u = *iList1
				int u = *iList1;
				vertexIterator<T> *iu = iterator(u);
				int v;
				T w;
				while ((v = iu->next(w)) != 0)
				{
					if (p[v] == 0 || d[u] + w < d[v])
					{
						// this is either the first path to v
						// or is a shorter path than earlier ones
						d[v] = d[u] + w;
						p[v] = u;
						// put v into list2 unless it is already there
						if (!inList2[v])
						{// put at end of list
							list2->insert(list2->size(), v);
							inList2[v] = true;
						}
					}
				}
			}

			// set list1 and list2 for next update round
			list1 = list2;
			list2 = new arrayList<int>;

			// reset inList2[1:n] to false
			for (arrayList<int>::iterator iList1 = list1->begin();
				iList1 != list1->end(); ++iList1)
				inList2[*iList1] = false;
		}
		p[s] = 0;  // s has no predecessor
	}

protected:
	static int* reach;
	static int* path;
	static int label;
	static int length;
	static int destination;
	static int* bin;
	static binNode* node;

	void rDfs(int v)
	{
		reach[v] = label;
		vertexIterator<T>* iv = iterator(v);
		int u;
		while ((u = iv->next()) != 0)
			if (reach[u] != 0)
				rDfs(u);
		delete iv;
	}

	bool rFindPath(int s)
	{//搜寻路径的实际算法。从顶点s开始实施深度优先搜索
		//顶点s不应该等于终点
		//当且仅当一条路径找到了，返回true
		reach[s] = 1;
		vertexIterator<T>* is = iterator(s);
		int u;
		while ((u = is->next()) != 0)
		{
			if (reach[u] == 0)
			{
				path[++length] = u;
				if (u == destination || rFindPath(u))
					return true;
				length--;
			}
		}
		delete is;
		return false;

	}

	void createBins(int b, int n)
	{//创建b个空bin和n个node
		bin = new int[b + 1];
		fill(bin, bin + b + 1, 0);
		node = new binNode[n + 1];
	}

	void insertBins(int b, int v)
	{//在bin b中插入v
		if (b == 0)
			return;
		node[v].left = b;
		if (bin[b] != 0)
			node[bin[b]].left = v;
		node[v].right = bin[b];
		bin[b] = v;
	}

	void moveBins(int bMax, int toBin, int v)
	{//将vertex v从current bin移到 toBin
		//bMax is rightmost nonempty bin
		//nodes to the left and right of v
		int l = node[v].left;
		int r = node[v].right;

		if (r != 0)
			node[r].left = node[v].left;
		if (l > bMax || bin[l] != v)
			node[l].right = r;
		else
			bin[l] = r;
		insertBins(toBin, v);
	}
};
int* graph<bool>::reach;
int graph<bool>::label;
int* graph<bool>::path;
int graph<bool>::length;
int graph<bool>::destination;
int* graph<bool>::bin;
binNode* graph<bool>::node;
int* graph<int>::reach;
int graph<int>::label;
int* graph<int>::path;
int graph<int>::length;
int graph<int>::destination;
int* graph<int>::bin;
binNode* graph<int>::node;
int* graph<float>::reach;
int graph<float>::label;
int* graph<float>::path;
int graph<float>::length;
int graph<float>::destination;
int* graph<float>::bin;
binNode* graph<float>::node;
int* graph<double>::reach;
int graph<double>::label;
int* graph<double>::path;
int graph<double>::length;
int graph<double>::destination;
int* graph<double>::bin;
binNode* graph<double>::node;

#endif // !graph_


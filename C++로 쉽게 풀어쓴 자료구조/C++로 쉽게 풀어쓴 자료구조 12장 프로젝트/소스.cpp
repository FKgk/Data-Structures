#include <iostream>
#include <cstdlib>
#include <ctime>
#pragma warning(disable:4996)
#define MAX_VTXS 256
#define INF 9999
#define MAX_ELEMENT 200
using std::cout;
using std::cin;
using std::endl;

class Graph
{
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
	int label[MAX_VTXS];
	bool visited[MAX_VTXS];

public:
	Graph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, 0);
			label[i] = 0;
			visited[i] = false;
		}
	}
	void resetVisited() {
		for (int i = 0; i < MAX_VTXS; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) == 1; }
	bool isFull() { return size >= MAX_VTXS; }
	bool isEmpty() { return size == 0; }

	void insertVertex(char name)	// 그래프에 정점 v를 삽입힌다.
	{
		if (isFull())
			cout << "정점의 개수 초과" << endl;
		else
		{
			vertices[size] = name;
			size++;
		}
	}
	void insertEdge(int u, int v)	//그래프에 간선 (u, v)를 삽입힌다.
	{
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	void deleteVertex(int v)	// 그래프의 정접 v를 삭제한다.
	{

	}
	void deleteEdge(int u, int v)	//그래프의 간선 (u, v)를 삭제한다.
	{
		setEdge(u, v, 0);
		setEdge(v, u, 0);
	}
	int * adjacent(int v)	// 정점 v에 인접한 모든 정점의 집합을 반환한다.
	{

	}
	void display(FILE *fp = stdout)
	{
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++)
		{
			fprintf(fp, "%c", getVertex(i));
			for (int j = 0; j < size; j++)
			{
				fprintf(fp, "%6d", getEdge(i, j));
			}
			fprintf(fp, "\n");
		}
	}

	void store(char * filename)
	{
		FILE *fp = fopen(filename, "w");
		if (fp != NULL)
		{
			display(fp);
			fclose(fp);
		}
		else
			cout << "파일 열기 실패" << endl;
	}

	void randomGraph(int numVtx, int numEdge)	// 정점의 수와 간선의 수를 입력하면 무작위로 그래프를 발생시키는 함수
	{
		srand((unsigned)time(NULL));
		int count = 0;
		for (int i = 0; i < numVtx; i++)
		{
			insertVertex('A' + i);
		}
		while (count < numEdge)
		{
			for (int i = 0; i < numVtx; i++)
			{
				for (int j = 0; j < i; j++)
				{
					if (count == numEdge)
						break;
					if (rand() % 2 == 1)
					{
						insertEdge(i, j);
						count++;
					}
					else
					{
						setEdge(i, j, 0);
						setEdge(j, i, 0);
					}
				}
			}
		}
	}

	void labelDFS(int v, int color)
	{
		label[v] = color;
		visited[v] = true;
		cout << getVertex(v) << " ";
		for (int i = 0; i < size; i++)
		{
			if (getEdge(v, i) == 1 && visited[i] == false)
				labelDFS(i, color);
		}
	}

	void findConnectedComponent()
	{
		int count = 1;
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == false)
				labelDFS(i, count++);
		}
		cout << "\n그래프 연결성분 개수 = " << count << endl;
		for (int i = 0; i < size; i++)
			cout << getVertex(i) << " = " << label[i] << " ";
		cout << endl;

	}
	bool findConnectedComponetReturn()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == false)
				labelDFS(i, ++count);
		}
		return count == 1;
	}
	void randomConnectedGraph(int numVtx)	// 정점의 수를 입력하면 무작위로 연결 그래프를 발생시키는 함수
	{
		srand((unsigned)time(NULL));

		for (int i = 0; i < numVtx; i++)
		{
			insertVertex('A' + i);
		}

		do
		{
			reset();
			size = numVtx;
			for (int i = 0; i < numVtx; i++)
				for (int j = 0; j < i; j++)
					if (rand() % 2 == 1)
						insertEdge(i, j);
		} while (findConnectedComponetReturn() == false);
	}
	int findBridge()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (getEdge(i, j) == 1)
				{
					deleteEdge(i, j);
					if (findConnectedComponetReturn() == false)
					{
						count++;
					}
					insertEdge(i, j);
					resetVisited();
				}
			}
		}

		return count;
	}
};

class VertexSets
{
	int parent[MAX_VTXS];	// 부모 정점의 id
	int nSets;				// 집합의 개수

public:
	VertexSets(int n) :nSets(n) // 모든 정점이 고유의 집합에 속함
	{
		for (int i = 0; i < nSets; i++)
			parent[i] = -1;
	}
	bool isRoot(int i) { return parent[i] < 0; }
	int findSet(int v)			// v가 속한 집합의 root노드를 찾아 반환
	{
		while (!isRoot(v))
			v = parent[v];
		return v;
	}
	void unionSets(int s1, int s2)	// 집합 s1을 집합 s2에 합침
	{
		parent[s1] = s2;
		nSets--;
	}
};

class HeapNode
{
	int key;
	int v1, v2;
public:
	HeapNode(int k = INF, int u = -1, int v = -1) :key(k), v1(u), v2(v) { }
	void setKey(int k, int u, int v) { key = k; v1 = u; v2 = v; }
	int getKey() { return key; }
	int getv1() { return v1; }
	int getv2() { return v2; }
};

class MinHeap
{
	HeapNode node[MAX_ELEMENT];
	int size;
public:
	MinHeap() :size(0) { }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }
	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key, int u, int v)
	{
		if (isFull())return;
		int i = ++size;
		while (i != 1 && key < getParent(i).getKey())
		{
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key, u, v);
	}
	HeapNode remove()
	{
		if (isEmpty())return NULL;
		HeapNode root = node[1];
		HeapNode last = node[size--];
		int parent = 1;
		int child = 2;
		while (child <= size)
		{
			if (child < size && getLeft(parent).getKey() > getRight(parent).getKey())
				child++;
			if (last.getKey() <= node[child].getKey()) break;
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;
		return root;
	}
};

class WGraph : public Graph
{

public:
	void insertEdge(int u, int v, int weight)
	{
		if (weight >= INF) weight = INF;
		setEdge(u, v, weight);
		setEdge(v, u, weight);
	}

	bool hasEdge(int i, int j) { return getEdge(i, j) < INF; }
	void reset(int maxWeight = 10000) {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, maxWeight);
			label[i] = 0;
			visited[i] = false;
		}
	}
	void load(char * filename)
	{
		FILE *fp = fopen(filename, "r");

		if (fp != NULL)
		{
			int n;
			fscanf(fp, "%d", &n);
			for (int i = 0; i < n; i++)
			{
				char str[80];
				int val;
				fscanf(fp, "%s", str);
				insertVertex(str[0]);
				for (int j = 0; j < n; j++)
				{
					fscanf(fp, "%d", &val);
					insertEdge(i, j, val);
				}
			}
			fclose(fp);
		}
	}

	void Kruskal()
	{
		MinHeap heap;
		// 힙에 모든 간선 삽입
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (hasEdge(i, j))
					heap.insert(getEdge(i, j), i, j);

		VertexSets set(size);

		int edgeAccepted = 0;
		while (edgeAccepted < size - 1)
		{
			HeapNode e = heap.remove();
			int uset = set.findSet(e.getv1());
			int vset = set.findSet(e.getv2());

			if (uset != vset)
			{
				cout << "간선 추가 : " << getVertex(e.getv1()) << " - " << getVertex(e.getv2()) << " (비용:" << e.getKey() << ")" << endl;
				set.unionSets(uset, vset);
				edgeAccepted++;
			}
		}
	}

	void Prim(int s)
	{
		bool selected[MAX_VTXS];	// 정점이 이미 포함되었는 지 확인
		int dist[MAX_VTXS];			// 거리
		for (int i = 0; i < size; i++)	// 배열 초기화
		{
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0;	// 시작 정점

		for (int i = 0; i < size; i++)
		{
			// 포함되지 않은 정점들 중에서 MST와의 거리가 최소인 정점
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] == INF) return;
			cout << getVertex(u) << " ";
			for (int v = 0; v < size; v++)
				if (getEdge(u, v) != INF)
					if (!selected[v] && getEdge(u, v) < dist[v])
						dist[v] = getEdge(u, v);
		}
		cout << endl;
	}

	//	MST에 포함되지 않은 정점들 중에서 MST와의 거리(dist)가 최소인 정점 선택
	int getMinVertex(bool* selected, int * dist)
	{
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v <size; v++)
			if (!selected[v] && dist[v] < mindist)
			{
				mindist = dist[v];
				minv = v;
			}
		return minv;
	}
	void labelDFS(int v, int color, int maxWeight = 10000)
	{
		label[v] = color;
		visited[v] = true;
		cout << getVertex(v) << " ";
		for (int i = 0; i < size; i++)
		{
			if (getEdge(v, i) < maxWeight && getEdge(v, i) > 0 && visited[i] == false)
				labelDFS(i, color, maxWeight);
		}
	}

	bool findConnectedComponetReturn(int maxWeight = 10000)
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == false)
				labelDFS(i, ++count, maxWeight);
		}
		return count == 1;
	}
	void randomConnectedWGraph(int numVtx, int maxWeight = 10000)	// 정점의 수와 가중치를 입력하면 무작위로 연결 그래프를 발생시키는 함수
	{
		srand((unsigned)time(NULL));

		for (int i = 0; i < numVtx; i++)
		{
			insertVertex('A' + i);
		}

		do
		{
			reset();
			size = numVtx;
			for (int i = 0; i < numVtx; i++)
				for (int j = 0; j < i; j++)
					if (rand() % 2 == 1)
						insertEdge(i, j, rand() % maxWeight);
					else
						insertEdge(i, j, INF);
			display();
			cout << " 실행" << endl;
		} while (findConnectedComponetReturn(maxWeight) == false);
	}

};


class WGraphDijkstra : public WGraph
{
	int dist[MAX_VTXS];		// 시작노드로부터의 최단경로 거리
	bool found[MAX_VTXS];	// 방문한 정점 표시
public:
	//방문하지 않은 정점들 중에서 최단경로 거리가 가장 작은 정점을 찾아 반환
	int chooseVertex()	// 우선순위 큐로 대치하면 더 빠르게 수행시킬 수 있다.
	{
		int min = INF;
		int minpos = -1;
		for (int i = 0; i <size; i++)
			if (dist[i] < min && !found[i])
			{
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}

	//Dijkstra의 최단 경로 알고리즘 : star 정점에서 시작함.
	void ShortestPath(int start)
	{
		//최가화
		for (int i = 0; i < size; i++)
		{
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;	// 시작노드 방문 표시
		dist[start] = 0;		// 최초 거리

		for (int i = 0; i < size; i++)
		{
			cout << "Step : " << i + 1;
			printDistance();
			int u = chooseVertex();
			found[u] = true;
			for (int w = 0; w < size; w++)
			{
				if (found[w] == false)
					if (dist[u] + getEdge(u, w) < dist[w])
						dist[w] = dist[u] + getEdge(u, w);
			}
		}

	}
	void printDistance() {
		for (int i = 0; i < size; i++)
			cout << "\t" << dist[i];
		cout << endl;
	}
};

class WGraphFloyd : public WGraph
{
	int A[MAX_VTXS][MAX_VTXS];	//최단경로 거리
public:
	void ShortestPathFloyd()
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				A[i][j] = getEdge(i, j);
		printA();
		for (int k = 0; k<size; k++)
			for (int i = 0; i<size; i++)
				for (int j = 0; j < size; j++)
					if (A[i][k] + A[k][j] < A[i][j])
						A[i][j] = A[i][k] + A[k][j];
		printA();
	}
	void printA()
	{
		cout << "============================" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (A[i][j] == INF) cout << "\tINF";
				else
					cout << "\t" << A[i][j];
			}
			cout << endl;
		}
	}
};


int main(void)
{
	WGraphFloyd g;
	/*
	cout << "MSt By Kruskal's Algorithm" << endl;
	g.Kruskal();
	*/

	/*
	cout << "\nShortest Path By Dijkstra Algorithm" << endl;
	g.ShortestPath(0);
	*/
	g.randomConnectedWGraph(26, 100);
	cout << "\nShortest Path By Floyd Algorithm" << endl;
	//g.ShortestPathFloyd();
}
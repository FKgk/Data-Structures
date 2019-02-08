#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX_VTXS 256
using std::cout;
using std::cin;
using std::endl;

class Graph
{
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
	bool isFull() {	return size >= MAX_VTXS; }
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
				fprintf(fp, "%3d", getEdge(i, j));
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


int main(void)
{
	char fileName[] = "My_Graph.txt";
	Graph graph;

	graph.randomConnectedGraph(5);
	graph.display();
	graph.store(fileName);
	graph.findConnectedComponent();
	cout << "\n 브리지의 개수 : "<<graph.findBridge() << endl;
}
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
	
	void insertVertex(char name)	// �׷����� ���� v�� ��������.
	{
		if (isFull())
			cout << "������ ���� �ʰ�" << endl;
		else
		{
			vertices[size] = name;
			size++;
		}
	}
	void insertEdge(int u, int v)	//�׷����� ���� (u, v)�� ��������.
	{
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	void deleteVertex(int v)	// �׷����� ���� v�� �����Ѵ�.
	{

	}
	void deleteEdge(int u, int v)	//�׷����� ���� (u, v)�� �����Ѵ�.
	{
		setEdge(u, v, 0);
		setEdge(v, u, 0);
	}
	int * adjacent(int v)	// ���� v�� ������ ��� ������ ������ ��ȯ�Ѵ�.
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
			cout << "���� ���� ����" << endl;
	}

	void randomGraph(int numVtx, int numEdge)	// ������ ���� ������ ���� �Է��ϸ� �������� �׷����� �߻���Ű�� �Լ�
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
		cout << "\n�׷��� ���Ἲ�� ���� = " << count << endl;
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
	void randomConnectedGraph(int numVtx)	// ������ ���� �Է��ϸ� �������� ���� �׷����� �߻���Ű�� �Լ�
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
	cout << "\n �긮���� ���� : "<<graph.findBridge() << endl;
}
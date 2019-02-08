#include <iostream>

#define MAX_ELEMENT 101
using std::cout;
using std::cin;
using std::endl;

class Node
{
	int key;
	Node * link;
public:
	Node(int k = 0, Node * l = NULL):key(k),link(l){}
	int getKey() { return key; }
	void setKey(int _key) { key = _key; }
	Node * getLink() { return link; } 
	void setLink(Node * _link) { link = _link; }
	void display() { cout << key << " "; }
};
class MinPriorityQueue
{
	Node * min;
	int size;
public:
	MinPriorityQueue(Node * node = NULL, int s = 0) :min(NULL), size(s) {}
	bool isEmpty() { return size == 0; }
	int getSize() { return size; }
	void insert(Node * node)
	{
		int i = ++size;
		Node * parent = min;
		Node * temp;

		for (int j = 0; j < i / 2; j++)
			parent = parent->getLink();

		while (i != 1 && node->getKey() > parent->getKey())
		{
			temp = parent;
			for (int j = 0; j < i / 2; j++)
				parent = parent->getLink();
			parent->setLink(temp->getLink());
			temp->setKey(parent->getKey());
			i /= 2;
			parent = min;
			for (int j = 0; j < i / 2; j++)
				parent = parent->getLink();
		}
		 
		/*
		size++;
		int i = size;
		while (i != 1 && data > elem[i/2])
		{
			elem[i] = elem[i / 2];
			i /= 2;
		}
		elem[i] = data;
		*/
	}
	int remove()
	{
		if (isEmpty())
			return -1;
		return -2;
	}
	int find()
	{
		if (isEmpty())
			return -1;
		return min->getKey();
	}
	void display()
	{
		int i = 1;
		Node * node = min;
		for (int j = 1; j <= size; j++)
		{
			if (i == j)
			{
				cout << endl;
				i *= 2;
			}
			cout << node->getKey() << " ";
			node = node->getLink();
		}
	}
};
class MaxPriorityQueue // 내림차순 정렬
{
	int elem[MAX_ELEMENT];	// 요소의 배열
	int size;	// 현재 요소의 개수

public:
	MaxPriorityQueue():size(0){}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }
	int getSize() { return size; }
	int *getElem() { return elem; }
	void insert(int data)
	{
		if (isFull())
		{
			cout << "큐가 가득 차 있습니다." << endl;
			return;
		}
		size++;
		int i = size;
		while (i != 1 && data > elem[i/2])
		{
			elem[i] = elem[i / 2];
			i /= 2;
		}
		elem[i] = data;

	}
	int remove()
	{
		if (isEmpty())
		{
			cout << "큐가 비어 있습니다." << endl;
			return -1;
		}
		int item = elem[1];
		int last = elem[size];
		int parent = 1;
		int child = 2;
		size--;
		while (child <= size)
		{
			child = elem[child] > elem[child + 1] ? child : child + 1;
			
			if (last > elem[child])
				break;
			
			elem[parent] = elem[child];
			parent = child;
			child *= 2;
		}

		elem[parent] = last;
		return item;
	}
	int find()
	{
		if (isEmpty())
			return -1;
		return elem[1];
	}
	void display()
	{
		cout << "-------------------" << endl;
		for (int i = 1, level = 1; i <= size; i++)
		{
			if (i == level)
			{
				cout << endl;
				level *= 2;
			}
			cout << elem[i] << " ";
			
		}
	}
	
};
bool isHeapRecur(int a[], int size)
{
	int parent = size / 2;

	if (parent== 0)
		return true;
	if (a[parent] < a[parent * 2] || a[parent] < a[parent * 2 + 1])
		return false;
	return isHeapRecur(a, size - 1);
}
bool isHeapIter(int a[], int size)
{
	int parent = size / 2;
	while (parent != 0)
	{

		if (a[parent] < a[parent * 2] || (parent * 2 + 1 <= size && a[parent] < a[parent * 2 + 1]))
			return false;
		parent /= 2;
	}
	return true;
}
int main(void)
{
	/*
	 
	MaxPriorityQueue que;
	que.insert(9);
	que.insert(7);
	que.insert(6);
	que.insert(5);
	que.insert(4);
	que.insert(3);
	que.insert(2);
	que.insert(2);
	que.insert(1);
	que.insert(3);
	que.insert(8);

	que.display();
	cout << " \n-------------" << endl;
	cout << que.remove() << endl;
	cout << que.remove() << endl;
	cout << que.remove() << endl;
	que.display();
	cout << "\n----------------isHeap?----" << endl;
	cout << isHeapRecur(que.getElem(), que.getSize()) << endl;
	cout << isHeapIter(que.getElem(), que.getSize()) << endl;

	int arr[11] = { 0, 9, 7, 6, 5, 4, 3, 2 , 2, 1, 3 };

	if (isHeapRecur(arr, 11))
		cout << "힙이다" << endl;
	else
		cout << "힙이 아니다" << endl;
	if (isHeapIter(arr, 11))
		cout << "힙이다" << endl;
	else
		cout << "힙이 아니다" << endl;
	*/

	cout << "----------------------MinPriorityQueue-------------------" << endl;
	MinPriorityQueue mque;

	mque.insert( new Node(9));
	mque.insert(new Node(7));
	mque.insert(new Node(6));
	mque.insert(new Node(5));
	mque.insert(new Node(4));
	mque.insert(new Node(3));
	mque.insert(new Node(2));
	mque.insert(new Node(2));
	mque.insert(new Node(1));
	mque.insert(new Node(3));
	mque.insert(new Node(8));


	mque.display();
	cout << " -------------" << endl;
	cout << mque.remove() << endl;
	cout << mque.remove() << endl;
	cout << mque.remove() << endl;
	cout << " -------------" << endl;
	mque.display();

	return 0;
}
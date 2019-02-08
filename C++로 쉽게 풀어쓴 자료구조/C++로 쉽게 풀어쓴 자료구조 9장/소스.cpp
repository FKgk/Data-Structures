#include <iostream>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdio>
using namespace std;
class Node
{
protected:
	int data;
	Node * left;
	Node * right;
public:
	Node(int val = NULL, Node * l = NULL, Node * r = NULL) :data(val), left(l), right(r) {}
	void setData(int val) { data = val; }
	void setLeft(Node * l) { left = l; }
	void setRight(Node * r) { right = r; }
	int getData() { return data; }
	Node *getLeft() { return left; }
	Node *getRight() { return right; }
	bool isLeaf() { return left == NULL && right == NULL; } // ���� ��尡 �ܸ� ������� �˻�
	void inorder()
	{
		if (getLeft() != NULL)
			getLeft()->inorder();
		cout << getData() << endl;
		if (getRight() != NULL)
			getRight()->inorder();
	}
	void preorder()
	{
		if (getLeft() != NULL)
			getLeft()->preorder();
		if (getRight() != NULL)
			getRight()->preorder();
		cout << getData() << endl;
	}
	void postorder()
	{
		cout << getData() << endl;
		if (getLeft() != NULL)
			getLeft()->postorder();
		if (getRight() != NULL)
			getRight()->postorder();
	}

	int getCount()
	{
		if (getLeft() == NULL && getRight() == NULL)
			return 1;
		if (getLeft() != NULL && getRight() == NULL)
			return 1 + getLeft()->getCount();
		if (getRight() != NULL && getLeft() == NULL)
			return 1 + getRight()->getCount();
		if (getRight() != NULL && getLeft() != NULL)
			return 1 + getLeft()->getCount() + getRight()->getCount();

		cout << "56�� ° �� ����ġ ���� ����" << getData() << endl;
		return 0;
	}
	int getHeight()
	{
		if (getLeft() == NULL && getRight() == NULL)
			return 1;
		if (getLeft() != NULL && getRight() == NULL)
			return 1 + getLeft()->getCount();
		if (getRight() != NULL && getLeft() == NULL)
			return 1 + getRight()->getCount();
		if(getRight() != NULL && getLeft() != NULL)
			return 1 + getLeft() -> getCount() > getRight()->getCount() ? getLeft()->getCount() : getRight()->getCount();

		cout << "70�� ° �� ����ġ ���� ����" << getData() << endl;
		return 0;
	}
	int getLeafCount()
	{
		if (getLeft() == NULL && getRight() == NULL)
			return 1;
		if (getLeft() != NULL && getRight() == NULL)
			return getLeft()->getLeafCount();
		if (getLeft() == NULL && getRight() != NULL)
			return getRight()->getLeafCount();
		if(getLeft() != NULL && getRight() != NULL)
			return getLeft()->getLeafCount() + getRight()->getLeafCount();
		cout << "83�� ° �� ����ġ ���� ����" << getData() << endl;
		return 0;
	}

	Node *search(int key) 
	{
		if (key == getData())
			return this;
		else if (key < getData() && left != NULL)
			return getLeft()->search(key);
		else if (key > getData() && right != NULL)
			return getRight()->search(key);
		else return NULL;

	}
	void insert(Node * node)
	{
		if (node->getData() == getData())
			return;
		else if (node->getData() < getData())
		{
			if (getLeft() == NULL)
				setLeft(node);
			else
				getLeft()->insert(node);
		}
		else if (node->getData() > getData())
		{
			if (getRight() == NULL)
				setRight(node);
			else
				getRight()->insert(node);
		}
	}
};

class Tree
{
	Node * root;
public:
	Tree() : root(NULL) {}
	void setRoot(Node * n) { root = n; }
	Node * getRoot() { return root; }
	bool isEmpty() { return root == NULL; }
	void inorder()
	{
		if (isEmpty() != true)
			inorder(root);
	}
	void inorder(Node * node)
	{
		if (node != NULL)
			node->inorder();
	}
	void preorder()
	{
		if (isEmpty() != true)
			preorder(root);
	}
	void preorder(Node * node)
	{
		if (node != NULL)
			node->preorder();
	}
	void postorder()
	{
		if (isEmpty() != true)
			postorder(root);
	}
	void postorder(Node * node)
	{
		if (node != NULL)
			node->postorder();
	}
	void levelorder()
	{
		queue<Node*> que;
		que.push(root);
		while (que.empty() == false)
		{
			Node *x = que.front();
			que.pop();
			if (x != NULL)
			{
				cout << x->getData() << endl;
				que.push(x->getLeft());
				que.push(x->getRight());
			}
		}
	}
	int getCount()
	{
		if (!isEmpty())
			return getCount(root);
		return 0;
	}
	int getCount(Node * node)
	{
		if (node == NULL)
			return 0;
		return node->getCount();
		
		//--------------------------------------------
		//return 1 + getCount(node->getLeft()) + getCount(node->getRight());
	}
	int getHeight() {
		if (isEmpty())
			return 0;
		return getHeight(root);
	}
	int getHeight(Node * node)
	{
		if (node == NULL)
			return 0;
		return node->getHeight();

		//--------------------------------------------
		//return 1 + getCount(node->getLeft()) > getCount(node->getRight()) ? getCount(node->getLeft()) : getCount(node->getRight());
	}
	int getLeafCount()
	{
		if (isEmpty())
			return 0;
		return getLeafCount(root);
	}
	int getLeafCount(Node * node)
	{
		if (node == NULL)
			return 0;
		
		return node->getLeafCount();

		//--------------------------------------------
		//if (node->getLeft() == NULL && node->getRight() == NULL)
		//	return 1;
		//return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}

	//////////////////////////
	bool isFull() // ���� ����Ʈ������ �˻�
	{
		if (isEmpty())
			return false;
		return isFull(root);
	}
	bool isFull(Node *node)
	{
		Node *temp = NULL;
		queue<Node *> que;
		que.push(node);
		while (que.empty() == false)
		{
			temp = que.front();
			que.pop();
			if (temp->isLeaf() == false && node->getLeft() == NULL && node->getRight() != NULL)
				return false;
			if (temp->isLeaf() == false && node->getLeft() != NULL && node->getRight() == NULL)
				return false;
			if (node != NULL)
			{
				if (node->getLeft())
					que.push(node->getLeft());
				if (node->getRight())
					que.push(node->getRight());
			}
		}
		return true;
	}
	int level(int node) // ������ node�� ������ ���ϴ� �Լ� node�� ������ 0��ȯ
	{
		queue<Node *> que;
		que.push(root);
		Node * x;
		int count = 0;
		while (que.empty() == false)
		{
			x = que.front();
			que.pop();
			if (x != NULL)
			{
				count++;
				if (x->getData() == node)
					return (int)(log(count) / log(2)) + 1;
				que.push(x->getLeft());
				que.push(x->getRight());
			}
		}
		return 0;
	}
	////////////////////////////
	bool isBalanced() // ��� ��忡�� ���� ����Ʈ���� ������ ����Ʈ���� ������ ���̰� 2���� ������ �Ǵ� �϶� (���̰� 2�����̸� true)
	{
		if (root == NULL)
			return true;
		return isBalanced(root);
	}
	bool isBalanced(Node * node)
	{
		if (node == NULL)
			return true;
		int leftHeight = getHeight(node->getLeft());
		int rightHeight = getHeight(node->getRight());

		if ((leftHeight - rightHeight) <= 1 && (leftHeight - rightHeight) >= -1
			&& isBalanced(node->getLeft()) && isBalanced(node->getRight()))
			return true;
		return false;
	}
	int pathLength() // ����� ���� ��ȯ ��Ʈ���� ��� �������� ����� ������ ��
	{
		if (isEmpty())
			return 0;
		return pathLength(root);
	}
	int pathLength(Node * node)
	{
		if (node == NULL)
			return 1;
		int l = getHeight() - pathLength(node->getLeft());
		int r = getHeight() - pathLength(node->getRight());

		return getHeight(node) + l + r;
	}
	bool reverse() // �¿�� ��Ī ��Ű�� ������ ����
	{
		if (isEmpty())
			return false;
		reverseNode(root);
		return true;
	}
	void reverseNode(Node * node)
	{
		if (node == NULL)
			return;
		reverseNode(node->getLeft());
		reverseNode(node->getRight());
		Node * temp = node->getLeft();
		node->setLeft(node->getRight());
		node->setRight(temp);

	}
	/////////////
	bool isDisjointFrom(Tree * that) // ���� Ʈ���� that Ʈ���� ���� ��带 ������ �ִ� �� �Ǵ��϶� (������ ������ false)
	{
		return findNode(that->getRoot());
	}
	bool findNode(Node * node)
	{
		if (node == NULL)
			return true;
		queue<Node *> que;
		que.push(root);
		Node * x;
		int count = 0;
		while (que.empty() == false)
		{
			x = que.front();
			que.pop();
			if (x != NULL)
			{
				count++;
				if (x->getData() == node->getData())
					return false;
				que.push(x->getLeft());
				que.push(x->getRight());
			}
		}
		return true && findNode(node->getLeft()) && findNode(node->getRight());
	}
	bool isValid() // ��� ����Ʈ���� ���� �и��Ǿ� �ִ� �� �Ǵ��϶� ( �и��Ǿ� ������ true)
	{

	}
	// isFull, isBalanced, isValid

	Node * search(int key)
	{
		return search(getRoot(), key);
	}
	Node * search(Node * node, int key)
	{
		if (node == NULL)
			return NULL;
		return node->search(key);
	}
	void insert(Node * node)
	{
		if (node == NULL)
			return;
		else if (isEmpty())
			setRoot(node);
		else 
			getRoot()->insert(node);
	}
	void remove(int key)
	{
		if (isEmpty()) return;
		Node * parent = NULL;	// ���� ����� �θ�
		Node * node = root;		// ���� ���
		while (node != NULL && node->getData() != key)
		{
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}
		//���� ��尡 Ʈ���� ����.
		if (node == NULL)
		{
			cout << "Error : key is not in the tree" << endl;
			return;
		}
		// ���� ��尡 Ʈ���� ����.
		else
			remove(parent, node);
	}
	void remove(Node * parent, Node * node)
	{
		// case 1 : ���� �Ϸ��� ��尡 �ܸ� ����� ��� 

		if (node->isLeaf())
		{
			if (parent == NULL) // ������°� ��.
				root = NULL;
			else
			{
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}

		// case 2 : �����Ϸ��� ��尡 �����̳� ������ �ڽĸ� ���� ���
		else if (node->getLeft() == NULL || node->getRight() == NULL)
		{
			//������ ����� ������ �ڽ� ��� => child
			Node * child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();
			//������ ��尡 root�̸� child�� ���ο� root�� �ȴ�.
			if (child == root)
				root = child;
			//�ƴϸ� �θ����� �ڽ����� �ڽ� ��� child�� ���� ����
			if (parent->getLeft() == node)
				parent->setLeft(child);
			else
				parent->setRight(child);
		}

		// case 3 : �����Ϸ��� ��尡 2���� �ڽ��� ��� �ִ� ���
		else
		{
			//�����Ϸ��� ����� ������ ����Ʈ������ ���� ū ��带 Ž��
			Node * succ = node->getRight();	//succ => �İ� ��� : ���� �� ����Ʈ������ ���� key�� ���� ���
			Node * succp = node;	//succp => �İ����� �θ� ���
			
			while (succ->getLeft() != NULL)	//�İ� ��� Ž��
			{
				succp = succ;	//�İ� ����� �θ� ���
				succ = succ->getLeft();	//�İ� ���
			}
			// �İ����� �θ�� �İ� ����� ������ �ڽ��� ���� ����
			if (succ->getLeft() != NULL)
			{
				succp->setLeft(succ->getRight());
			}
			//�İ� ��尡 ������ ����� �ٷ� ������ �ڽ��� ���
			else
			{
				succp->setRight(succ->getRight());
			}
			// �İ� ��� ������ ������ ��忡 ����
			node->setData(succ->getData());
			// ������ ��带 �İ� ���� ���� : �����δ� �İ��尡 ���ŵ�
			// ������ ��忡 �İ��带 �����ϰ� �İ��带 �����Ѵ�.
			node = succ;
		}
		delete node;
	}

	// ��ȯ�� �ƴ� �˻� ���
	Node * searchWithWhile(int key)
	{
		Node * temp = getRoot();
		while (temp != NULL)
		{
			if (temp->getData() == key)
			{
				cout << "Ž�� ����" << endl;
				return temp;
			}
			else if (temp->getData() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		cout << "Ž�� ����" << endl;
	}
};
int sequentialSearch(int list[], int n, int key)
{
	for (int i = 0; i < n; i++)
		if (list[i] == key)
			return i;
	return -1;
}
int main(void)
{
	Tree tree;
	int *arr;
	clock_t start;
	double duration = 0;
	int ans_i;
	Node * ans_n;
	srand((unsigned)time(NULL));
	for (int n = 1000000; n <= 5000000; n += 1000000)
	{
		arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = rand() % 10000 + 1;
	
		start = clock();
		ans_i = sequentialSearch(arr, n, 5000);
		cout << "n�� " << n << "�϶� ��� �ð� : " << (clock() - start)  << "\t";
		cout << ans_i << endl;
	}
	cout << "-----------------------------------" << endl;
	cout << clock() << endl;
	for (int n = 1000000; n <= 5000000; n += 1000000)
	{
		for (int i = 0; i < n; i++)
			tree.insert( new Node(rand() % 10000 + 1));
		
		start = clock();
		ans_n = tree.search(500);
		cout << "n�� " << n << "�϶� ��� �ð� : " << (clock() - start)  << "\t";
		cout << ans_n << endl;
	}
	return 0;
}
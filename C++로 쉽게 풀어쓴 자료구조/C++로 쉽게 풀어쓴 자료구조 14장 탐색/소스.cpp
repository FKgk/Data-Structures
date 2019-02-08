#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#define MAX_LIST 20

using std::cout;
using std::endl;
using std::queue;

// ������ �迭 ����
void randomNumber(int list[])	// ���� �迭 ����
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_LIST; i++)
		list[i] = rand();
}
// ���� Ž��
int sequentialSearch(int list[], int key, int low, int high)	// ���ĵ��� ���� �迭���� ���� Ž��
{
	for (int i = 0; i <= high; i++)
		if (list[i] == key)
			return i;
	return -1;
}
int sortedSequentialSearch(int list[], int key, int low, int high)	// ���ĵ� �迭������ ���� Ž��
{
	if (key <list[low] || key > list[high])return -1;
	for (int i = low; i <= high; i++)
	{
		if (list[i] > key)return -1;
		if (list[i] == key) return i;
	}
}
// ���ĵ� �迭���� ���� Ž��
int binarySearch(int list[], int key, int low, int high)	// ���ȣ���� �̿��� ����Ž��
{
	if (low <= high)	// �ϳ� �̻��� �׸��� �־�� Ž��
	{
		int middle = (low + high) / 2;
		if (list[middle] == key) return middle;	// Ž�� ����
		else if (key < list[middle]) return binarySearch(list, key, low, middle - 1);	// ���� �κи���Ʈ Ž��
		else return binarySearch(list, key, middle + 1, high);	// ������ �κи���Ʈ Ž��
	}
	return -1;	// Ž�� ����
}
int binarySearchIter(int list[], int key, int low, int high) // �ݺ����� �̿��� ����Ž��
{
	if (low <= high)	// �׸���� ���� ������ (���� ����)
	{
		int middle = (low + high) / 2;
		if (key == list[middle]) return middle;				// Ž�� ����
		else if (key > list[middle]) low = middle + 1;		// key�� middle�� ������ ũ�� middle + 1 ~ high ���� �˻�
		else high = middle - 1;								// key�� middle�� ������ ������ low ~ middle - 1 ���� �˻�
	}
	return -1;												// Ž�� ����
}
// ���� ���� Ž��
struct Index {
	int key;	// Ű ��
	int index;	// Ű ���� �ε���
};
int indexedSearch(int list[], int nList, Index *tbl, int nTbl, int key)	// ���� ���� Ž�� nList �׸��� ��, nTbl �ε��� ���̺��� ũ�� ���⵵ = O(nTbl + nList / nTbl)
{
	if (key <list[0] || key > list[nList - 1]) return -1;	// Ű ���� ����Ʈ ���� ��
	for (int i = 0; i < nTbl - 1; i++)	// �ε��� ���̺� ����
	{
		if (tbl[i].key <= key && tbl[i + 1].key > key)
			return sequentialSearch(list, key, tbl[i].index, tbl[i + 1].index);
	}
	return sequentialSearch(list, key, tbl[nTbl - 1].index, nList);
}
// ���� Ž��
int interpolationSearch(int list[], int nList, int key)		// ���� Ž�� ���⵵ = O(log2n)
{
	int low = 0;
	int high = nList - 1;
	while ((list[low] < key) && (key <= list[high]))
	{
		int j = (int)((double)(key - list[low]) / (list[high] - list[low])*(high - low)) + low;

		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else return j;							// Ž�� ����
	}
	return -1;									// Ž�� ����
}

// AVL Ʈ��
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
		if (getRight() != NULL && getLeft() != NULL)
			return 1 + getLeft()->getCount() > getRight()->getCount() ? getLeft()->getCount() : getRight()->getCount();

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
		if (getLeft() != NULL && getRight() != NULL)
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
				cout << x->getData() << " ";
				que.push(x->getLeft());
				que.push(x->getRight());
			}
		}
		cout << endl;
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

class AVLTree : public Tree
{
public:
	int getHeightDiff(Node * node)		// ����� �����μ��� ��ȯ
	{
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return hLeft - hRight;
	}

	Node *rotateLL(Node *parent)		// LL ȸ�� �Լ�
	{
		Node * child = parent->getLeft();
		parent->setLeft(child->getRight());
		child->setRight(parent);
		return child;
	}
	Node *rotateRR(Node *parent)		// RR ȸ�� �Լ�
	{
		Node * child = parent->getRight();
		parent->setRight(child->getLeft());
		child->setLeft(parent);
		return child;
	}
	Node *rotateRL(Node * parent)		// RL ȸ�� �Լ�
	{
		Node * child = parent->getRight();
		parent->setRight(rotateLL(child));
		return rotateRR(parent);
	}
	Node *rotateLR(Node * parent)		// LR ȸ�� �Լ�
	{
		Node * child = parent->getLeft();
		parent->setLeft(rotateRR(child));
		return rotateLL(parent);
	}

	Node *reBalance(Node * parent)		// Ʈ���� ����Ʈ���� �����
	{
		int hDiff = getHeightDiff(parent);
		if (hDiff > 1)
		{
			if (getHeightDiff(parent->getLeft()) > 0)
				parent = rotateLL(parent);
			else
				parent = rotateLR(parent);
		}
		else if (hDiff < -1)
		{
			if (getHeightDiff(parent->getRight()) < 0)
				parent = rotateRR(parent);
			else
				parent = rotateRL(parent);
		}
		return parent;
	}
	void insert(int data)			// AVL Ʈ���� ���� ����
	{
		if (isEmpty()) setRoot(new Node(data));
		else setRoot(insertAVL(getRoot(), data));
	}
	Node * insertAVL(Node * parent, int data)
	{
		if (data < parent->getData())
		{
			if (parent->getLeft() != NULL)
				parent->setLeft(insertAVL(parent->getLeft(), data));
			else
				parent->setLeft(new Node(data));
			return reBalance(parent);
		}
		else if (data > parent->getData())
		{
			if (parent->getRight() != NULL)
				parent->setRight(insertAVL(parent->getRight(), data));
			else
				parent->setRight(new Node(data));
			return reBalance(parent);
		}
		else 
		{
			cout << "�ߺ��� Ű����" << endl;
			return NULL;
		}
	}
};

// �ؽ��� �̿��� Ž��
#define KEY_SIZE 64		// Ž��Ű�� �ִ� ����
#define VALUE_SIZE 64	// Ž��Ű�� ���õ� ����
#define TABLE_SIZE 13	// �ؽ� ���̺� ũ��

inline int transform(const char *key)
{
	int number = 0;
	while (*key)
		number += (*key++);
	return number;
}
inline int hashFunction(const char *key)
{
	return transform(key) & TABLE_SIZE;
}

class Record
{
	char key[KEY_SIZE];		// Ű �ʵ� (������ ��� "�ܾ�")
	char value[VALUE_SIZE];	// Ű�� ���õ� �ڷ�("�ǹ�")
public:
	Record(const char *k = "", const char *v = "") { set(k, v); }
	void set(const char *k, const char * v)
	{
		strcpy(key, k);
		strcpy(value, v);
	}
	char *getKey() { return key; }
	void reset() { set("", ""); }
	bool isEmpty() { return key[0] == '\0'; }
	bool equal(const char *k) { return strcmp(k, key) == 0; }
	void display() { cout << key << "\t" << value << endl; }
};

class HashMap
{
	Record table[TABLE_SIZE];
public:
	HashMap() { reset(); }
	void reset()		// ��� ������ �����.
	{
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i].reset();
	}
	void display()		// ���� ��ü ������ ���
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << i << " ";
			table[i].display();
		}
	}
	void addLinearProb(const char * key, const char * value)	// ���� ������� �̿��� ����
	{
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false)
		{
			if (table[i].equal(key))
			{
				cout << key << " Ž�� Ű�� �ߺ��Ǿ����ϴ�." << endl;
				return;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue)
			{
				cout << key << " ���̺��� ���� á���ϴ�." << endl;
				return;
			}
		}
		table[i].set(key, value);
	}
	Record* searchLinearProb(const char *key)				// ���� ������� �̿��� Ű�� Ž��
	{
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false)
		{
			if (table[i].equal(key))
			{
				cout << key << " Ž�� ���� " << i << endl;
				table[i].display();
				return table + i;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue)break;
		}
		cout << key << " Ž�� ����: ã�� ���� ���̺� ����" << endl;
		return NULL;
	}
};

class hashNode : public Record	//����ȸ���Ʈ�� ���� ��� Ŭ����
{
	hashNode * link;			// ���� ��带 ����Ű�� ������ ����
public:
	hashNode(const char *key, const char *val) : Record(key, val), link(NULL) {}
	hashNode *getLink() { return link; }
	void setLinke(hashNode * next) { link = next; }
};

class HashChainMap
{
	hashNode * table[TABLE_SIZE];
public:
	HashChainMap() {
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	}
	void display() {
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << i << " ";
			for (hashNode* p = 0; p != NULL; p = p->getLink())
			{
				cout << p->getKey();
			}
			cout << endl;
		}
	}
	void addRecord(hashNode * n)		// ü�ι��� �̿��Ͽ� ���̺� Ű�� ����
	{
		int hashValue = hashFunction(n->getKey());
		for (hashNode*p = table[hashValue]; p != NULL; p = p->getLink())
		{
			if (p->equal(n->getKey()))
			{
				cout << "�̹� Ž��Ű�� ����Ǿ� ����" << endl;
				delete n;
				return;
			}
		}
	}

	void searchRecord(const char *key)	// ü�ι��� �̿��Ͽ� ���̺� ����� Ű�� Ž��
	{
		int hashValue = hashFunction(key);
		for (hashNode * p = table[hashValue]; p != NULL; p = p->getLink())
		{
			if (p->equal(key))
			{
				cout << "Ž�� ����" << endl;
				p->display();
				return;
			}
		}
		cout << "Ž�� ���� " << key << endl;
	}
};


int main(void)
{
	
	return 0;
}
/*
�ؽ��Լ��� ����
1. �浹�� ����� �Ѵ�.
2. �ؽ� �Լ� ���� �ؽ� ���̺��� �ּ� ���� ������ ���� �����Ǿ�� �Ѵ�
3. ����� ����� �Ѵ�.
���� �Լ� - K % M�� ��� (�� �� M�� �Ҽ�)

�����Լ�- Ž��Ű�� ���� �κ����� ������ ��� ���� ���� �ؽ� �ּҷ� ����Ѵ�.
Ž�� Ű�� �ؽ� ���̺��� �ε��� ���� �� ���� ��Ʈ�� �ʿ��� ���
Ž��Ű�� �� ���� �κ����� ������ �̸� ���ϰų� ��Ʈ���� XOR ���� �ο� ������ �Ѵ�.
�̵� ���� - Ž��Ű�� ���� �κδɷ� ���� ������ ���Ѵ�.
��� ���� - �̿��� �κ��� �Ųٷ� ���� �ؽ� �ּҸ� ��� ��.

�߰� ���� �Լ� - Ž��Ű�� ������ ����, �߰��� �� ��Ʈ�� ���ؼ� �ؽ� �ּҸ� �����Ѵ�.

��Ʈ ���� ��� - �ؽ� ���̺��� ũ�Ⱑ M = 2^k�� �� Ž��Ű�� �������� �����Ͽ� ������ ��ġ�� k���� ��Ʈ�� �ؽ� �ּҷ� ����ϴ� ���̴�.

���� �м� ��� - Ű�� ������ ��ġ�� �ִ� ���� �߿��� ���ߵ��� �ʴ� ������ �ؽ� ���̺��� ũ�⿡ ������ ��ŭ �����Ͽ� �ؽ� �ּҷ� ����ϴ� ����̴�.

Ž��Ű�� ���ڿ��� ��� - ���� �� ���ڿ� ������ �������� �ٲٰ� �ȴ�.

�ؽ��� ���� �÷ο� ó�� ���
���� ����� : �浹�� �Ͼ�� �ؽ� ���̺��� �ٸ� ��ġ�� ã�� �׸��� �����Ѵ�.
�ؽ� �Լ��� ���� ���Ͽ� �� ������ ������ �� ���� ���Ͽ��� �� ������ �ִ����� ã�� ����̴�.
���� ����� �������� ȸ���Ѵ�.

���� ����� - ���� ������� ����������, �浹 �߻� �� ������ ������ ��ġ�� ���� �Ŀ� ���Ͽ� �����Ѵ�.
����	:	���̺��� ũ��� �Ҽ����� �Ѵ�.

inc = inc + 1;
i = ( i + inc * inc) % TABLE_SIZE;

���� �ؽ̹�(���ؽ�)	-	�����÷ο찡 �߻��Կ� ���� �׸��� ������ ���� ��ġ�� ������ ��,
						���� �ؽ� �Լ��� �ٸ� ������ �ؽ� �Լ��� �̿��ϴ� ���

ü�̴� : �ϳ��� ���ʿ� ���� ���� ���ڵ带 ������ �� �ֵ��� �ϴ� ���

���� �е�(���� ����) : a = (����� �׸��� ����) / (�ؽ� ���̺��� ������ ����) = n/M
*/
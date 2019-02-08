#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#define MAX_LIST 20

using std::cout;
using std::endl;
using std::queue;

// 무작위 배열 생성
void randomNumber(int list[])	// 랜덤 배열 생성
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_LIST; i++)
		list[i] = rand();
}
// 순차 탐색
int sequentialSearch(int list[], int key, int low, int high)	// 정렬되지 않은 배열에서 순차 탐색
{
	for (int i = 0; i <= high; i++)
		if (list[i] == key)
			return i;
	return -1;
}
int sortedSequentialSearch(int list[], int key, int low, int high)	// 정렬된 배열에서의 순차 탐색
{
	if (key <list[low] || key > list[high])return -1;
	for (int i = low; i <= high; i++)
	{
		if (list[i] > key)return -1;
		if (list[i] == key) return i;
	}
}
// 정렬된 배열에서 이진 탐색
int binarySearch(int list[], int key, int low, int high)	// 재귀호출을 이용한 이진탐색
{
	if (low <= high)	// 하나 이상의 항목이 있어야 탐색
	{
		int middle = (low + high) / 2;
		if (list[middle] == key) return middle;	// 탐색 성공
		else if (key < list[middle]) return binarySearch(list, key, low, middle - 1);	// 왼쪽 부분리스트 탐색
		else return binarySearch(list, key, middle + 1, high);	// 오른쪽 부분리스트 탐색
	}
	return -1;	// 탐색 실패
}
int binarySearchIter(int list[], int key, int low, int high) // 반복문을 이용한 이진탐색
{
	if (low <= high)	// 항목들이 남아 있으면 (종료 조건)
	{
		int middle = (low + high) / 2;
		if (key == list[middle]) return middle;				// 탐색 성공
		else if (key > list[middle]) low = middle + 1;		// key가 middle의 값보다 크면 middle + 1 ~ high 사이 검색
		else high = middle - 1;								// key가 middle의 값보다 작으면 low ~ middle - 1 사이 검색
	}
	return -1;												// 탐색 실패
}
// 색인 순차 탐색
struct Index {
	int key;	// 키 값
	int index;	// 키 값의 인덱스
};
int indexedSearch(int list[], int nList, Index *tbl, int nTbl, int key)	// 색인 순차 탐색 nList 항목의 수, nTbl 인덱스 테이블의 크기 복잡도 = O(nTbl + nList / nTbl)
{
	if (key <list[0] || key > list[nList - 1]) return -1;	// 키 값이 리스트 범위 밖
	for (int i = 0; i < nTbl - 1; i++)	// 인덱스 테이블 조사
	{
		if (tbl[i].key <= key && tbl[i + 1].key > key)
			return sequentialSearch(list, key, tbl[i].index, tbl[i + 1].index);
	}
	return sequentialSearch(list, key, tbl[nTbl - 1].index, nList);
}
// 보간 탐색
int interpolationSearch(int list[], int nList, int key)		// 보간 탐색 복잡도 = O(log2n)
{
	int low = 0;
	int high = nList - 1;
	while ((list[low] < key) && (key <= list[high]))
	{
		int j = (int)((double)(key - list[low]) / (list[high] - list[low])*(high - low)) + low;

		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else return j;							// 탐색 성공
	}
	return -1;									// 탐색 실패
}

// AVL 트리
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
	bool isLeaf() { return left == NULL && right == NULL; } // 현재 노드가 단말 노드인지 검사
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

		cout << "56번 째 줄 예상치 못한 에러" << getData() << endl;
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

		cout << "70번 째 줄 예상치 못한 에러" << getData() << endl;
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
		cout << "83번 째 줄 예상치 못한 에러" << getData() << endl;
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
	bool isFull() // 완전 이진트리인지 검사
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
	int level(int node) // 임이의 node의 레벨을 구하는 함수 node가 없으면 0반환
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
	bool isBalanced() // 모든 노드에서 왼쪽 서브트리와 오른쪽 서브트리의 높이의 차이가 2보다 작은지 판단 하라 (차이가 2이하이면 true)
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
	int pathLength() // 경로의 길이 반환 루트에서 모든 노드까지의 경로의 길이의 합
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
	bool reverse() // 좌우로 대칭 시키는 연산을 구현
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
	bool isDisjointFrom(Tree * that) // 현재 트리와 that 트리가 같은 노드를 가지고 있는 지 판단하라 (가지고 있으면 false)
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
	bool isValid() // 모든 서브트리가 서로 분리되어 있는 지 판단하라 ( 분리되어 있으면 true)
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
		Node * parent = NULL;	// 없앨 노드의 부모
		Node * node = root;		// 없앨 노드
		while (node != NULL && node->getData() != key)
		{
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}
		//없앨 노드가 트리에 없음.
		if (node == NULL)
		{
			cout << "Error : key is not in the tree" << endl;
			return;
		}
		// 없앨 노드가 트리에 있음.
		else
			remove(parent, node);
	}
	void remove(Node * parent, Node * node)
	{
		// case 1 : 삭제 하려는 노드가 단말 노드인 경우 

		if (node->isLeaf())
		{
			if (parent == NULL) // 공백상태가 됨.
				root = NULL;
			else
			{
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}

		// case 2 : 삭제하려는 노드가 왼쪽이나 오른쪽 자식만 갖는 경우
		else if (node->getLeft() == NULL || node->getRight() == NULL)
		{
			//삭제할 노드의 유일한 자식 노드 => child
			Node * child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();
			//삭제할 노드가 root이면 child가 새로운 root가 된다.
			if (child == root)
				root = child;
			//아니면 부모노드의 자식으로 자식 노드 child를 직접 연결
			if (parent->getLeft() == node)
				parent->setLeft(child);
			else
				parent->setRight(child);
		}

		// case 3 : 삭제하려는 노드가 2개의 자식이 모두 있는 경우
		else
		{
			//삭제하려는 노드의 오른쪽 서브트리에서 가장 큰 노드를 탐색
			Node * succ = node->getRight();	//succ => 후계 노드 : 오른 쪽 서브트리에서 가장 key가 작은 노드
			Node * succp = node;	//succp => 후계노드의 부모 노드

			while (succ->getLeft() != NULL)	//후계 노드 탐색
			{
				succp = succ;	//후계 노드의 부모 노드
				succ = succ->getLeft();	//후계 노드
			}
			// 후계노드의 부모와 후계 노드의 오른쪽 자식을 직접 연결
			if (succ->getLeft() != NULL)
			{
				succp->setLeft(succ->getRight());
			}
			//후계 노드가 삭제할 노드의 바로 오른쪽 자식인 경우
			else
			{
				succp->setRight(succ->getRight());
			}
			// 후계 노드 정보를 삭제할 노드에 복사
			node->setData(succ->getData());
			// 삭제할 노드를 후계 노드로 변경 : 실제로는 후계노드가 제거됨
			// 삭제할 노드에 후계노드를 저장하고 후계노드를 제거한다.
			node = succ;
		}
		delete node;
	}

	// 순환이 아닌 검색 방법
	Node * searchWithWhile(int key)
	{
		Node * temp = getRoot();
		while (temp != NULL)
		{
			if (temp->getData() == key)
			{
				cout << "탐색 성공" << endl;
				return temp;
			}
			else if (temp->getData() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		cout << "탐색 실패" << endl;
	}
};

class AVLTree : public Tree
{
public:
	int getHeightDiff(Node * node)		// 노드의 균형인수를 반환
	{
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return hLeft - hRight;
	}

	Node *rotateLL(Node *parent)		// LL 회전 함수
	{
		Node * child = parent->getLeft();
		parent->setLeft(child->getRight());
		child->setRight(parent);
		return child;
	}
	Node *rotateRR(Node *parent)		// RR 회전 함수
	{
		Node * child = parent->getRight();
		parent->setRight(child->getLeft());
		child->setLeft(parent);
		return child;
	}
	Node *rotateRL(Node * parent)		// RL 회전 함수
	{
		Node * child = parent->getRight();
		parent->setRight(rotateLL(child));
		return rotateRR(parent);
	}
	Node *rotateLR(Node * parent)		// LR 회전 함수
	{
		Node * child = parent->getLeft();
		parent->setLeft(rotateRR(child));
		return rotateLL(parent);
	}

	Node *reBalance(Node * parent)		// 트리를 균형트리로 만든다
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
	void insert(int data)			// AVL 트리의 삽입 연산
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
			cout << "중복된 키에러" << endl;
			return NULL;
		}
	}
};

// 해싱을 이용한 탐색
#define KEY_SIZE 64		// 탐색키의 최대 길이
#define VALUE_SIZE 64	// 탐색키와 관련된 정보
#define TABLE_SIZE 13	// 해싱 테이블 크기

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
	char key[KEY_SIZE];		// 키 필드 (사전의 경우 "단어")
	char value[VALUE_SIZE];	// 키와 관련된 자료("의미")
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
	void reset()		// 모든 버켓을 지운다.
	{
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i].reset();
	}
	void display()		// 맵의 전체 내용을 출력
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << i << " ";
			table[i].display();
		}
	}
	void addLinearProb(const char * key, const char * value)	// 선형 조사법을 이용한 삽입
	{
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false)
		{
			if (table[i].equal(key))
			{
				cout << key << " 탐색 키가 중복되었습니다." << endl;
				return;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue)
			{
				cout << key << " 테이블이 가득 찼습니다." << endl;
				return;
			}
		}
		table[i].set(key, value);
	}
	Record* searchLinearProb(const char *key)				// 선형 조사법을 이용한 키를 탐색
	{
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false)
		{
			if (table[i].equal(key))
			{
				cout << key << " 탐색 성공 " << i << endl;
				table[i].display();
				return table + i;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue)break;
		}
		cout << key << " 탐색 실패: 찾는 값이 테이블에 없음" << endl;
		return NULL;
	}
};

class hashNode : public Record	//연결된리스트를 위한 노드 클래스
{
	hashNode * link;			// 다음 노드를 가리키는 포인터 변수
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
	void addRecord(hashNode * n)		// 체인법을 이용하여 테이블에 키를 삽입
	{
		int hashValue = hashFunction(n->getKey());
		for (hashNode*p = table[hashValue]; p != NULL; p = p->getLink())
		{
			if (p->equal(n->getKey()))
			{
				cout << "이미 탐색키가 저장되어 있음" << endl;
				delete n;
				return;
			}
		}
	}

	void searchRecord(const char *key)	// 체인법을 이용하여 테이블에 저장된 키를 탐색
	{
		int hashValue = hashFunction(key);
		for (hashNode * p = table[hashValue]; p != NULL; p = p->getLink())
		{
			if (p->equal(key))
			{
				cout << "탐색 성공" << endl;
				p->display();
				return;
			}
		}
		cout << "탐색 실패 " << key << endl;
	}
};


int main(void)
{
	
	return 0;
}
/*
해시함수의 조건
1. 충돌이 적어야 한다.
2. 해시 함수 값이 해시 테이블의 주소 영역 내에서 고르게 분포되어야 한다
3. 계산이 빨라야 한다.
제산 함수 - K % M을 사용 (이 때 M은 소수)

폴딩함수- 탐색키를 여러 부분으로 나누어 모두 더한 값을 해시 주소로 사용한다.
탐색 키가 해시 테이블의 인덱스 보다 더 많은 비트가 필요할 경우
탐색키를 몇 개의 부분으로 나누어 이를 더하거나 비트별로 XOR 같은 부울 연산을 한다.
이동 폴딩 - 탐색키를 여러 부부능로 나눈 값들을 더한다.
경계 폴딩 - 이웃한 부분을 거꾸로 더해 해시 주소를 얻는 다.

중간 제곱 함수 - 탐색키를 제곱한 다음, 중간의 몇 비트를 취해서 해시 주소를 생성한다.

비트 추출 방법 - 해시 테이블의 크기가 M = 2^k일 때 탐색키를 이진수로 간주하여 임이의 위치의 k개의 비트를 해시 주소로 사용하는 것이다.

숫자 분석 방법 - 키의 각각의 위치에 있는 숫자 중에서 편중되지 않는 수들을 해시 테이블의 크기에 적합한 만큼 조합하여 해시 주소로 사용하는 방법이다.

탐색키가 문자열인 경우 - 보통 각 문자에 정수를 대응시켜 바꾸게 된다.

해싱의 오버 플로우 처리 방법
선형 조사법 : 충돌이 일어나면 해시 테이블의 다른 위치에 찾아 항목을 저장한다.
해싱 함수로 구한 버켓에 빈 슬롯이 없으면 그 다음 버켓에서 빈 슬롯이 있는지를 찾는 방법이다.
버켓 조사는 원형으로 회전한다.

이차 조사법 - 선형 조사법과 유사하지만, 충돌 발생 시 다음에 조사할 위치를 다음 식에 의하여 결정한다.
주의	:	테이블의 크기는 소수여야 한다.

inc = inc + 1;
i = ( i + inc * inc) % TABLE_SIZE;

이중 해싱법(재해싱)	-	오버플로우가 발생함에 따라 항목을 저장할 다음 위치를 결정할 때,
						원래 해시 함수와 다른 별개의 해시 함수를 이용하는 방법

체이닝 : 하나의 버켁에 여러 개의 레코드를 저장할 수 있도록 하는 방법

적재 밀도(적재 비율) : a = (저장된 항목의 개수) / (해싱 테이블의 버켓의 개수) = n/M
*/
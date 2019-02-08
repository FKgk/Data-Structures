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
		if(getRight() != NULL && getLeft() != NULL)
			return 1 + getLeft() -> getCount() > getRight()->getCount() ? getLeft()->getCount() : getRight()->getCount();

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
		if(getLeft() != NULL && getRight() != NULL)
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
		cout << "n이 " << n << "일때 경과 시간 : " << (clock() - start)  << "\t";
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
		cout << "n이 " << n << "일때 경과 시간 : " << (clock() - start)  << "\t";
		cout << ans_n << endl;
	}
	return 0;
}
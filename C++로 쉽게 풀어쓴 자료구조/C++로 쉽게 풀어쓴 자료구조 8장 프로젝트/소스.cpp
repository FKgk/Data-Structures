#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
class Node
{
protected:
	char data;
	Node * left;
	Node * right;
public:
	Node(char val = NULL, Node * l = NULL, Node * r = NULL):data(val), left(l), right(r){}
	void setData(char val) { data = val; }
	void setLeft(Node * l) { left = l; }
	void setRight(Node * r) { right = r; }
	char getData() { return data; }
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
	
};

class Tree
{
	Node * root;
public:
	Tree(): root(NULL){}
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
		return 1 + getCount(node->getLeft()) + getCount(node->getRight());
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
		return 1 + getCount(node->getLeft()) > getCount(node->getRight()) ? getCount(node->getLeft()) : getCount(node->getRight());
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
		if (node->getLeft() == NULL && node->getRight() == NULL)
			return 1;
		return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
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
	int level(char node) // 임이의 node의 레벨을 구하는 함수 node가 없으면 0반환
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
		return true && findNode(node->getLeft()) && findNode(node->getRight()) ;
	}
	bool isValid() // 모든 서브트리가 서로 분리되어 있는 지 판단하라 ( 분리되어 있으면 true)
	{

	}
	// isFull, isBalanced, isValid

};
int main(void)
{
	Tree tree;
	Node * d = new Node('D', NULL, NULL);
	Node * e = new Node('E', NULL, NULL);
	Node * b = new Node('B', d, e);
	Node * f = new Node('F', NULL, NULL);
	Node * c = new Node('C', f, NULL);
	Node * a = new Node('A', b, c);
	
	Tree tree2;
	Node * D = new Node('d', NULL, NULL);
	Node * E = new Node('e', NULL, NULL);
	Node * B = new Node('b', D, E);
	Node * F = new Node('f', NULL, NULL);
	Node * C = new Node('c', F, NULL);
	Node * A = new Node('a', B, C);

	tree.setRoot(a);
	tree2.setRoot(A);
	cout << tree.isBalanced() << endl;
	cout << tree.isDisjointFrom(&tree2) << endl;;
	//tree.postorder();
	//cout << tree.getCount() << endl;
	//cout << tree.getHeight() << endl;
	//cout << tree.getLeafCount() << endl;
	//tree.levelorder();
	//cout << tree.level('F') << endl;
	//cout << tree.pathLength() << endl;
	//cout << tree.reverse() << endl;
	//tree.postorder();
	return 0;
}
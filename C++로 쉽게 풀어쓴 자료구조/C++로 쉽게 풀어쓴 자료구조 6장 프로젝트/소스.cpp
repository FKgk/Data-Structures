#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Node
{
	int data;
	Node * link;
public:
	Node (int val):data(val), link(NULL)	{}
	Node * getLink(){ return link; }
	void setLink(Node *next){ link = next;}
	void display(){	cout << data << " ";}
	bool hasData(int val){ return data == val; }
	void insertNext(Node * node){
		if (node == NULL)
			return;
		//if (link == NULL)
		//	node->link = node ;
		//else
		node->link = link;
		link = node;
	}
	Node * removeNext() {
		Node * removed = link;
		if (removed != NULL)
			if (link->getLink() == link)
				link = NULL;
			else
				link = removed->link;

			return removed;
	}
	int getData() { return data; }
};

class LinkedList 
{
	Node org;
public:
	LinkedList() :org(23) {}
	~LinkedList() { clear(); }
	void clear() {
		while (isEmpty() == false)
			delete remove(0);
	}
	Node * getHead() { return org.getLink(); }
	void insert(int pos, Node * node) {////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "node data : " << node->getData() << " processing" << endl;
		Node *prev = getEntry(pos - 1);
		cout << "pre node data : " << prev->getData() << endl;
		if (prev != NULL)
		{
			if (pos == 0)
			{
				if (size() > 0)
				{
					Node * lastNode = getEntry(size() - 1);
					lastNode->setLink(node);
					cout << "lastNode : " << lastNode->getData() << endl;
				}
				else
				{
					cout << "insertNext" << endl;
					prev->insertNext(node);
					cout << "setLink(node)" << endl;
					node->setLink(node);
				}
			}
			else
				prev->insertNext(node);
		}
		cout << "insert processing end" << endl;
		return;
	}
	Node * remove(int pos) 
	{
		Node *prev = getEntry(pos - 1);
		return prev->removeNext();
	}
	Node * getEntry(int pos) {
		Node *node = &org;
		/*for (int i = -1; i < pos; i++, node = node->getLink())
			if (node == NULL)
				break;
				*/
		while (node != NULL && pos-- > -1)
			node = node->getLink();
		cout << "return getEntry node Data " << node->getData() << endl;
		return node;
	}
	bool isEmpty() { return org.getLink() == NULL; }
	Node * find(int item) {
		Node * finder = org.getLink();
		if (finder != NULL)
			while (finder->hasData(item) == false)
				finder = finder->getLink();
		return finder;
	}
	void replace(int pos, Node * node) 
	{
		Node * prev = getEntry(pos - 1);
		delete prev->removeNext();
		prev->insertNext(node);
	}
	int size() {
		Node *node = &org;
		
		int count = 1;
		cout << "size begin" << endl;
		if (getHead() == NULL)
			return 0;

		for (node = getHead()->getLink(); node != getHead(); node = node->getLink())
		{
			count++;
			cout << node->getData() <<" : " << node->getLink() << endl;
		}
		cout << node->getData() << " : " << node->getLink() << endl;
		cout << "size end count : " << count<< endl;
		return count;
	}
	void display() {
		Node *node = getHead();
		if (node == NULL)
			return;
		node->display();
		for ( node = node ->getLink(); node != getHead() && node != NULL; node = node->getLink())
			node->display();
		cout <<"display 실행 완료" <<endl;
	}
	void reverse()
	{
		Node *node = NULL;
		Node *temp = getEntry(size() - 1);
		for (int i = size() - 2; i >= 0; i--)
		{
			node = getEntry(i);
			node->getLink()->setLink(node);
		}
		node->setLink(NULL);
		org.setLink(temp);
	}
	void merge(LinkedList *that)
	{
		Node * node = getEntry(size() - 1);
		node->setLink(that->getHead());
		that->org.setLink(NULL);
	}
};

int main(void)
{

	LinkedList list, list2;
	cout << "list.insert ( 0, new Node(10)); " << endl;
	list.insert(0, new Node(10));
	cout << "main end" << endl;

	list.insert(0, new Node(20));
	list.insert(0, new Node(30));
	list.insert(0, new Node(40));

	cout << "list display() ; -----------" << endl;
	list.display();
	
	return 0;
}
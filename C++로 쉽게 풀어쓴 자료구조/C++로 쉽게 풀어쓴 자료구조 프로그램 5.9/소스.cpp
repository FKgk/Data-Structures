#include <iostream>
using namespace std;
struct Student
{
	int id;
	char name[20];
	Student(int i, const char * n) :id(i)
	{
		strcpy(name, n);
	}
};
class Node : public Student
{
	Node * link;
public:
	Node(int id = 0, const char *name = "") :Student(id, name)
	{link = NULL;}
	Node * getLink() { return link; }
	void setLink(Node *p) { link = p; }
	void display()
	{
		cout << id << name << endl;
	}
};

class LinkedStack
{
	Node * top;
public:
	LinkedStack() { top = NULL; }
	bool isEmpty() { return top == NULL; }
	void push(Node *p) {
		if (isEmpty()) top = p;
		else
		{
			p->setLink(top);
			top = p;
		}
	}
	Node *pop()
	{
		if (isEmpty()) return NULL;
		Node *p = top;
		top = top->getLink();
		return p;
	}
	void display()
	{
		cout << "[Linked Stack]" << endl;
		for (Node *p = top; p != NULL; p = p->getLink())
		{
			p->display(); 
		}
		cout << endl;
	}
};
int main(void)
{
	Node a(1, "1");
	Node b(2, "2");
	Node c(3, "3");
	LinkedStack linkedlist;
	linkedlist.push(&a);
	linkedlist.push(&b);
	linkedlist.push(&c);

	linkedlist.display();
	return 0;
}
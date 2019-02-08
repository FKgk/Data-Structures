#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

inline void error(const char * str)
{
	cout << str << endl;
	exit(1);
}

class queue 
{
	int que[100];
	int front, rear;
public:
	queue() :front(0), rear(0)	{}
	bool isFull(void)	{	return front == (rear + 1) % 100;	}
	bool isEmpty(void) {	return front == rear;	 }
	void addRear(int val)
	{
		if (isFull() == true)
			error("ť�� �� á���ϴ�.");
		rear++;
		que[rear] = val;
	}
	void addFront(int val)
	{
		if (isFull() == true)
			error("ť�� �� á���ϴ�.");
		que[front] = val;
		front = (front + 99) % 100;
	}
	int getFront()
	{
		if (isEmpty() == true)
			error("ť�� ������ϴ�.");
		return que[ (front + 1) % 100];
	}
	int getRear()
	{
		if (isEmpty() == true)
			error("ť�� ������ϴ�.");
		return que[rear];
	}
	int deleteRear()
	{
		if (isEmpty() == true)
			error("ť�� ������ϴ�.");
		int temp = que[rear];
		rear = (rear + 99) % 100;
		return temp;
	}
	int deleteFront()
	{
		if (isEmpty() == true)
			error("ť�� ������ϴ�.");
		
		front = (front + 1) % 100;
		return que[front];
	}
};

class System
{
	queue male, female;
	queue couple;

	int couMale;
	int couFemale;
	
	int nSimulation; // ��ü �ùķ��̼� Ƚ��
	double probArrival; // �����ð��� �Է��ϴ� ��� �л� ��
	int tMaxService; // �� ���� ���� �ִ� ���� �ð�
	int count = 0; // ��ü ���� �ּ� Ƚ��

	int totalWaitTime; // ������ ��ٸ� ��ü�ð�
	int nCustomers; // ��ü �� ��
	int nServedCustomers; // ���� ���� �� ��

	double random() { return rand() / (double)RAND_MAX; }
	bool randGender() { return random() > 0.5; }
	bool isNewCustomer() { return random() > probArrival; }
	int randServiceTime() { return (int)(tMaxService * random()) + 1; }

	void insertCustomer(int arrivalTime)
	{
		cout << "�� " << ++nCustomers ;
		if (randGender() == true)
		{
			male.addRear(nCustomers);
			cout << " �湮 ���� : " << "male" << endl;
		}
		else
		{
			female.addRear(nCustomers);
			cout << " �湮 ���� : " << "female" << endl;
		}
	}
public:
	System():nCustomers(0), totalWaitTime(0),nServedCustomers(0){}
	bool checkcouple(void)
	{
		if (male.isEmpty() == false && female.isEmpty() == false)
			return true;
		return false;
	}
	void readSimulationParameters(void)
	{
		cout << "�ùķ��̼� �� �ִ� �ο� : ";	cin >> nSimulation;
		cout << "�����ð��� �����ϴ� �� ��(0~1) : ";	cin >> probArrival;
		cout << "====================================" << endl;
	}
	void run(void)
	{
		int clock = 0;
		while (clock < nSimulation)
		{
			clock++;
			cout << "����ð� = " << clock << endl;

			if (isNewCustomer())
				insertCustomer(clock);
			if (male.isEmpty() && female.isEmpty())
				continue;
			printStatus(clock);
		}
	}
	
	void printStatus(int clock)
	{
		if (checkcouple() == true)
		{
			couMale = male.deleteFront();
			couFemale = female.deleteFront();
			couple.addRear(couMale);
			couple.addRear(couFemale);
			count++;
			totalWaitTime += clock * 2 - (couMale + couFemale);
		}
	}
	void printStat(void) 
	{
		cout << "===================================" << endl;
		cout << " Ŀ�� ���� ��ȣ "<< endl;
		while (couple.isEmpty() == false)
		{
			cout << couple.deleteFront() << " , " << couple.deleteFront() << endl;
		}
		cout << " ��ü ���� �ּ� Ƚ�� = " << count << endl;
		cout << " ���� �� ��� ��� �ð� = " << (double)totalWaitTime / count << endl;
	}
};

int main(void)
{
	System system;
	srand((unsigned int)time(NULL));
	system.readSimulationParameters();
	system.run();
	system.printStat();
}
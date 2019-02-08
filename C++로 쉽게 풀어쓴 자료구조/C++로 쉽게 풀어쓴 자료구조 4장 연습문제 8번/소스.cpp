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
			error("큐가 꽉 찼습니다.");
		rear++;
		que[rear] = val;
	}
	void addFront(int val)
	{
		if (isFull() == true)
			error("큐가 꽉 찼습니다.");
		que[front] = val;
		front = (front + 99) % 100;
	}
	int getFront()
	{
		if (isEmpty() == true)
			error("큐가 비었습니다.");
		return que[ (front + 1) % 100];
	}
	int getRear()
	{
		if (isEmpty() == true)
			error("큐가 비었습니다.");
		return que[rear];
	}
	int deleteRear()
	{
		if (isEmpty() == true)
			error("큐가 비었습니다.");
		int temp = que[rear];
		rear = (rear + 99) % 100;
		return temp;
	}
	int deleteFront()
	{
		if (isEmpty() == true)
			error("큐가 비었습니다.");
		
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
	
	int nSimulation; // 전체 시뮬레이션 횟수
	double probArrival; // 단위시간에 입력하는 평균 학생 수
	int tMaxService; // 한 고객에 대한 최대 서비스 시간
	int count = 0; // 전체 미팅 주선 횟수

	int totalWaitTime; // 고객들이 기다린 전체시간
	int nCustomers; // 전체 고객 수
	int nServedCustomers; // 서비스 받은 고객 수

	double random() { return rand() / (double)RAND_MAX; }
	bool randGender() { return random() > 0.5; }
	bool isNewCustomer() { return random() > probArrival; }
	int randServiceTime() { return (int)(tMaxService * random()) + 1; }

	void insertCustomer(int arrivalTime)
	{
		cout << "고객 " << ++nCustomers ;
		if (randGender() == true)
		{
			male.addRear(nCustomers);
			cout << " 방문 성별 : " << "male" << endl;
		}
		else
		{
			female.addRear(nCustomers);
			cout << " 방문 성별 : " << "female" << endl;
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
		cout << "시뮬레이션 할 최대 인원 : ";	cin >> nSimulation;
		cout << "단위시간에 도착하는 고객 수(0~1) : ";	cin >> probArrival;
		cout << "====================================" << endl;
	}
	void run(void)
	{
		int clock = 0;
		while (clock < nSimulation)
		{
			clock++;
			cout << "현재시각 = " << clock << endl;

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
		cout << " 커플 쌍의 번호 "<< endl;
		while (couple.isEmpty() == false)
		{
			cout << couple.deleteFront() << " , " << couple.deleteFront() << endl;
		}
		cout << " 전체 미팅 주선 횟수 = " << count << endl;
		cout << " 서비스 고객 평균 대기 시간 = " << (double)totalWaitTime / count << endl;
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
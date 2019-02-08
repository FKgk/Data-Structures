#include <iostream>
using namespace std;

int Horner(int *a, int n, int current, int size)
{
	if (current == size - 2)
		return a[current + 1] * n + a[current];
	else
		return Horner(a, n, current + 1, size) * n + a[current];
}

void turnBool(bool &a)
{
	if (a)
		a = false;
	else
		a = true;
}
void TrueOrFalse(bool n[], int current, int size)
{
	if (current == size - 1)
	{
		for (int i = 0; i < size; i++)
		{
			if (n[i])
				cout << "true ";
			else
				cout << "false ";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < size * 2; i++)
		{
			TrueOrFalse(n, current + 1, size);
			turnBool(n[i % 2]);
		}
	}
}

bool binarySearch(int n[], int find, int left, int right)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;
		if (n[middle] > find)
			return binarySearch(n, find, left, middle - 1);
		else if (n[middle] < find)
			return binarySearch(n, find, middle + 1, right);
		else
			return true;
	}
	return false;
}

template <typename t>
void swap(t &a, t &b)
{
	t temp = a;
	a = b;
	b = temp;
}
void PrintArray(int x, int y, int z)
{
	if (x <= y && y <= z)
		cout << x << " " << y << " " << z << endl;
	else if (x > y)
		PrintArray(y, x, z);
	else if (y > z)
		PrintArray(x, z, y);

}

int searchArray(int a[], int x, int current, int size)
{
	if (current == size)
		return -1;
	if (a[current] == x)
		return a[current];
	else
		return searchArray(a, x, current + 1, size);
}

int factorial(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}

int fibo(int n)
{
	if (n <= 2)
		return 1;
	else
		return fibo(n - 1) + fibo(n - 2);
}

int combinationByRecursive(int n, int m)
{
	if (m == 0 || n == m)
		return 1;
	else
		return combinationByRecursive(n - 1, m) + combinationByRecursive(n - 1, m - 1);
}

int Ackermann(int m, int n)
{
	int ans = 0;
	int **dp = new int*[m];
	for (int i = 0; i < m; i++)
	{
		dp[i] = new int[n];
		for (int j = 0; j < n; j++)
			dp[i][j] = 0;
	}
	int i = 0, j = 0;
	while (m == i && n == j)
	{
		if (i == 0)
			dp[i][j] = j + 1;
		else if (j == 0)
			dp[i][j];

	}

	return n + 1;
}
int AckermannByRecursive(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return AckermannByRecursive(m - 1, 1);
	else
		return AckermannByRecursive(m - 1, AckermannByRecursive(m, n - 1));
}

void fun(int &a)
{
	a = (a + 1) % 5;
}
int * pogeonhole_principle(int n[], int size, void f(int&) = fun )
{
	int ans[2];
	for (int i = 0; i < size; i++)
		f(n[i]);
	for (int i = 0; i < size - 1; i++)
		for (int j = i + 1; j < size; j++)
			if (n[i] == n[j])
			{
				ans[0] = i;
				ans[1] = j;
				return ans;
			}
	ans[0] = ans[1] = -1;
	return ans;
}

void powerset(char s[], int current, int point, int size)
{
	cout << "(";
	for (int i = 0; i < current; i++)
	{

	}
}

int main(void)
{
	// 1
	int a[] = { 0,1,2,3,4,5,6,7,8 };
	cout << "Horner : " << Horner(a, 1, 0, sizeof(a) / sizeof(a[0])) << endl;
	// 2
	bool n[] = { true, true };
	TrueOrFalse(n, 0, 2);
	// 4
	PrintArray(1, 0, 4);
	// 5
	cout << "searchArray : " << searchArray(a, 5, 0, sizeof(a) / sizeof(a[0])) << endl;
	// 6
	cout << "factorial(5) : " << factorial(5) << endl;
	// 7
	cout << "fibo(10) : " << fibo(5) << endl;
	// 8
	cout << "combinationByRecursive(5, 2) : " << combinationByRecursive(5, 2) << endl;
	// 10
	cout << "AckermannByRecursive(3, 2) : " << AckermannByRecursive(3, 2) << endl;
	cout << "Ackermann(3, 2) : " << Ackermann(3, 2) << endl;
	// 12
	int *num = pogeonhole_principle(a, sizeof(a) / sizeof(a[0]));
	cout << "pogeonhole_principle : " << num[0] << " " << num[1] << endl;
	// 14
	


	cout << endl;
	return 0;
}
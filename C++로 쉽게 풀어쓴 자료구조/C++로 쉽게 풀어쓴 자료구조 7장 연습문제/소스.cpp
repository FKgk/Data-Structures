#include <iostream>
#pragma warning(disable:4996)
using namespace std;

long fibo(long n)
{
	if (n == 1)
		return 1;
	if (n == 0)
		return 0;
	return fibo(n - 1) + fibo(n - 2);
}
char * reverse(const char * str1)
{
	char * str = new char[strlen(str1) + 1];

	strcpy(str, str1);
	char * a = new char[strlen(str) + 1];
	if (strlen(str) == 1)
	{
		strcpy(a, str);
		str[0] = NULL;
		return a;
	}
	else
	{
		strcpy( a, reverse(&str[1]));
		str[1] = NULL;
		return strcat(a, &str[0]);
	}
}
int main(void)
{
	char a[] = "0123456789";
	
	cout << reverse("0123456789") << endl;

	return 0;
}
#include <iostream>


int a(int m, int n)
{
	if (m == 0)
		return 1;
	if (m == 1 && n == 0)
		return 2;
	if (m > 1)
		return m + 2;
	if (m > 0 && n > 0)
		return a(a((m - 1), n), n - 1);
	std::cout << "error: " << m << " " << n << std::endl;
	exit(1);
}
int main(void)
{
	std::cout << a(4, 10) << std::endl;




	return 0;
}
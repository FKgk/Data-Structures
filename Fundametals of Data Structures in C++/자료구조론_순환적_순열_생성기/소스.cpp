#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}
void Permutations(char *a, const int k, const int m)
{
	if (k == m)
	{
		for (int i = 0; i <= m; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	else
	{
		for (int i = k; i <= m; i++)
		{
			swap(a[k], a[i]);
			Permutations(a, k + 1, m);
			swap(a[k], a[i]);
		}
	}
}


int main(void)
{
	char a[] = { 'a', 'b', 'c', 'd', 'e' };
	Permutations(a, 0, 4);

	return 0;
}
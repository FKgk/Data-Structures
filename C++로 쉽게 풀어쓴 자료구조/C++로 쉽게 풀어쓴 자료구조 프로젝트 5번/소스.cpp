#include <iostream>
using namespace std;
int Square(int n, int i)
{
	if (i == 0)
		return 1;
	if (i % 2)
		return n * Square(n * n, (i - 1) / 2);
	return Square(n * n, i / 2);
}
int draw_tree(int row, int left, int right)
{
	if (row == 4)
		return 0;
	int squ = Square(2, row);
	for (int j = 0; j < squ; j++)
	{
		for (int i = 0; i < right / (squ * 2) - 1 ; i++)
		{
			cout << "-";
		}
		cout << "X";
		for (int i = 0; i <(double) right / (squ * 2) - 1; i++)
		{
			cout << "-";
		}
		if (row != 0 && j != squ - 1)
			cout << "-";
	}
	cout << endl;
	draw_tree(row + 1, 1, right);
	return 1;
}
int main(void)
{
	draw_tree(0, 1, 40);

}
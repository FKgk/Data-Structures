#include <cstdio>
#include <cstdlib>

class matrix
{
private:
	int matrixXY[50][50];
	int matrixCount[2];
	int transposeXY[50][50];
	int transposeCount[2];
public:
	matrix(const int *count)
	{
		int i, j;
		for(i = 0; i < 2; i++)
			matrixCount[i] = count[i];
		for (i = 0; i < matrixCount[0]; i++)
			for (j = 0; j < matrixCount[1]; j++)
				matrixXY[i][j] = rand();
	}
	void matrixDisplay(void)
	{
		int i, j;
		for (i = 0; i < matrixCount[0]; i++)
		{
			for (j = 0; j < matrixCount[1]; j++)
				printf("%d ", matrixXY[i][j]);
			printf("\n");
		}
	}
	void transpose(void)
	{
		int i, j;
		for (i = 0; i < 2; i++)
			transposeCount[1-i] = matrixCount[i];
		for (i = 0; i < transposeCount[0]; i++)
			for (j = 0; j < transposeCount[1]; j++)
				transposeXY[i][j] = matrixXY[j][i] ;
	}
	void transposeDisplay(void)
	{
		int i, j;
		for (i = 0; i < transposeCount[0]; i++)
		{
			for (j = 0; j < transposeCount[1]; j++)
				printf("%d ", transposeXY[i][j]);
			printf("\n");
		}
	}
};
int main(void)
{
	srand(NULL);
	int count[2] = { 2, 3 };
	matrix m(count);
	m.matrixDisplay();
	printf("--------------------------------\n");
	m.transpose();

	m.transposeDisplay();
	return 0;
}
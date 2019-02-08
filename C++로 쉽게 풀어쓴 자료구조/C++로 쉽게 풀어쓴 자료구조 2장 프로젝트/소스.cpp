#include <iostream>
using namespace std;
typedef struct _list {
	int expon; // 항의 지수
	double coef; // 항의 계수
}Term;

class SparsePoly
{
private :
	int nTerms; //계수가 0이 아닌 항의 개수
	Term term[80]; // 계수가 0이 아닌 항의 배열
public:
	SparsePoly() {}
	void read()
	{
		double temp;
		int maxNumber, count = 0;
		cout << "다항식의 최고차수를 입력해주세요";
		cin >> maxNumber;
		cout << "각 항의 차수를 입력해주세요(내림차순)" << endl;
		for (int i = 0; i <= maxNumber; i++)
		{
			cin >> temp;
			if (temp != 0)
			{
				term[count].coef = temp;
				term[count].expon = maxNumber - i;
				count++;
			}
		}
		nTerms = count;
	}
	void add(SparsePoly a, SparsePoly b)
	{
		int bignTerms = a.nTerms - 1;
		int acount = 0, bcount = 0, i;
		for (i = 0; i < bignTerms; i++)
		{
			if (bcount > b.nTerms)
				b.term[bcount].expon = 0;
			if (acount > a.nTerms)
				a.term[bcount].expon = 0;
			if (a.term[acount].expon != b.term[bcount].expon)
			{
				if (a.term[acount].expon > b.term[bcount].expon)
				{
					term[i].expon = a.term[acount].expon;
					term[i].coef = a.term[acount].coef;
					acount++;
				}
				else
				{
					term[i].expon = b.term[bcount].expon;
					term[i].coef = b.term[bcount].coef;
					bcount++;
				}
				bignTerms++;
			}
			else
			{
				term[i].expon = a.term[acount].expon;
				term[i].coef = a.term[acount].coef + b.term[bcount].coef;
				acount++;
				bcount++;
			}
		}
		nTerms = bignTerms-1;
	}
	void display(const char * str = "SPoly = ")
	{
		for (int i = 0; i < nTerms; i++)
		{
			if(term[i].expon == 0)
				cout << term[i].coef << endl;
			else if (i == nTerms - 1)
				cout << term[i].coef << "x^" << term[i].expon << endl;
			else
				cout << term[i].coef << "x^" << term[i].expon << " + ";
		}
	}
};

class Polynomial
{
private:
	int degree; // 최고차수
	double *coef; // 각 항의 계수
public:
	Polynomial(void) 
	{ 
		degree = 0;
		coef = NULL;
	}
	void read()
	{
		std::cout << "다항식의 최고차수를 입력해주세요";
		cin >> degree;
		coef = new double[degree + 1];
		std::cout << "각 항의 차수를 입력해주세요(내림차순)" << endl;
		for (int i = 0; i <= degree; i++)
			cin >> coef[i];
	}
	void display(const char *str = "Poly = ")
	{
		cout << str;
		for (int i = 0; i < degree; i++)
		{
			if (coef[i] == 0)
				continue;
			if(coef[i] != 1)
				cout << coef[i];
			cout << " x^" << degree - i << " + ";
		}
		if(coef[degree] != 0)
			cout << coef[degree] << endl;
	}
	void add(Polynomial a, Polynomial b)
	{
		if (a.degree > b.degree)
		{

			*this = a;
			for (int i = 0; i <= b.degree; i++)
			{
				coef[i + degree - b.degree] += b.coef[i];
			}
		}
		else
		{
			*this = b;
			for (int i = 0; i <= a.degree; i++)
			{
				coef[i + degree - a.degree] += a.coef[i];
			}
		}
	}
	void sub(Polynomial a, Polynomial b)
	{
		if (a.degree > b.degree)
		{
			*this = a;
			for (int i = 0; i <= b.degree; i++)
			{
				coef[i + degree - b.degree] -= b.coef[i];
			}
		}
		else
		{
			*this = b;
			for (int i = 0; i <= a.degree; i++)
				coef[i + degree - a.degree] -= a.coef[i];
		}
	}
	void mul(Polynomial a, Polynomial b)
	{
		int i, j;

		degree = a.degree + b.degree;
		coef = new double[degree + 1];
		for (i = 0; i <= degree; i++)
			coef[i] = 0;
		for (i = 0; i <= a.degree; i++)
		{
			for (j = 0; j <= b.degree; j++)
			{
				coef[degree - (i + j)] += a.coef[a.degree - i] * b.coef[b.degree - j];
			}
		}
	}
	void trim()
	{
		for (int i = degree; i >= 0; i--)
		{
			if (coef[i] == 0)
			{
				degree--;
			}
			else
				break;
		}
	}
	/*
	5 3 6 0 0 0 10 4 7 0 5 0 1
	*/
	bool isZero() { return degree == 0; }
	void negate() {
		for (int i = 0; i < degree; i++)
			coef[i] = -coef[i];
	}
};

int main(void)
{
	SparsePoly a, b, c;
	a.read();
	b.read();
	cout << "A----------------------" << endl;
	a.display();
	cout << "B----------------------" << endl;
	b.display();
	cout << "add----------------------" << endl;
	c.add(a, b);
	cout << "display----------------------" << endl;
	c.display();
	/*
	Polynomial poly, a, b;
	a.read();
	b.read();
	cout << "A----------------------" << endl;
	a.display();
	cout << "B----------------------" << endl;
	b.display();
	cout << "add--------------------" << endl;
	poly.add(a, b);
	poly.display();
	cout << "sub--------------------" << endl;
	poly.sub(a, b);
	poly.display();
	cout << "trim--------------------" << endl;
	poly.trim();
	poly.display();

	cout << "A----------------------" << endl;
	a.display();
	cout << "B----------------------" << endl;
	b.display();
	cout << "mul--------------------" << endl;
	poly.mul(a, b); 
	poly.display();
	*/
	return 0;
}
/*
5 3 6 0 0 0 10 4 7 0 5 0 0
*/
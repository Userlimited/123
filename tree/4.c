#include <iostream>
using namespace std;

int a = 0;

int &fun()
{
	return a;
}

int main()
{
	int *p;
	int *&rp = p;
	int x = 100;
	int &rx = x;
	p = &x;
	cout << "*p=" << *p << endl;
	cout << "x=" << x << endl;
	cout << "rx=" << rx << endl;
	cout << "*rp" << *rp << endl;
	x++;
	(*p)++;
	rx++;
	(*rp)++;
	cout << "*p=" << *p << endl;
	cout << "x=" << x << endl;
	cout << "rx=" << rx << endl;
	cout << "*rp" << *rp << endl;
}

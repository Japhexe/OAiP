#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


int main()
{
	double x, y, f, a, b;
	int k;
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
	setlocale(LC_ALL, "rus");
	cout << "Выберите формат f: " << endl;
	cout << "1 - sh(x)" << endl;
	cout << "2 - x ^ 2" << endl;
	cout << "3 – exp(x) " << endl;
	bool o = 1;
	while (o) {
		o = 0;
		cin >> k;
		switch (k) {
		case 1: f = sinh(x); break;
		case 2: f = pow(x, 2); break;
		case 3: f = exp(x); break;
		default: cout << "Введите 1, 2 или 3: " << endl; o = 1;
		}
	}
	if (y != 0) {
		a = x / y;
		if (a < 0) {
			b = pow((pow(f, 2) + y), 3);
		}
		else if (a > 0) {
			b = log(abs(f / y)) + (x / y);
		}
	}
	else {
		b = pow(abs(sin(y)), 1. / 3);
	}
	cout << "Результат вычисления: " << b;
	return 0;
}

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

double inputNumber(int& i);

int main()
{
	bool correctInput = 0;
	double x, y, f, a, b;
	int k, j = 0;
	while (!(correctInput)) {
		cout << "x = ";
		x = inputNumber(j);
		if (j != 0) {
			continue;
		}
		cout << "y = ";
		y = inputNumber(j);
		if (j != 0) {
			continue;
		}
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
		if (!isfinite(f)) { // проверка на бесконечность f
			setlocale(LC_ALL, "rus");
			cout << "Результат вычисления функции f вышел за допустимый лимит! Повторите попытку: " << endl;
			setlocale(LC_ALL, "eng");
			continue;
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
		if (!isfinite(b)) { // проверка на бесконечность результата
			setlocale(LC_ALL, "rus");
			cout << "Результат вычисления вышел за допустимый лимит! Повторите попытку: " << endl;
			setlocale(LC_ALL, "eng");
			continue;
		}
		correctInput = 1;
	}
	cout << "Результат вычисления: " << b;
	return 0;
}

double inputNumber(int& i) {
	string sNumber;
	cin >> sNumber;
	string z = sNumber; // запаминающая переменная
	double numberE = 0;
	bool e = 0, notCorrectE = 1, bigger = 0;
	int o = 0;
	i = 0;
	if (sNumber.find('e') != 4294967295 || sNumber.find('E') != 4294967295) { //  проверка на наличие экспонентной формы
		int fE;
		if (sNumber.find('e') != 4294967295) {
			fE = sNumber.find('e');
		}
		else {
			fE = sNumber.find('E');
		}
		string a1, a2; // часть число до 'e' и после
		for (int i = 0; i != fE; i++) {
			a1.push_back(sNumber[i]);
		}
		for (int i = fE + 1; i != sNumber.length(); i++) {
			a2.push_back(sNumber[i]);
		}
		if (a2[0] == '+' || a2[0] == '-') {
			a2.erase(0, 1);
		}
		else {
			notCorrectE = 0;
		}
		bool errorInput = 0;
		if (!(a2[0] >= '0' && a2[0] <= '9')) {
			errorInput = 1;
		}
		if (!(errorInput)) {
			ostringstream c;
			if (!(a2.length() > 308)) { // проверка длинны экспоненты
				numberE = stod(a2);
				int s1, s2;
				s1 = a2.length();
				c << setprecision(a2.length()) << numberE;
				s2 = c.str().size();
				if (!(s1 == s2)) {
					notCorrectE = 0;
				}
				if (numberE > 308) {
					bigger = 1;
				}
			}
			else {
				notCorrectE = 0;
			}
		}
		else {
			notCorrectE = 0;
		}
		sNumber = a1;
		e = 1;
	}
	ostringstream c;
	double number;
	int p = 0;
	if (sNumber[0] == '+') {
		sNumber.erase(0, 1);
	}
	if (sNumber.length() > 1) {
		if (!(((sNumber[0] >= '0' && sNumber[0] <= '9') || sNumber[0] == '-') && (sNumber[1] >= '0' && sNumber[1] <= '9') || (sNumber[0] != '-' && sNumber[1] == '.'))) {
			p = 1;
		}
	}
	else if (!(sNumber[0] >= '0' && sNumber[0] <= '9')) {
		p = 1;
	}
	if (p == 0 && notCorrectE) { // проверка верности ввода
		if (!((sNumber.length() > 308) || (bigger) || (sNumber.length() + numberE > 308))) {
			number = stod(sNumber);
			int s1, s2;
			s1 = sNumber.length();
			c << setprecision(sNumber.length()) << number;
			s2 = c.str().size();
			if (s1 == s2) { // сравнение длины sNumber и  number
				if (e) {
					number = stod(z);
				}
				cin.ignore(32767, '\n');
				return number;
			}
			else {
				setlocale(LC_ALL, "rus");
				cout << "Некорректный ввод! Повторите попытку: " << endl;
				setlocale(LC_ALL, "eng");
				i = 1;
			}
		}
		else {
			setlocale(LC_ALL, "rus");
			cout << "Число вышло за допустимый лимит! Повторите попытку: " << endl;
			setlocale(LC_ALL, "eng");
			i = 1;
		}
	}
	else {
		setlocale(LC_ALL, "rus");
		cout << "Некорректный ввод! Повторите попытку: " << endl;
		setlocale(LC_ALL, "eng");
		i = 1;
	}
}

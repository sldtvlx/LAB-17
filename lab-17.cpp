 //	Данные: ФИО, №счета, сумма
 //	Ключ: ФИО
 //	Хэш-функция: H(k)=k mod M
 //	Метод рехеширования: метод открытой адресации

#include <iostream>
#include <list>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int getCorrectNumber()
{
	unsigned int num;
	while (!(cin >> num) || (cin.peek() != '\n') || num < 0)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите корректное число: ";
	}
	return num;
}

struct people
{
	string fio;
	string pass_num;
	string summ;
};

int Hash_rem(string s, int n)
{
	int l;
	l = s.size();
	return (l % n);
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int len = 0;
	int adress;
	people x;
	string user_search;
	int error = 0;

	while (len < 2 || len>100)
	{
		cout << "Введите размер таблицы: ";
		len = getCorrectNumber();
	}

	const int N = len;

	cin.get();
	people* data_base = new people[len];
	string* key = new string[len];

	for (int i = 0; i < len; i++) key[i] = "Пусто";

	ifstream F1("F1.txt");
	ifstream F2("F2.txt");
	ifstream F3("F3.txt");

	for (int i = 0; i < N; i++)
	{
		getline(F1, x.fio);
		getline(F2, x.pass_num);
		getline(F3, x.summ);
		adress = Hash_rem(x.fio, N);

		while (adress >= len || key[len - 1] != "Пусто")
		{
			people* data_base_new = new people[len * 2];
			string* key_new = new string[len * 2];

			for (int i = 0; i < len; i++)
			{
				data_base_new[i] = data_base[i];
				key_new[i] = key[i];
			}

			for (int i = len; i < len * 2; i++) key_new[i] = "Пусто";

			delete[] data_base;
			delete[] key;

			data_base = data_base_new;
			key = key_new;
			len *= 2;
		}

		if (key[adress] != "Пусто")
		{
			error++;

			while (key[adress] != "Пусто") adress++;

			cout << endl;
		}

		data_base[adress] = x;
		key[adress] = x.fio;
	}

	cout << "Таблица создана. Коллизий: " << error << endl;

	for (int i = 0; i < len; i++)
	{
		cout << i << ": " << key[i] << endl;
	}

	cout << "\nВведите запрос\n";
	getline(cin, user_search);
	
	adress = Hash_rem(user_search, N);

	while (adress < len)
	{
		if (key[adress] == user_search)
		{
			cout << "\nОбъект найден:\n";
			cout << "ФИО - " << data_base[adress].fio << endl;
			cout << "Номер счета - " << data_base[adress].pass_num << endl;
			cout << "Сумма - " << data_base[adress].summ << endl;
			break;
		}

		if (key[adress] == "Пусто")
		{
			cout << "Неизвестный объект [Пустая ячейка]\n";
			break;
		}

		adress++;
	}

	if (adress == len) cout << "Неизвестный объект [Пустая ячейка]\n";
}
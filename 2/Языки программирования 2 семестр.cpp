#include <iostream>
#include <Windows.h>
#include <string.h>

using namespace std;

void nline()
{
	cout.fill('-'); cout.width(99); cout << "|" << "|\n";
}

struct Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct Record 
{
	char name[9];
	char type;
	int s;
	int workers;
	struct Date date;
};

void DrawHead()
{
	cout << "\n";
	cout.fill('-'); cout.width(101); cout << right << "\n";
	cout << "|" << left; cout.width(98); cout.fill(' '); cout << "Сельскохозяйственные предприятия" << "|\n";
	nline();
	cout << "|"; cout.width(12); cout.fill(' '); cout << "Название";
	cout << "|"; cout.width(21); cout << "Вид собственности";
	cout << "|"; cout.width(22); cout << "Площадь земли (га)";
	cout << "|"; cout.width(19); cout << "Кол. работников";
	cout << "|"; cout.width(20); cout << "Дата документа" << "|\n";
	nline();
}

void szeros(int n)
{
	if (n < 10)
	{
		 cout.width(3); cout << "000"; cout.width(19); cout << left << n;
	}
	if (n > 9 and n < 100)
	{
		 cout.width(2); cout << "00"; cout.width(20); cout << left << n;
	}
	if (n > 100)
	{
		cout.width(1); cout << "0"; cout.width(21); cout << left << n;
	}
}

void datezeros(unsigned short day, unsigned short month, unsigned short year)
{
	cout << "|" << left; cout.width(5); cout << ' ';
	if (day < 10)
	{
		cout.width(1);
		cout << '0';
		cout.width(1);
		cout << day;
	}
	else
	{
		cout.width(2);
		cout << day;
	}
	cout << '.';
	if (month < 10)
	{
		cout.width(1);
		cout << '0';
		cout.width(1);
		cout << month;
	}
	else
	{
		cout.width(2);
		cout << month;
	}
	cout << '.';
	cout << year;
	cout.width(5); cout << ' '; cout << "|\n";
}

void DrawContents(struct Record* records, unsigned short change)
{
	for (int i = 0; i < change; i++)
	{
		cout << "|"; cout.width(12); cout.fill(' '); cout << records[i].name;
		cout << "|"; cout.width(21); cout << records[i].type;
		cout << "|"; szeros(records[i].s);
		cout << "|" ;  cout.width(19); cout << right << records[i].workers;
		datezeros(records[i].date.day, records[i].date.month, records[i].date.year);
		nline();
	} 
}

void DrawBottom()
{
	cout << "|" << left; cout.width(98); cout.fill(' '); cout << "Вид собственности: Д - государтсвенная, Ч - частная, К - кооперативная" << "|\n";
	cout.fill('-'); cout.width(101); cout << right << "\n";
}

void table(struct Record* records, bool addmins)
{
	DrawHead();
	if (addmins)
	{
		DrawContents(records, 3);
		cout << "|"; cout.width(34); cout.fill(' '); cout << "Минимальные числовые значения";
		cout << right << "|", szeros(records[3].s);
		cout << "|"; cout.width(19); cout << right << records[3].workers;
		cout << "|" << left; cout.width(20); cout << ' '; cout << "|\n";
		nline();
	}
	else DrawContents(records, 3);
	DrawBottom();
}

int main()
{
	struct Record records[10];
	records[0] = { "Заря", 'Д', 300, 120, { 7, 3, 2022 } };
	records[1] = { "Росинка", 'К', 174, 27, { 3, 7, 2022 } };
	records[2] = { "Петренко", 'Ч', 56, 6, { 8, 8, 2021 } };
	setlocale(LC_ALL, "RU");
	cout.fill(' '); cout.width(60); cout << right << "Практическая работа 2\n"; 
	cout.fill(' '); cout.width(73); cout << left << "Работу выполнил Малеженков Даниил"; cout << right << "Вариант стартовой таблицы 8\n";

	//cout.fill(' '); cout.width(101); cout << right << "Вариант задания 1\n";

	cout.fill(' '); cout.width(58); cout << right << "Изначальная таблица";
	table(records, false);

	/*records[3] = { "xd", ' ', min(records[0].s, min(records[1].s, records[2].s)), min(records[0].workers, min(records[1].workers, records[2].workers)), ' ' };
	cout << endl;  cout.fill(' '); cout.width(59); cout << right << "Измененная таблица";
	table(records, true);*/
	

	//   КОД  2  ПРАКТИКИ

	Record* A;
	A = (Record*)malloc(3 * sizeof(Record));
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(A[i].name, records[i].name);
		A[i].type = records[i].type;
	}

	A = (Record*)realloc(A, 10 * sizeof(Record));

	Record** B;
	B = (Record**) new Record * [10];
	for (int i = 0; i < 10; i++)
	{
		B[i] = (Record*) new Record;
		*(B[i]) = A[i];
	}

	for (int i = 0; i < 10; i++)
	{
		cout << "\nЗапись номер " << i+1;
		cout << "\n Адрес А[i]: " << &A[i] << " A[i]->name: " << A[i].name;
		cout << "\n Адрес А[i]: " << &A[i] << " A[i]->type: " << A[i].type;
		cout << endl;
		cout << "\n Адрес B[i]: " << &B[i] << " B[i]->name: " << B[i]->name;
		cout << "\n Адрес B[i]: " << &B[i] << " B[i]->type: " << B[i]->type;
		cout << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		delete B[i];
	}
	delete[]B;
	free(A);
}
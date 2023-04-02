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
	string name;
	char type;
	int s;
	int workers;
	struct Date date;
};

struct Node {
	Record data;
	struct Node* next;
};
struct Node* Head;
int Count = 0;

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

void table_list()
{
	DrawHead();
	struct Node* current = Head;
	while (current)
	{
		cout << "|"; cout.width(12); cout.fill(' '); cout << current->data.name;
		cout << "|"; cout.width(21); cout << current->data.type;
		cout << "|"; szeros(current->data.s);
		cout << "|";  cout.width(19); cout << right << current->data.workers;
		datezeros(current->data.date.day, current->data.date.month, current->data.date.year);
		nline();
		current = current->next;
	}
	DrawBottom();
}

void add(Record data)
{
	struct Node* New = new Node();
	New->data = data;
	if (Count == 0) {
		New->next = NULL;
	}
	else
	{
		New->next = Head;
	}
	Head = New;
	Count++;
}

int findIndex(string name)
{
	struct Node* current = Head;
	int i = 0;
	while (current)
	{
		if (current->data.name == name)
		{
			return i;
		}
		i++;
		current = current->next;
	}
	return -1;
}

void Delete(string name)
{
	int index = findIndex(name);
	struct Node* current = Head;
	struct Node* old;
	if (index == 0) {
		old = Head;
		Head = current->next;
		delete old;
		Count--;
	}
	else {
		int i = 0;
		while (current) {
			if (i == index - 1) {
				old = current->next->next;
				delete current->next;
				current->next = old;
				Count--;
				break;
			}
			i++;
			current = current->next;
		}
	}
}

int main()
{
	struct Record records[10];
	records[0] = { "Заря", 'Д', 300, 120, { 7, 3, 2022 } };
	records[1] = { "Росинка", 'К', 174, 27, { 3, 7, 2022 } };
	records[2] = { "Петренко", 'Ч', 56, 6, { 8, 8, 2021 } };
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout.fill(' '); cout.width(60); cout << right << "Практическая работа 3\n"; 
	cout.fill(' '); cout.width(73); cout << left << "Работу выполнил Малеженков Даниил"; cout << right << "Вариант стартовой таблицы 8\n";
	cout.fill(' '); cout.width(101); cout << right << "Вариант задания 1\n";
	cout.fill(' '); cout.width(58); cout << right << "Изначальная таблица";
	table(records, false);
	
	//   КОД  3  ПРАКТИКИ

	add(records[0]);
	add(records[1]);
	add(records[2]);
	cout << endl;
	cout.fill(' '); cout.width(58); cout << right << "Таблица по списку";
	table_list();
	cout << "\nВведите название удаляемого предприятия: ";
	string dead;
	cin >> dead;
	Delete(dead);
	cout << endl;
	cout.fill(' '); cout.width(58); cout << right << "Измененная таблица";
	table_list();
}
#include <iostream>
#include <string.h>

using namespace std;

void nline()
{
	using namespace std;
	cout.fill('-'); cout.width(98); cout << "|" << "|\n";
}

void DrawHead()
{
	cout << "\n";
	cout.fill('-'); cout.width(100); cout << right << "\n";
	cout << "|" << left; cout.width(97); cout.fill(' '); cout << "Сельскохозяйственные предприятия" << "|\n";
	nline();
	cout << "|"; cout.width(12); cout.fill(' '); cout << "Название";
	cout << "|"; cout.width(21); cout << "Вид собственности";
	cout << "|"; cout.width(22); cout << "Площадь земли (га)";
	cout << "|"; cout.width(19); cout << "Кол. работников";
	cout << "|"; cout.width(19); cout << "Дата документа" << "|\n";
	nline();
}

void zeros(int n)
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

void DrawContents(const char* names[], char types[], int s[], int workers[], const char* dates[])
{
	
	for (int i = 0; i < 3; i++)
	{
		cout << "|"; cout.width(12); cout.fill(' '); cout << names[i];
		cout << "|"; cout.width(21); cout << types[i];
		cout << "|"; zeros(s[i]);
		cout << "|" ;  cout.width(19); cout << right << workers[i];
		cout << "|" << left; cout.width(4); cout << ' ';
		cout << dates[i]; 
		cout.width(5); cout << ' '; cout << "|\n";
		nline();
	} 
}

void DrawBottom()
{
	
	cout << "|" << left; cout.width(97); cout.fill(' '); cout << "Вид собственности: Д - государтсвенная, Ч - частная, К - кооперативная" << "|\n";
	cout.fill('-'); cout.width(100); cout << right << "\n";
}

int main()
{
	
	setlocale(LC_ALL, "RU");
	cout.fill(' '); cout.width(90); cout << left << "Работу выполнил Малеженков Даниил"; cout << right << "Вариант 8\n";
	DrawHead();
	const char* names[] = { "Заря", "Росинка", "Петренко" };
	char types[] = { 'Д', 'К', 'Ч' };
	int s[] = { 300, 174, 56 };
	int workers[] = { 120, 27, 6 };
	const char* dates[] = { "07.03.2022", "03.07.2022", "08.08.2021" };
	DrawContents(names, types, s, workers, dates);
	DrawBottom();	
}

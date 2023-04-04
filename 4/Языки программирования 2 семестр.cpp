#include <iostream>
#include <Windows.h>
#include <string.h>
#include <iomanip>

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
	if (n > 100 and n < 1000)
	{
		cout.width(1); cout << "0"; cout.width(21); cout << left << n;
	}
	if (n > 999)
	{
		cout.width(22); cout << left << n;
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

void table(struct Record* records, unsigned short str, bool addmins)
{
	DrawHead();
	if (addmins)
	{
		DrawContents(records, str);
		cout << "|"; cout.width(34); cout.fill(' '); cout << "Минимальные числовые значения";
		cout << right << "|", szeros(records[3].s);
		cout << "|"; cout.width(19); cout << right << records[3].workers;
		cout << "|" << left; cout.width(20); cout << ' '; cout << "|\n";
		nline();
	}
	else DrawContents(records, str);
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
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	cout.fill(' '); cout.width(60); cout << right << "Практическая работа 4\n"; 
	cout.fill(' '); cout.width(73); cout << left << "Работу выполнил Малеженков Даниил"; cout << right << "Вариант стартовой таблицы 8\n";
	cout.fill(' '); cout.width(101); cout << right << "Вариант задания 1\n";
	cout.fill(' '); cout.width(58); cout << right << "Изначальная таблица";
	table(records, 3, false);
	
	//   КОД  4  ПРАКТИКИ

	FILE* f;
	fopen_s(&f, "Malezhenkov.txt", "w");
	for (int i = 0; i < 3; i++)
	{
		fprintf(f, "%s %c %d %d %hu %hu %hu\n", records[i].name, records[i].type, records[i].s, records[i].workers,
			records[i].date.day, records[i].date.month, records[i].date.year);
	}
	fclose(f);

	fopen_s(&f, "Malezhenkov.txt", "r");
	struct Record read[4];
	cout << "\nИнформация из текстового файла:";
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(f, "%s %c %d %d %hu %hu %hu\n", read[i].name, 9, &read[i].type, 1, &read[i].s, &read[i].workers,
			&read[i].date.day, &read[i].date.month, &read[i].date.year);
		cout << endl << read[i].name << ' ' << read[i].type << ' ' << read[i].s << ' ' << read[i].workers << ' ' <<
			read[i].date.day << '.' << read[i].date.month << '.' << read[i].date.year << endl;
	}
	fclose(f);
	cout << endl;

	fopen_s(&f, "Malezhenkov.bin", "wb");
	for (int i = 0; i < 3; i++)
	{
		fwrite(&records[i], sizeof(Record), 1, f);
	}
	fclose(f);

	fopen_s(&f, "Malezhenkov.bin", "rb");
	cout << "Информация из бинарного файла:\n";
	for (int i = 0; i < 3; i++)
	{
		fread(&read[i], sizeof(Record), 1, f);
		cout << read[i].name << ' ' << read[i].type << ' ' << read[i].s << ' ' << read[i].workers << ' ' <<
			read[i].date.day << '.' << read[i].date.month << '.' << read[i].date.year << endl;
	}
	fclose(f);

	char d = 'Д', k = 'К', ch = 'Ч';
	fopen_s(&f, "Malezhenkov.bin", "a+b");
	while (read[3].type != d and read[3].type != k and read[3].type != ch or read[3].s > 9999 or read[3].s < 1 or read[3].date.day == 5428
		or read[3].date.day < 1 or read[3].date.day > 31 or read[3].date.month < 1 or read[3].date.month > 12 or read[3].date.year > 9999 or read[3].date.year < 1000)
	{
		cout << "\nВведите данные новой записи: ";
		cin >> read[3].name >> read[3].type >> read[3].s >> read[3].workers
			>> read[3].date.day >> read[3].date.month >> read[3].date.year;
		if (read[3].type != d and read[3].type != k and read[3].type != ch) cout << "\nВведен несоответствующий стандарту тип недвижимости\n";
		if (read[3].s > 9999) cout << "\nПлощадь земли слишком большая\n";
		if (read[3].s < 1) cout << "\nПлощадь земли слишком маленькая\n";
		if (read[3].workers == 2147483647 or read[3].date.day == 5428) cout << "\nСлишком много работников\n";
		if (read[3].workers < 1) cout << "\nСлишком мало работников\n";
		if (read[3].date.day < 1 or read[3].date.day > 31) cout << "\nНеправильный формат дня\n";
		if (read[3].date.month < 1 or read[3].date.month > 12) cout << "\nНеправильный формат месяца\n";
		if (read[3].date.year > 9999) cout << "\nНеправильный формат года\n";
		if (read[3].date.year < 1000) cout << "\nЗарегестрировано более тысячи лет назад? Серьезно?\n";
		cin.clear();
	}
	cout << endl;
	fwrite(&read[3], sizeof(read[3]), 1, f);
	fclose(f);

	Record frecords[4];
	fopen_s(&f, "Malezhenkov.bin", "r+b");

	for (int i = 0; i < 4; i++)
	{
		fread(&frecords[i], sizeof(Record), 1, f);
	}
	fclose(f);
	swap(frecords[1], frecords[3]);
	fopen_s(&f, "Malezhenkov.bin", "w+b");
	cout.fill(' '); cout.width(80); cout << right << "Таблица с добавленной строкой (изменения сохранены в файле)";
	for (int i = 0; i < 4; i++)  fwrite(&frecords[i], sizeof(Record), 1, f);
	table(frecords, 4, false);
	fclose(f);
}
// DriverWin.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <vector>
#include "conio.h"

using namespace std;

struct superBlock {
	unsigned int sizeOfFileSys;
	unsigned int sizeOfFatTable;
	unsigned int sizeOfMainPart;
};

void displayFatTable(vector<int*> fatTable) {
	printf("Number of block     Value\n");
	for (int i = 0; i < fatTable.size(); i++)
		printf("%d                   %d\n", i, fatTable[i]);
}

int main()
{
	FILE *file;
	struct superBlock sB;
	vector<int*> fatTable;
	int sizeOfRowFAT = 0;
	
	//super block
	fopen_s(&file, "v12.dat", "r");
	if (file == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit(1);
	}
	fread(&sB, sizeof(struct superBlock), 1, file);
	printf("sizeOfFileSys = %d sizeOfFatTable = %d sizeOfMainPart = %d\n", sB.sizeOfFileSys, sB.sizeOfFatTable, sB.sizeOfMainPart);
	sizeOfRowFAT = sB.sizeOfFatTable / sizeof(int *);

	//FAT
	int *row = new int;
	fread(&row, sizeof(int *), 1, file);
	for (int i = 0; i < sizeOfRowFAT; i++){
		if (i % 2 == 1) {
			fread(&row, sizeof(int *), 1, file);
			continue;
		}
		fread(&row, sizeof(int *), 1, file);
		fatTable.push_back(row);
		//printf("FAT = %d\n", row);
	}

	//MENU
	while (true)
	{
		system("cls");
		int choice = 0;
		cout << "Press 1-6 to select\n";
		cout << "1. Display FAT table.\n";
		cout << "2. Search file.\n";
		cout << "3. Display file system tree.\n";
		cout << "4. Save file to device.\n";
		cout << "5. Display file.\n";
		cout << "6. Quit.\n";
		scanf_s("%d", &choice);
		if (choice == 1) {
			displayFatTable(fatTable);
			printf("Press ENTER to continue");
			while (!_kbhit()){}
		}
		else if (choice == 2) {

		}
		else if (choice == 3) {

		}
		else if (choice == 4) {

		}
		else if (choice == 5) {

		}
		else if (choice == 6)
			break;
	}




	fclose(file);
	//delete row;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

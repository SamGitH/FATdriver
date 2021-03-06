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

struct fileStruct
{
	char fileName[12];
	int numberOfFirstBlock;
	int attribute;
};

void displayFatTable(vector<int> fatTable) {
	printf("Number of block\tValue\n");
	for (int i = 0; i < fatTable.size(); i ++)
		printf("%d\t%d\n", i, fatTable[i]);
}

void displayMainPart(vector<fileStruct> data) {
	for (int i = 0; i < data.size(); i++){
		char type;
		if (data[i].numberOfFirstBlock == 0)//неправильная обработка
			continue;
		if (data[i].attribute == 1)
			type = 'd';
		else
			type = 'f';
		printf("%c\t%d\t%s\n", type, data[i].numberOfFirstBlock, data[i].fileName);
	}
}

vector <int> getBlockChain(int numberOfBlock, vector<int> fatTable) {
	vector <int> chain;
	while (true) {
		chain.push_back(numberOfBlock);
		if (fatTable[numberOfBlock] == -1)
			break;
		numberOfBlock = fatTable[numberOfBlock];
	}
	return chain;
}

void displayFileSystemTree(vector<fileStruct> data, vector<int> fatTable, FILE *file, int shift, superBlock sB, string oldTab) {
	char* tab = _strdup(oldTab.c_str());
	for (int i = 0; i < data.size(); i++) {
		if (data[i].attribute == 1) {
			printf("%c%s%s\n", 'd', tab, data[i].fileName);
			vector <int> chain = getBlockChain(data[i].numberOfFirstBlock, fatTable);
			for (int j = 0; j < chain.size(); j++) {
				oldTab.push_back('\t');
				tab = _strdup(oldTab.c_str());
				fseek(file, shift + sB.sizeOfFileSys * chain[i], SEEK_SET);
				struct fileStruct fS;
				vector<fileStruct> newData;
				for (int k = 0; k < sB.sizeOfFileSys / sizeof(fileStruct); k++) {
					fread(&fS, sizeof(struct fileStruct), 1, file);
					if (fS.attribute == 1) {					
						newData.push_back(fS);
					}
					else if (fS.numberOfFirstBlock != 0) {//неправильная обработка
						printf("%c%s%s\n", 'f', tab, fS.fileName);
					}
				}
				displayFileSystemTree(newData, fatTable, file, shift, sB, oldTab);
			}
			oldTab.pop_back();
			tab = _strdup(oldTab.c_str());
		}
		else if(data[i].numberOfFirstBlock != 0){//неправильная обработка
			printf("%c%s%s\n", 'f', tab, data[i].fileName);
		}
	}
}

void searchFile()

void pressToContinue() {
	printf("Press ENTER to continue");
	while (!_kbhit()) {}
}

int main()
{
	FILE *file;
	struct superBlock sB;
	struct fileStruct fS;
	vector<int> fatTable;
	vector<fileStruct> data;
	int sizeOfRowFAT = 0;
	string tab;
	tab.push_back('\t');
	

	fopen_s(&file, "v12.dat", "r+b");
	if (file == NULL) {
		fprintf(stderr, "\nError opening file\n");
		exit(1);
	}

	//super block
	fread(&sB, sizeof(struct superBlock), 1, file);
	sizeOfRowFAT = sB.sizeOfFatTable / sizeof(int);
	int shift = sizeof(superBlock) + sB.sizeOfFatTable + sB.sizeOfMainPart * sizeof(fileStruct);

	//FAT
	int *row = new int;
	for (int i = 0; i < sizeOfRowFAT; i++) {
		fread(row, sizeof(int), 1, file);
		if (i % 2 != 0)
			fatTable.insert(fatTable.end(), *row);
	}

	//MainPart
	for (int i = 0; i < sB.sizeOfMainPart; i++){
		fread(&fS, sizeof(struct fileStruct), 1, file);
		data.push_back(fS);
	}

	//MENU
	while (true)
	{
		system("cls");
		printf("sizeOfFileSys = %d sizeOfFatTable = %d sizeOfMainPart = %d\n", sB.sizeOfFileSys, sB.sizeOfFatTable, sB.sizeOfMainPart);
		int choice = 0;
		cout << "Press 1-6 to select\n";
		cout << "1. Display FAT table.\n";
		cout << "2. Search file.\n";
		cout << "3. Display file system tree.\n";
		cout << "4. Save file to device.\n";
		cout << "5. Display file.\n";
		cout << "6. Display root directory.\n";
		cout << "7. Quit.\n";
		scanf_s("%d", &choice);
		if (choice == 1) {
			displayFatTable(fatTable);
			pressToContinue();
		}
		else if (choice == 2) {

		}
		else if (choice == 3) {
			displayFileSystemTree(data, fatTable, file, shift, sB, tab);
			pressToContinue();
		}
		else if (choice == 4) {

		}
		else if (choice == 5) {

		}
		else if (choice == 6) {
			displayMainPart(data);
			pressToContinue();
		}
		else if (choice == 7)
			break;
	}

	fclose(file);
	//delete row;
	return 0;
}

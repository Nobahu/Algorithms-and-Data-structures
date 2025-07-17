#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>

#include "SortingAlgorithms.h"
#include "Competitor.h"

int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	//Задание 1
	int n;
	cout << "Введите размерность массива n: ";
	cin >> n;
	
	vector<int*> array(n);
	
	for (int i = 0; i < n; i++)
	{
		array[i] = new int(1 + rand() % 10000);
		//cout << *array[i] << " ";
	}
	
	size_t Bubblesort_optimized = Sort<int>::Bubblesort_optimized(array);

	//cout << endl << endl;
	//cout << "Отсортированный массив: ";
	//for (double* val : array) 
	//{
	//	cout << *val << " ";
	//}
	//cout << endl;
	
	cout << "Массив отсортирован? " << (Sort<int>::isSorted(array) ? "Да" : "Нет") << endl;
	cout << "Количество операций сравнения: " << Bubblesort_optimized << endl;
	
	size_t Pyramidsort = Sort<int>::Pyramidsort(array,n);
	
	cout << "Массив отсортирован? " << (Sort<int>::isSorted(array) ? "Да" : "Нет") << endl;
	cout << "Количество операций сравнения: " << Pyramidsort << endl;
	
	size_t Mergesort = Sort<int>::Mergesort(array, n);
	
	cout << "Массив отсортирован? " << (Sort<int>::isSorted(array) ? "Да" : "Нет") << endl;
	cout << "Количество операций сравнения: " << Mergesort << endl;
	
	// Освобождаем выделенную память
	//for (int* val : array) 
	//{
	//	delete val;
	//}

	//Задание 2
	int numofcomp;
	cout << "Введите количество участников: ";
	cin >> numofcomp;

	vector<Competitor*> Competitors;
	for (int i = 0; i < numofcomp; i++) 
	{
		Competitors.push_back(new Competitor(i + 1, rand() % 6, 60 + rand() % 241, rand() % 26, rand() % 21));
	}
	

	vector<Competitor*> CompetitorPtrs = Competitors;
	Sort<Competitor>::Mergesort(CompetitorPtrs, CompetitorPtrs.size());

	ofstream file("results.txt");
	file << "ID | Баллы | Решенные задачи | Время | Попытки" << endl;
	file << "----------------------------------------" << endl;

	for (Competitor* p : CompetitorPtrs)
	{
		file << p->competitors_id << " | " << p->score << " | " << p->completed_task << " | " << p->time << " | " << p->attempts << endl;
	}
	file.close();

	//for (Competitor* p : Competitors)
	//{
	//	delete p;
	//}
	//return 0;
}

#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class Sort {

private:

	//Вспомогательные методы для работы сортировок
	static void heapify(vector<T*>& arr, size_t i, size_t n, size_t& count) {
		size_t smallest = i;
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;

		if (left < n && *arr[left] < *arr[smallest]) {
			smallest = left;
		}

		if (right < n && *arr[right] < *arr[smallest]) {
			smallest = right;
		}

		if (smallest != i) {
			swap(*arr[i], *arr[smallest]);
			count++;
			heapify(arr, smallest, n, count);
		}
	}

	static void Merge(vector<T*>& arr, size_t left, size_t mid, size_t right, size_t& count)
	{
		size_t n1 = mid - left + 1;
		size_t n2 = right - mid;

		vector<T*> arr1(n1), arr2(n2);

		for (size_t i = 0; i < n1; i++)
		{
			arr1[i] = arr[left + i];
		}
		for (size_t j = 0; j < n2; j++)
		{
			arr2[j] = arr[mid + 1 + j];
		}

		size_t i = 0;
		size_t j = 0;
		size_t k = left;

		while (i < n1 && j < n2)
		{
			count++; // Увеличиваем счетчик сравнений
			if (*arr1[i] >= *arr2[j])
			{
				arr[k] = arr1[i];
				i++;
			}
			else
			{
				arr[k] = arr2[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = arr1[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = arr2[j];
			j++;
			k++;
		}
	}

public:

	//Улучшенная пузырьковая сортировка
	static size_t Bubblesort_optimized(vector<T*>& arr)
	{
		size_t count = 0;
		size_t n = arr.size();
		bool sorted = false;
		for (size_t m = n; m > 1 and sorted == false; m--)
		{
			sorted = true;
			for (size_t i = 0; i < m - 1; i++)
			{
				count++;
				if (*arr[i] < *arr[i + 1])
				{
					swap(*arr[i], *arr[i + 1]);
					sorted = false;
				}
			}
		}
		return count;
	}

	//Пирамидальная сортировка
	static size_t Pyramidsort(vector<T*>& arr, size_t n) {

		size_t count = 0;

		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(arr, i, n, count);
		}

		for (int i = n - 1; i > 0; i--) {
			swap(*arr[0], *arr[i]);
			heapify(arr, 0, i, count);
		}

		return count;
	}

	//Рекурентая сортировка слиянием 
	static size_t Mergesort(vector<T*>& arr, size_t n)
	{
		size_t count = 0;
		for (size_t size = 1; size <= n - 1; size = 2 * size)
		{
			for (size_t leftstart = 0; leftstart < n - 1; leftstart += 2 * size)
			{
				size_t mid = min(leftstart + size - 1, n - 1);
				size_t rightend = min(leftstart + 2 * size - 1, n - 1);
				Merge(arr, leftstart, mid, rightend, count);
			}
		}
		return count;
	}

	static bool isSorted(const vector<T*>& arr)
	{
		for (size_t i = 1; i < arr.size(); i++)
		{
			if (*arr[i - 1] < *arr[i])
			{
				return false;
			}
		}
		return true;
	}
};
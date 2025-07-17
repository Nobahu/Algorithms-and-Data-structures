#include "Header.h"

int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    int n;

    cout << "Введите размерность массива: ";
    cin >> n;

    int* M = new int[n];

    for (int i = 0; i < n; i++) {
        int num;
        bool isUnique;

        do {
            isUnique = true;
            num = rand() % 100 + 1; 

            for (int j = 0; j < i; j++) {
                if (M[j] == num) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        M[i] = num;  // Записываем уникальное число в массив
    }

    cout << "Сгенерированный массив: ";
    for (int i = 0; i < n; i++)
    {
        cout << M[i] << " ";
    }
    cout << endl << endl;

    // Строим дерево из массива
    BinaryTree tree;
    tree.buildTreeFromArray(M, n);

    BinaryTree opt_tree;
    opt_tree.BuildOptimalTree(M, n);

    // Выводим дерево
    cout << "Дерево (прямой обход): ";
    tree.print();
    cout << "Максимальное по дереву значение уровня вершин: " << tree.MaxDepth() << endl;
    cout << "Среднее по дереву значение уровня вершин: " << tree.AverageDepth() << endl;

    cout << endl;

    cout << "Оптимальное дерево (прямой обход): ";
    opt_tree.print();
    cout << "Максимальное по дереву значение уровня вершин: " << opt_tree.MaxDepth() << endl;
    cout << "Среднее по дереву значение уровня вершин: " << opt_tree.AverageDepth() << endl;

    cout << endl;

    int SearchElem;
    cout << "Введите ключ, который хотите найти: ";
    cin >> SearchElem;
    tree.SearchMain(SearchElem);

    cout << endl;

    int GetLvlElem;
    cout << "Введите элемент, узел которого хотите найти: "; cin >> GetLvlElem; cout << endl;
    cout << tree.GetLvl(GetLvlElem) << endl;

    cout << endl;

    int RemoveElem;
    cout << "Введите элемент, который хотите удалить: "; cin >> RemoveElem; cout << endl;
    tree.Remove(RemoveElem);
    cout << "Дерево c удаленным элементом: ";
    tree.print();

    cout << endl;

    int MinVal, MaxVal;
    cout << "Введите диапазон значений: "; cin >> MinVal >> MaxVal; cout << endl;
    vector<int> DiapElem = tree.FDEHelper(MinVal, MaxVal);
    for (int val : DiapElem)
    {
        cout << val << " ";
    }

    // Освобождаем память
    delete[] M;

    return 0;
}



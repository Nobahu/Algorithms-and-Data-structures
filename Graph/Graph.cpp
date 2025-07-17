#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

struct Edge {

    int a, b;
    int weight;

    Edge(int a, int b, int weight) : a(a), b(b), weight(weight) {};

    bool operator<(Edge const& other)
    {
        return weight < other.weight;
    }

};

struct Point {

    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};


// Функция генерации N рандомных вершин
vector<Point> generateRandomPoints(int n)
{
    int min = 1, max = 100;
    
    vector<Point> points;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);

    for (int i = 0; i < n; i++) {
        points.emplace_back(dist(gen), dist(gen));
    }
    return points;
}

class Graph
{

public:

    Graph(vector<Point>& points, bool isWeighted) : points(points)
    {
        int n = points.size();
        adjMatrix.resize(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            adjMatrix[i][i] = 0;
            for (int j = i + 1; j < n; j++) {
                if (isWeighted) {
                    int distance = static_cast<int>(sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2))); // Вычисление расстояния между двумя точками в пространстве
                    adjMatrix[i][j] = distance;                                                                                   // с округлением через static_cast
                    adjMatrix[j][i] = distance;

                    edges.emplace_back(i, j, distance);
                }
                else {
                    adjMatrix[i][j] = 1;
                    adjMatrix[j][i] = 1;

                    edges.emplace_back(i, j, 1);
                }
            }
        }
    }

    // Сортировка по весу всех ребер при помощи улучшенного пузырька
    void edgeSorting(vector<Edge>& mst)
    {
        int count = 0;
        int n = mst.size();
        bool sorted = false;
        for (int m = n; m > 1 and sorted == false; m--)
        {
            sorted = true;
            for (int i = 0; i < m - 1; i++)
            {
                count++;
                if (mst[i].weight > mst[i + 1].weight)
                {
                    swap(mst[i], mst[i + 1]);
                    sorted = false;
                }
            }
        }
    }

    // Алгоритм Прима
    vector<Edge> Prim_algorithm() {
        int n = adjMatrix.size();
        vector<bool> inMST(n, false);
        vector<int> key(n, INT_MAX);  // минимальный вес до MST
        vector<int> parent(n, -1);    // откуда пришли в MST
        key[0] = 0;

        for (int i = 0; i < n - 1; i++) {
            // Найдём вершину с минимальным ключом
            int u = -1, minKey = INT_MAX;
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            if (u == -1) break; // граф несвязен

            inMST[u] = true;

            // Обновляем ключи соседей
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] > 0 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Построим вектор рёбер остова
        vector<Edge> mst;
        for (int i = 1; i < n; i++) {
            if (parent[i] != -1) {
                mst.emplace_back(parent[i], i, adjMatrix[parent[i]][i]);
            }
        }

        return mst;
    }

    // Создание матрицы смежности минимального остовного графа
    void MSTadjMatrix(vector<Edge>& mst, int n, int k)
    {
        mst_adjMatrix.resize(n, vector<int>(n, 0));

        for (int i = 0; i < k - 1 && !mst.empty(); i++) {
            mst.pop_back();
        }

        for (const Edge& edge : mst) {
            mst_adjMatrix[edge.a][edge.b] = edge.weight;
            mst_adjMatrix[edge.b][edge.a] = edge.weight;
        }
    }

    // Вспомогательная функция поиска вглубь
    void DFS(int i,vector<int>& component, vector<bool>&visited,int n)
    {
        visited[i] = true;
        component.push_back(i);

        for (int j = 0; j < n; j++) {
            if (mst_adjMatrix[i][j] != 0 and !visited[j]) {
                DFS(j, component, visited, n);
            }
        }
    }

    // Функция для нахождения и выделения компонент связности графа
    void findComponents(vector<vector<int>>& components)
    {
        int n = mst_adjMatrix.size();
        vector<bool> visited(n, false); //Вспомогательный вектор посещений

        for (int i = 0; i < n; i++) {
            vector<int> component;
            if (!visited[i]) {
                DFS(i, component, visited, n);
                components.push_back(component);
            }
        }
    }


    // Вывод всех сгенерированных ребер
    void displayEdges()
    {
        for (const auto& edge : edges) {
            cout << "Ребро: (" << edge.a << " - " << edge.b << ") Вес ребра: " << edge.weight << endl;
        }
    }

    // Вывод матрицы смежности исходного полного графа
    void displayMatrix() {
        int n = adjMatrix.size();
        cout << "Матрица смежности:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << adjMatrix[i][j];  // Форматированный вывод
            }
            cout << endl;
        }
    }

    // Вывод матрицы смежности ребер минимального остова
    void displayMSTMatrix()
    {
        cout << "Матрица смежности MST: " << endl;
        int n = mst_adjMatrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout<< setw(4) << mst_adjMatrix[i][j];
            }
            cout << endl;
        }
    }

    // Вывод найденных компонент связности
    void displayComponents()
    {
        findComponents(components);
        for (int i = 0; i < components.size(); i++) {
            cout << "Компонента " << i << ": ";
            for (int p : components[i]) {
                cout << p << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Вывод числа комонент, а также числа вершин и центроидов
    void displayComponentsStats(const string& filename)
    {
        ofstream file;
        file.open(filename);

        file << "Component,Vertex,X,Y,CentroidX,CentroidY\n";

        for (int i = 0; i < components.size(); i++) {
            int minX = INT_MAX, maxX = INT_MIN;
            int minY = INT_MAX, maxY = INT_MIN;
            double sumX = 0, sumY = 0;

            for (int index : components[i]) {
                int x = points[index].x;
                int y = points[index].y;

                minX = min(minX, x);
                minY = min(minY, y);
                maxX = max(maxX, x);
                maxY = max(maxY, y);

                sumX += x;
                sumY += y;
            }
            int numVertices = components[i].size();
            double centroidX = sumX / numVertices;
            double centroidY = sumY / numVertices;

            for (int index : components[i]) {
                file << i << "," << index << "," << points[index].x << "," << points[index].y << ","
                    << centroidX << "," << centroidY << "\n";
            }

            cout << "Компонента " << i << ":\n";
            cout << "Число вершин: " << numVertices << "\n";
            cout << "X: min = " << minX << ", max = " << maxX << "\n";
            cout << "Y: min = " << minY << ", max = " << maxY << "\n";
            cout << "Центроид: (" << centroidX << ", " << centroidY << ")\n";
            cout << "_________________________________________________\n";
        }

        file.close();
        cout << "Результаты сохранены в файл: " << filename << endl;

    }

    void saveEdgesCSV(const vector<Edge>& mst, const string& filename) {
        ofstream file(filename);
        file << "From,To,Weight\n";
        for (const auto& edge : mst) {
            file << edge.a << "," << edge.b << "," << edge.weight << "\n";
        }
        file.close();
    }
    
private:

    bool isWeighted;
    vector<vector<int>> components; // Вектор для хранения компонент связности
    vector<Point> points; // Вектор для хранения координат вершин
    vector<vector<int>> adjMatrix; // Матрица смежности полного графа
    vector<vector<int>> mst_adjMatrix; // Матрица смежности минимального оставного графа
    vector<Edge> edges; // Вектор для хранения ребер (его вершинах и весе)

};


int main()
{
    setlocale(LC_ALL, "RU");

    int num_points,num_clusters;
    bool isWeighted;

    cout << "Введите количество вершин графа: "; cin >> num_points;
    cout << "\nВаш граф взвешенный? (1/0):"; cin >> isWeighted;
    cout << "\nВведите количество кластеров: "; cin >> num_clusters;


    vector<Point> points = generateRandomPoints(num_points);

    cout << "Сгенерированные точки: " << endl;
    for (int i = 0; i < points.size(); i++) {
        cout << "Точка " << i << ": (" << points[i].x << ", " << points[i].y << ")\n";
    }

    cout << endl;

    Graph graph(points,isWeighted);
    graph.displayMatrix();

    cout << endl;

    graph.displayEdges();

    cout << endl;

    vector<Edge> mst = graph.Prim_algorithm();
    graph.edgeSorting(mst);
    cout << "Миимальный остов: " << endl;
    for (int i = 0; i < mst.size(); i++) {
        cout << "Ребро " << i << ": (" << mst[i].a << ", " << mst[i].b << " Вес: " << mst[i].weight<< ")\n";
    }

    cout << endl;

    graph.MSTadjMatrix(mst, points.size(), num_clusters);
    graph.displayMSTMatrix();

    cout << endl;

    graph.displayComponents();

    graph.displayComponentsStats("components.csv");
    graph.saveEdgesCSV(mst, "edges.csv");

    return 0;
}
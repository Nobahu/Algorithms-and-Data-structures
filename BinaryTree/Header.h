#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//struct Node
//{
//    int key;
//    Node* left;
//    Node* right;
//
//    Node(int data) : key(data), left(nullptr), right(nullptr) {}
//};

class BinaryTree
{
private:

    struct Node
    {
        int key;
        Node* left;
        Node* right;

        Node(int data) : key(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    BinaryTree() : root(nullptr) {}

    Node* Insert(Node* node, int key)
    {
        if (node == nullptr)
        {
            return new Node(key);
        }
        if (key < node->key)
        {
            node->left = Insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = Insert(node->right, key);
        }
        return node;
    }

    Node* Search(Node* node, int key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->key == key)
        {
            return node;
        }

        if (key < node->key)
        {
            return Search(node->left, key);
        }
        else
        {
            return Search(node->right, key);
        }
    }

    Node* Remove(Node* node, int key)
    {
        if (!Search(node,key)) 
        {
            return nullptr;
        }

        if (key < node->key)
        {
            node->left = Remove(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = Remove(node->right, key);
        }

        else
        {
            if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = node->right;
            while (temp != nullptr and temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->key = temp->key;
            node->right = Remove(node->right, temp->key);
        }
        return node;
    }

    void FindDiapElem(Node* node, int MinVal, int MaxVal, vector<int>& DiapElem)
    {

        if (node == nullptr) return;

        if (node->key > MinVal)
        {
            FindDiapElem(node->left, MinVal, MaxVal, DiapElem);
        }

        if (node->key >= MinVal and node->key <= MaxVal)
        {
            DiapElem.push_back(node->key);
        }

        if (node->key < MaxVal)
        {
            FindDiapElem(node->right, MinVal, MaxVal, DiapElem);
        }
    }

    int FindMaxDepth(Node* node,int level = 1)
    {

        if (node == nullptr) { return -1; }

        int leftDepth = FindMaxDepth(node->left);
        int rightDepth = FindMaxDepth(node->right);

        return level = max(leftDepth, rightDepth) + 1;
    }

    void FindAverageDepth(Node* node, int level, int& sumDepth, int& count) {

        if (node == nullptr) {
            return;
        }
        
        sumDepth += level;
        count++;

        // Рекурсивно идем в левое и правое поддерево
        FindAverageDepth(node->left, level + 1, sumDepth, count);
        FindAverageDepth(node->right, level + 1, sumDepth, count);
    }

public:

    BinaryTree() : root(nullptr) {}

    BinaryTree(int key)
    {
        root = new Node(key);
    }

    void SearchMain(int key)
    {
        Node* node = Search(root, key);
        if (!root)
        {
            cout << "Такого ключа в дереве нет!" << endl;
        }
        else if (root->key == key)
        {
            cout << "Такой ключ есть в дереве!" << endl;
        }
    }

    void Insert(int key) {
        root = Insert(root, key);
    }

    int GetLvl(int key)
    {
        int lvl = 1;
        Node* node = Search(root, key);

        if (node == nullptr) { return -1; }

        Node* temp = root;

        while (temp != nullptr)
        {
            if (temp->key == key) { return lvl; }
            temp = (temp->key < key) ? temp->right : temp->left;
            lvl++;
        }

        return -1;
    }

    void Remove(int key) {
        root = Remove(root, key);
    }

    int MaxDepth()
    {
        return FindMaxDepth(root) + 1;
    }

    double AverageDepth() {

        int sumDepth = 0;
        int count = 0;

        FindAverageDepth(root, 1, sumDepth, count);

        return (count == 0) ? 0 : (double)sumDepth / count;
    }

    vector<int> FDEHelper(int MinVal, int MaxVal)
    {
        vector<int> DiapElem;
        FindDiapElem(root, MinVal, MaxVal, DiapElem);
        return DiapElem;
    }

    void printTree(Node* node) {
        if (node != nullptr) {
            std::cout << node->key << " ";
            printTree(node->left);
            printTree(node->right);
        }
    }

    void print() {
        printTree(root);
        std::cout << std::endl;
    }


    void buildTreeFromArray(int* arr, int size) {
        for (int i = 0; i < size; ++i) {
            Insert(arr[i]);
        }
    }

    void BuildOptimalTree(int* arr, int size)
    {
        bool sorted = false;
        for (int i = size; i > 1 and sorted == false; i--)
        {
            sorted = true;
            for (int j = 0; j < i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    sorted = false;
                }
            }
        }
        Balancefunc(arr, 0, size - 1);
    }

    void Balancefunc(int* arr, int left, int right)
    {
        if (left > right) return;

        int mid = (left + right) / 2;
        Insert(arr[mid]);

        Balancefunc(arr, left, mid - 1);
        Balancefunc(arr, mid + 1, right);
    }

};

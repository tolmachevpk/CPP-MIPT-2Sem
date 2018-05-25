#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int INF = 1000000000;
struct Node {
    Node *left = nullptr; //дети
    Node *right = nullptr;
    int leftFacet; // левая граница множества, которым представлена данная вершина
    int rightFacet; //правая граница множества, которым представлена данная вершина
    int currentValue;
    int push; //дополнительная отдельная ячейка
};

//совмещение основного и вспомогательного дерева
void push(Node *node) {
    if (node->push != INF) {
        node->currentValue = node->push;
        if (node->leftFacet == node->rightFacet) {
            return;
        } else {
            node->left->push = node->push;
            node->right->push = node->push;
        }
        node->push = INF;
    }
}

//изменение значений нашего дерева
void modify(Node *node, int newValue, int left, int right) {
    push(node);
    if (right < node->leftFacet) {
        return;
    }
    if (left > node->rightFacet) {
        return;
    } else {
        if (node->leftFacet >= left && right >= node->rightFacet) {
            node->push = newValue;
            push(node);
        } else {
            modify(node->left, newValue, left, right);
            modify(node->right, newValue, left, right);
            node->currentValue = min(node->right->currentValue, node->left->currentValue);
        }
    }
}

//запрос
int query(Node *node, int left, int right) {
    push(node);
    if (right < node->leftFacet || node->rightFacet < left) {
        return INF;
    } else {
        if (left <= node->leftFacet && node->rightFacet <= right) {
            int minVal = min(node->currentValue, node->push);
            return minVal;
        } else {
            return min(query(node->left, left, right), query(node->right, left, right));
        }
    }
}

//постоим дерево с помощью массива
Node *buildTree(vector<int> &values, int left, int right) {
    Node *result = new Node();
    result->push = INF;
    result->leftFacet = left;
    result->rightFacet = right;

    if (left != right) {
        if (right > left) {
            int mid = left + (right - left) / 2;
            result->right = buildTree(values, mid + 1, right);
            result->left = buildTree(values, left, mid);
            result->currentValue = min(result->left->currentValue, result->right->currentValue);
            return result;
        } else {
            return nullptr;
        }
    } else {
        result->currentValue = values[right];
        return result;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> values;
    for (int i = 0; i < n; i++) {
        int R, G, B;
        cin >> R >> G >> B;
        values.push_back(R + G + B);
    }
    Node *node = buildTree(values, 0, n - 1);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int C, D, R, G, B, E, F;
        cin >> C >> D >> R >> G >> B >> E >> F;
        modify(node, R + G + B, C, D);
        cout << query(node, E, F) << endl;
    }
}
#include <iostream>
#include<iomanip>
#include <map>
#include <vector>
#include <algorithm>

struct Graph {
    int num;
    std::map<Graph, int> input;
    std::map<Graph, int> output;

    explicit Graph(const int &n) : num(n) {}
    bool numb(const Graph &n) {
        for (const auto &i: output) {
            if (i.first.num == n.num) return true;
        }
        return false;
    }
    int getw(const Graph &n) {
        for (const auto &i : output) {
            if (i.first.num == n.num) return i.second;
        }
        return 0;
    }
    friend bool operator<(const Graph &left, const Graph &right) {
        return left.num < right.num;
    }

};


void Pair(Graph &left, Graph &right, int w) {
    left.output.insert(std::make_pair(right, w));
    right.input.insert(std::make_pair(left, w));
}

void print (const std::vector<std::vector<int>> &matrix) {
    for (const auto &i:matrix) {
        for (const auto &el:i) {
            std::cout << '|' << std::setw(5) << el << std::setw(3) << '|';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int FloydAlgorithm(std::vector<Graph> &gr) {
    int inf = 100;
    std::vector<std::vector<int>> matrix(gr.size());
    for (auto &i:matrix) {
        i.resize(gr.size());
    }
    for (int i = 0; i < gr.size(); ++i) {
        for (int j = 0; j < gr.size(); ++j) {
            if (i == j) {
                matrix[i][j] = 0;
            } else if (gr[i].numb(gr[j])) {
                matrix[i][j] = gr[i].getw(gr[j]);
            } else {
                matrix[i][j] = inf;
            }
        }
    }
    std::cout << "Matrix for iteration 0 :"<<std::endl;
    print(matrix);

    for (int k = 0; k < gr.size(); ++k) {
        for (int i = 0; i < gr.size(); ++i) {
            for (int j = 0; j < gr.size(); ++j) {
                if (matrix[i][k] != inf && matrix[k][j] != inf) {
                    matrix[i][j] = (matrix[i][j] == inf ? matrix[i][k] + matrix[k][j] :
                                    std::max(matrix[i][j], matrix[i][k] + matrix[k][j]));
                }
            }
        }
        std::cout << "Matrix for iteration " << k + 1 << " :"<< std::endl;
        print(matrix);
    }
    return matrix[0][gr.size() - 1];
}

int main()
{
    int a = 3, b = 5, c = 2, d = 4, e = 3, f = 1, g = 4, h = 3, i = 3, j = 2, k = 5;
    Graph n1(1);
    Graph n2(2);
    Graph n3(3);
    Graph n4(4);
    Graph n5(5);
    Graph n6(6);
    Graph n7(7);
    Graph n8(8);
    Pair(n1, n2, a);
    Pair(n1, n3, e);
    Pair(n2, n4, b);
    Pair(n3, n4, f);
    Pair(n1, n5, i);
    Pair(n5, n6, j);
    Pair(n4, n6, g);
    Pair(n6, n7, h);
    Pair(n4, n7, c);
    Pair(n6, n8, k);
    Pair(n7, n8, d);
    std::vector<Graph> gr = {n1, n2, n3, n4, n5, n6, n7};
    int l = FloydAlgorithm(gr);
    std::cout << "Critical path length = " << l << std::endl;
    return 0;
}
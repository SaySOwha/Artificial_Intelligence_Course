#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "A_Star_Search.h"
#include "PathNode.h"

using namespace std;

// -------- 全局变量 --------//
vector<vector<int>> Maze;
size_t row, column;
int StartX = 1, StartY = 0;
int EndX = 16, EndY = 24;

// -------- main函数 --------//
int main() {
    // 读文件
    ifstream in("input.txt");
    if (!in.is_open()) {
        cout << "Error opening file";
        exit(1);
    }
    while (!in.eof()) {
        char buffer[1024];
        in.getline(buffer, 1024, '\n');
        column = (strlen(buffer) + 1) / 2;
        vector<int> one_row(column);
        for (int i = 0; i < column; i++) {
            one_row[i] = buffer[2 * i] - '0';
        }
        Maze.push_back(one_row);
    }
    row = Maze.size();

    // 开始搜索
    auto start_time = clock();
    A_Star_Search A_Star_Solution(Maze, StartX, StartY, EndX, EndY, row, column);
    PathNode *EndNode = A_Star_Solution.SearchPath();
    auto end_time = clock();
    PathNode *temp = EndNode;

    // 输出结果
    ofstream out("output.txt");
    out << (double) (end_time - start_time) / CLOCKS_PER_SEC << endl;
    char directions[200];
    int count = 0;
    while (temp->parent) {
        int dx = temp->get_x() - temp->parent->get_x();
        int dy = temp->get_y() - temp->parent->get_y();
        if (dx == 1)
            directions[count] = 'D';
        else if (dx == -1)
            directions[count] = 'U';
        else {
            if (dy == 1)
                directions[count] = 'R';
            else
                directions[count] = 'L';
        }
        count++;
        temp = temp->parent;
    }
    for (int i = count - 1; i >= 0; i--) {
        out << directions[i];
    }
    out << endl << count << endl;
    out.close();
    in.close();
    return 0;
}
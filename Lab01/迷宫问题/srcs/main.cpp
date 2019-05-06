#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "A_Star_Search.h"
#include "PathNode.h"
#include "IDA_Star_Search.h"

using namespace std;

// -------- 全局变量 --------//
vector<vector<int>> Maze;
size_t row, column;
int StartX = 1, StartY = 0;
int EndX = 16, EndY = 24;
//int EndX = 28, EndY = 59;

// -------- 输出函数 --------//
void OutPut(PathNode *EndNode, clock_t start_time, clock_t end_time, char *filename) {
    PathNode *temp = EndNode;
    ofstream out(filename);
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
}

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
    in.close();
    row = Maze.size();
    int op = 0;
    cout << "A×搜索输入1 IDA×搜索输入2" << endl;
    cin >> op;
    if (op == 1) {
        // A*搜索
        auto start_time = clock();
        A_Star_Search A_Star_Solution(Maze, StartX, StartY, EndX, EndY, row, column);
        PathNode *EndNode = A_Star_Solution.SearchPath();
        auto end_time = clock();
        OutPut(EndNode, start_time, end_time, "A*_output");
    } else {
        // IDA* 搜索
        auto ida_start_time = clock();
        IDA_Star_Search IDA_Star_Solution(Maze, StartX, StartY, EndX, EndY, row, column);
        PathNode *ida_EndNode = IDA_Star_Solution.SearchPath();
        auto ida_end_time = clock();
        OutPut(ida_EndNode, ida_start_time, ida_end_time, "IDA*_output");
    }
    // 输出结果
    return 0;
}
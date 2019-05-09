//
// Created by yxchen on 19-5-8.
//

#ifndef GOBANG_CHESS_H
#define GOBANG_CHESS_H

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

// 参数定义
class CONFIG {
public:
    static const int BOARD_WIDTH = 15;
    static const int INF = 106666666;
    static const int MAX_SCORE = 50000;
    static const int MIN_SCORE = -50000;
    enum Role {
        Empty = 0, Human = 1, AI = 2
    };
    int HumanScore = 0;
    int AIScore = 0;
    char pieces[3] = {'-', 'O', 'X'};

    vector<pair<string, int>> PatternScore = {
            {"11111",  50000},
            {"011110", 4320},
            {"011100", 720},
            {"001110", 720},
            {"011010", 720},
            {"010110", 720},
            {"11110",  720},
            {"01111",  720},
            {"11011",  720},
            {"10111",  720},
            {"11101",  720},
            {"001100", 120},
            {"001010", 120},
            {"010100", 120},
            {"000100", 20},
            {"001000", 20}
    };
};

// 棋盘
class ChessBoard : CONFIG {
public:
    int board[BOARD_WIDTH][BOARD_WIDTH];

    ChessBoard() {
        for (int i = 0; i < BOARD_WIDTH; i++)
            for (int j = 0; j < BOARD_WIDTH; j++)
                board[i][j] = Empty;
    }

    ChessBoard(const ChessBoard &othr) {
        for (int i = 0; i < BOARD_WIDTH; ++i)
            for (int j = 0; j < BOARD_WIDTH; ++j)
                board[i][j] = othr.board[i][j];
    }

    void PrintBoard(Role role) {
        char str[20];
        if (role == Human)
            strcpy(str, " AI\'s ");
        else
            strcpy(str, " your ");
        cout << "It's" << str << "turn:" << endl;
        cout << "   ";
        for (int i = 0; i < BOARD_WIDTH; i++) {
            cout << setfill('0') << setw(2) << i << ' ';
        }
        cout << endl;
        for (int i = 0; i < BOARD_WIDTH; i++) {
            cout << setfill('0') << setw(2) << i << ' ';
            for (int j = 0; j < BOARD_WIDTH; j++) {
                cout << ' ' << pieces[board[i][j]] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    bool PlacePiece(int x, int y, Role role) {
        if (board[x][y] == Empty) {
            board[x][y] = role;
            return true;
        }
        return false;
    }
};

#endif //GOBANG_CHESS_H

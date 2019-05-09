//
// Created by yxchen on 19-5-8.
//

#ifndef GOBANG_GAME_H
#define GOBANG_GAME_H

#include "Chess.h"
#include <iostream>
#include <iomanip>
#include <memory.h>
#include <vector>

using namespace std;

class Game : CONFIG {
private:
    int MAX_DEPTH = 3;  // 最大搜索层数
    vector<pair<int, int>> Record;

    void HumanTurn() {
        int x = 0, y = 0;
        do {
            cout << "Input the coordinate(x,y)" << endl;
            cin >> x >> y;
            cout << endl;
        } while (!CurBoard.PlacePiece(x, y, Human));
        Record.emplace_back(x, y);
        CurBoard.PrintBoard(Human);
        if (IsWin(x, y, Human)) {
            EndGame(Human);
        } else
            AITurn();
    }

    int cnt[BOARD_WIDTH][BOARD_WIDTH];

    void AITurn() {
        int weight;
        int max = -INF; // 本层的权值上界
        int x = 0, y = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                if (CurBoard.board[i][j] == Empty && CanSearch(CurBoard, i, j)) {
                    weight = MinMax(CurBoard, i, j, AI, 1, -INF, max);
                    cnt[i][j] = weight;
                    if (weight > max) {
                        max = weight; // 更新下层上界
                        x = i;
                        y = j;
                    }
                } else
                    continue;
            }
        }
        CurBoard.PlacePiece(x, y, AI);
        Record.emplace_back(x, y);
        CurBoard.PrintBoard(AI);
        if (IsWin(x, y, AI)) {
            EndGame(AI);
        } else
            HumanTurn();
    }

    Role NextRole(Role role) {
        return role == Human ? AI : Human;
    }

    int MinMax(ChessBoard state, int x, int y, Role role, int depth, int alpha, int beta) {
        ChessBoard newState(state);
        newState.PlacePiece(x, y, NextRole(role));

        int weight = 0;
        int max = -INF; // 下层权值上界
        int min = INF; // 下层权值下界

        if (depth < MAX_DEPTH) {
            // 已输或已胜则不继续搜索
            if (EvaluatePoint(newState, x, y, NextRole(role)) >= MAX_SCORE) {
                if (role == AI)
                    return MAX_SCORE; // 我方胜
                else
                    return MIN_SCORE; // AI胜
            }

            int i, j;
            for (i = 0; i < BOARD_WIDTH; ++i) {
                for (j = 0; j < BOARD_WIDTH; ++j) {
                    if (newState.board[i][j] == Empty && CanSearch(newState, i, j)) {
                        weight = MinMax(newState, i, j, NextRole(role), depth + 1, min, max);

                        if (weight > max)
                            max = weight; // 更新下层上界
                        if (weight < min)
                            min = weight; // 更新下层下界

                        // alpha-beta
                        if (role == Human) {
                            if (max >= alpha)
                                return max;
                        } else {
                            if (min <= beta)
                                return min;
                        }
                    } else
                        continue;
                }
            }

            if (role == Human)
                return max; // 最大层给出最大值
            else
                return min; // 最小层给出最小值
        } else {
            weight = EvaluateState(newState, Human); // 评估我方局面
            weight -= role == AI ? EvaluateState(newState, AI) * 10 : EvaluateState(newState, AI); // 评估对方局面
            return weight; // 搜索到限定层后给出权值
        }
    }

    // 将点加入到待匹配的string中
    void PushIntoLine(ChessBoard CurBoard, int x, int y, Role role, string &line) {
        if (CurBoard.board[x][y] == role)
            line.push_back('1');
        else if (CurBoard.board[x][y] == Empty)
            line.push_back('0');
        else
            line.push_back('X');
    }

    // 评价一个点的分数
    int EvaluatePoint(ChessBoard CurBoard, int x, int y, Role role) {
        int value = 0;
        string lines[4]; // 横行 竖列 斜线 反斜线
        auto BOARD_WIDTH = CONFIG::BOARD_WIDTH;
        for (int i = max(0, x - 5); i < min(BOARD_WIDTH, x + 6); i++)
            if (i == x)
                lines[0].push_back('1');
            else
                PushIntoLine(CurBoard, i, y, role, lines[0]);

        for (int i = max(0, y - 5); i < min(BOARD_WIDTH, y + 6); i++)
            if (i == y)
                lines[1].push_back('1');
            else
                PushIntoLine(CurBoard, x, i, role, lines[1]);

        for (int i = x - min(min(x, y), 5), j = y - min(min(x, y), 5);
             i < min(BOARD_WIDTH, x + 6) && j < min(BOARD_WIDTH, y + 6); i++, j++)
            if (i == x)
                lines[2].push_back('1');
            else
                PushIntoLine(CurBoard, i, j, role, lines[2]);

        for (int i = x + min(min(y, BOARD_WIDTH - 1 - x), 5), j = y - min(min(y, BOARD_WIDTH - 1 - x), 5);
             i >= max(0, x - 5) && j < min(BOARD_WIDTH, y + 6); i--, j++)
            if (i == x)
                lines[3].push_back('1');
            else
                PushIntoLine(CurBoard, i, j, role, lines[3]);

        for (auto &line : lines) {
            value += GetValue(line);
        }
        return value;
    }

    // 对一条线进行匹配得分
    int GetValue(string line) {
        int value = 0;
        for (auto &ps : PatternScore) {
            unsigned long pos = line.find(ps.first);
            while (pos != string::npos) {
                value += ps.second;
                pos = line.find(ps.first, pos + 1);
            }
        }
        return value;
    }

    // 评估整个局面的分数
    int EvaluateState(ChessBoard CurBoard, Role role) {
        int value = 0;
        string lines[6];

        // 从四个方向产生
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                PushIntoLine(CurBoard, i, j, role, lines[0]);
                PushIntoLine(CurBoard, j, i, role, lines[1]);
                PushIntoLine(CurBoard, i + j, j, role, lines[2]);
                PushIntoLine(CurBoard, i - j, j, role, lines[3]);
                PushIntoLine(CurBoard, j, i + j, role, lines[4]);
                PushIntoLine(CurBoard, BOARD_WIDTH - j - 1, i + j, role, lines[5]);
            }
            // 估计
            int special = i == 0 ? 4 : 6;
            for (int p = 0; p < special; ++p) {
                value += GetValue(lines[p]);
            }
        }
        return value;
    }

    bool IsWin(int x, int y, Role role) {
        if (EvaluatePoint(CurBoard, x, y, role) >= MAX_SCORE)
            return true;
        return false;
    }

    bool CanSearch(ChessBoard CurBoard, int x, int y) {
        int TmpX = x - 1;
        int TmpY = y - 1;
        for (int i = 0; TmpX < BOARD_WIDTH && i < 3; ++TmpX, ++i) {
            int ty = TmpY;
            for (int j = 0; ty < BOARD_WIDTH && j < 3; ++ty, ++j) {
                if (TmpX >= 0 && ty >= 0 && CurBoard.board[TmpX][ty] != Empty)
                    return true;
                else
                    continue;
            }
        }
        return false;
    }

public:
    ChessBoard CurBoard;    // 当前棋盘

    void StartGame() {
        int StartX;
        int StartY;
        StartX = 7;
        StartY = 7;
        CurBoard.PlacePiece(StartX, StartY, AI);
        Record.emplace_back(StartX, StartY);
        CurBoard.PrintBoard(AI);
        HumanTurn();
    }

    void EndGame(Role winner) {
        cout << "  AI \t  ME" << endl;
        int turn = 0;
        for (auto item:Record) {
            cout << '[' << item.first << ',' << item.second << ']';
            if (turn % 2 == 0) {
                cout << '\t';
            } else {
                cout << endl;
            }
            turn++;
        }
        switch (winner) {
            case Human:
                cout << "I WIN! " << endl;
                break;
            case AI:
                cout << "AI WIN!" << endl;
                break;
            default:
                cout << "NO ONE WIN!" << endl;
                break;
        }
    }


};


#endif //GOBANG_GAME_H

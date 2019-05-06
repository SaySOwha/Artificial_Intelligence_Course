//
// Created by yxchen on 19-5-6.
//

#ifndef AI_LAB01_A_STAR_SEARCH_H
#define AI_LAB01_A_STAR_SEARCH_H

#include <vector>
#include <cmath>
#include <list>
#include "PathNode.h"

using namespace std;

class A_Star_Search {
private:
    vector<vector<int>> Maze;
    int StartX;
    int StartY;
    int EndX;
    int EndY;
    int Row, Column;

    int GetF(int CurX, int CurY) {
        int g = static_cast<int>(abs(StartX - CurX) + abs(StartY - StartY));
        int h = static_cast<int>(abs(EndX - CurX) + abs(EndY - CurY));
        return g + h;
    }

    PathNode *GetMinF(list<PathNode *> OpenList);

    bool Pass(int x, int y);

    list<PathNode *>
    HandleChildNode(PathNode *curMinFNode, int x, int y, list<PathNode *> OpenList, list<PathNode *> CloseList);

    bool IsExistList(PathNode *child, list<PathNode *> CloseList);

public:
    A_Star_Search(vector<vector<int>> Maze, int StartX, int StartY, int EndX, int EndY, int Row, int Column) {
        this->Maze = Maze;
        this->StartX = StartX;
        this->StartY = StartY;
        this->EndX = EndX;
        this->EndY = EndY;
        this->Row = Row;
        this->Column = Column;
    }

    PathNode *SearchPath();

};


#endif //AI_LAB01_A_STAR_SEARCH_H

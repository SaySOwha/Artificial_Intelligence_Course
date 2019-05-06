//
// Created by yxchen on 19-5-6.
//

#ifndef AI_LAB01_IDA_STAR_SEARCH_H
#define AI_LAB01_IDA_STAR_SEARCH_H

#include <vector>
#include "PathNode.h"
#include <cmath>

using namespace std;

class IDA_Star_Search {
private:
    vector<vector<int>> Maze;
    int StartX;
    int StartY;
    int EndX;
    int EndY;
    int Row, Column;
    PathNode *EndNode;

    bool DFS(PathNode *p, int MaxF);

public:
    IDA_Star_Search(vector<vector<int>> Maze, int StartX, int StartY, int EndX, int EndY, int Row, int Column) {
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


#endif //AI_LAB01_IDA_STAR_SEARCH_H

//
// Created by yxchen on 19-5-6.
//

#include "A_Star_Search.h"
#include <iostream>

PathNode *A_Star_Search::GetMinF(list<PathNode *> OpenList) {
    int MinF = 1000000;
    PathNode *temp = nullptr;
    for (auto node:OpenList) {
        if (node->get_f() < MinF) {
            MinF = node->get_f();
            temp = node;
        }
    }
    return temp;
}

bool A_Star_Search::Pass(int x, int y) {
    //边界判断
    if (x >= 0 && x < Column && y >= 0 && y < Column) {
        //障碍判断
        return Maze[x][y] == 0;
    } else {
        return false;
    }
}

bool A_Star_Search::IsExistList(PathNode *child, list<PathNode *> CloseList) {
    for (auto node:CloseList) {
        if (node->get_x() == child->get_x() && node->get_y() == child->get_y())
            return true;
    }
    return false;
}


list<PathNode *>
A_Star_Search::HandleChildNode(PathNode *curMinFNode, int x, int y, list<PathNode *> OpenList,
                               list<PathNode *> CloseList) {
    PathNode *child;
    if (Pass(x, y)) {
        child = new PathNode(x, y, GetF(x, y));
        if (!IsExistList(child, CloseList) && !IsExistList(child, OpenList))//
        {
            child->parent = curMinFNode;
            OpenList.push_back(child);
        }
    }
    return OpenList;
}


PathNode *A_Star_Search::SearchPath() {
    list<PathNode *> OpenList;
    list<PathNode *> CloseList;
    PathNode *EndNode;
    auto StartNode = new PathNode(StartX, StartY, 0);
    OpenList.push_back(StartNode);
    while (!OpenList.empty()) {
        PathNode *CurMinFNode = GetMinF(OpenList);
        list<PathNode *>::iterator itList;
        for (itList = OpenList.begin(); itList != OpenList.end(); itList++) {
            PathNode *temp = *itList;
            if (temp->get_x() == CurMinFNode->get_x() && temp->get_y() == CurMinFNode->get_y()) {
                OpenList.erase(itList);
                CloseList.push_back(temp);
                break;
            }
        }
        if (CurMinFNode->get_x() == EndX && CurMinFNode->get_y() == EndY) {
            EndNode = CurMinFNode;
            break;
        } else {
            OpenList = HandleChildNode(CurMinFNode, CurMinFNode->get_x(), CurMinFNode->get_y() + 1, OpenList, CloseList);
            OpenList = HandleChildNode(CurMinFNode, CurMinFNode->get_x() + 1, CurMinFNode->get_y(), OpenList, CloseList);
            OpenList = HandleChildNode(CurMinFNode, CurMinFNode->get_x(), CurMinFNode->get_y() - 1, OpenList, CloseList);
            OpenList = HandleChildNode(CurMinFNode, CurMinFNode->get_x() - 1, CurMinFNode->get_y(), OpenList, CloseList);
        }
    }

    return EndNode;
}



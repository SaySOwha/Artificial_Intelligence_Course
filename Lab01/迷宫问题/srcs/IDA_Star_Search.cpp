//
// Created by yxchen on 19-5-6.
//

#include "IDA_Star_Search.h"
#include <iostream>

bool IDA_Star_Search::DFS(PathNode *p, int MaxF) {
    int x = p->get_x();
    int y = p->get_y();
    if (x == EndX && y == EndY) {
        EndNode = p;
        return true;
    }
    if (p->get_f() > MaxF)
        return false;

    if (x < 0 || y < 0 || x >= Row || y >= Column || Maze[x][y] == 1)
        return false;

    auto pr = new PathNode(x, y + 1);
    pr->parent = p;
    pr->depth = p->depth + 1;
    pr->set_f(EndX, EndY);
    auto pl = new PathNode(x, y - 1);
    pl->parent = p;
    pl->depth = p->depth + 1;
    pl->set_f(EndX, EndY);
    auto pu = new PathNode(x - 1, y);
    pu->parent = p;
    pu->depth = p->depth + 1;
    pu->set_f(EndX, EndY);
    auto pd = new PathNode(x + 1, y);
    pd->parent = p;
    pd->depth = p->depth + 1;
    pd->set_f(EndX, EndY);

    Maze[x][y] = 1;
    if (DFS(pr, MaxF))
        return true;
    if (DFS(pd, MaxF))
        return true;
    if (DFS(pl, MaxF))
        return true;
    if (DFS(pu, MaxF))
        return true;
    Maze[x][y] = 0;

    return false;
}

PathNode *IDA_Star_Search::SearchPath() {
    auto StartNode = new PathNode(StartX, StartY);
    StartNode->set_f(EndX, EndY);
    int maxf = StartNode->get_f();
    while (!DFS(StartNode, maxf)) {
        maxf++;
    }
    return EndNode;
}

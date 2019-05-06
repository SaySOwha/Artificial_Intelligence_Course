//
// Created by yxchen on 19-5-6.
//

#ifndef AI_LAB01_PATHNODE_H
#define AI_LAB01_PATHNODE_H

#include <cmath>

using namespace std;

class PathNode {
private:
    int x;
    int y;

public:
    int f;
    int depth;
    PathNode *parent;

    PathNode(int x, int y) {
        this->x = x;
        this->y = y;
        f = 0;
        depth = 0;
    }

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    int get_f() {
        return f;
    }

    void set_f(int EndX, int EndY) {
        f = static_cast<int>(depth + abs(EndX - x) + abs(EndY - y));
    }

};


#endif //AI_LAB01_PATHNODE_H

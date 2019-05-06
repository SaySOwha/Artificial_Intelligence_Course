//
// Created by yxchen on 19-5-6.
//

#ifndef AI_LAB01_PATHNODE_H
#define AI_LAB01_PATHNODE_H


class PathNode {
private:
    int x;
    int y;
    int f;

public:
    PathNode *parent;

    PathNode(int x, int y, int f) {
        this->x = x;
        this->y = y;
        this->f = f;
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


};


#endif //AI_LAB01_PATHNODE_H

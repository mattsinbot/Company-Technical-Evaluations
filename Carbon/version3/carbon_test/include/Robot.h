#ifndef ROBOT_H_
#define ROBOT_H_

/* Forward declaration */
#include "pt2d.h"

class Robot{
  private:
    int rx;
    int ry;
  public:
    Robot(int x, int y) {rx = x; ry = y;}
    pt2d move(int);
    void update_state(pt2d);
    int get_px() {return rx;}
    int get_py() {return ry;}
};

#endif

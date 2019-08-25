#include "robot.h"

// class pt2d;


pt2d robot::move(int srch_dir) {
      if (srch_dir == 0) {pt2d pt(rx, ry+1); return pt;}      // move right
      else if (srch_dir == 1) {pt2d pt(rx, ry-1); return pt;} // move left
      else if (srch_dir == 2) {pt2d pt(rx-1, ry); return pt;} // move up
      else {pt2d pt(rx+1, ry); return pt;}                    // move down
}

void robot::update_state(pt2d pt) {
      rx = pt.getpt_x(); 
      ry = pt.getpt_y();
}

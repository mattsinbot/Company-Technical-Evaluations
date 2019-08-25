#ifndef ROBOT_H_
#define ROBOT_H_

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

pt2d Robot::move(int srch_dir) {
      if (srch_dir == 0) {pt2d pt(rx, ry+1); return pt;}      // move right
      else if (srch_dir == 1) {pt2d pt(rx, ry-1); return pt;} // move left
      else if (srch_dir == 2) {pt2d pt(rx-1, ry); return pt;} // move up
      else {pt2d pt(rx+1, ry); return pt;}                    // move down
}

void Robot::update_state(pt2d pt) {
      rx = pt.getpt_x(); 
      ry = pt.getpt_y();
}

#endif

#ifndef PT_2D_
#define PT_2D_

class pt2d{
  private:
    int x, y;
  public:
    pt2d() {x = 0; y = 0;}
    pt2d(int, int);
    int getpt_x();
    int getpt_y();
};

#endif

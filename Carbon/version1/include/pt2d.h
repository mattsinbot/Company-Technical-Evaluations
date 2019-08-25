class pt2d{
  private:
    int x, y;
  public:
    pt2d() {x = 0; y = 0;}
    pt2d(int, int);
    int getpt_x();
    int getpt_y();
};

pt2d::pt2d(int a, int b) {x =a; y = b;}
int pt2d::getpt_x(){return x;}
int pt2d::getpt_y(){return y;}

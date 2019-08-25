#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

/* Integrator Function */
void EulerIntegrater(vector<double>* x, vector<double>* y, vector<double>* dx, vector<double>* dy, double dt, double F, double m, double k, double tf) {
    int i = 0;
    double t;

    while (t < tf) {
        dx->push_back(y->at(i));
        dy->push_back((-k/m)*x->at(i) + F/m);

        if (dx->at(i+1) >= 0) {
            F = -0.5;
        }
        else {
            F = 0.5;
        }

        x->push_back(x->at(i) + dt*dx->at(i));
        y->push_back(y->at(i) + dt*dy->at(i));

        i++;
        t += dt;
    }
}

/* Euler Method */
int main(int argc, char *argv[]) {
    double k = 4, m = 4, F;
    double x0 = 0, y0 = 0, dx0 = 0, dy0 = 0, t0 = 0, tf = 10;
    double dt = 0.1;
    vector<double> x, y, dx, dy;
    
    // Initialize all the arrays
    x.push_back(x0);   y.push_back(y0); 
    dx.push_back(dx0); dy.push_back(dy0);

    // Call Euler Integrator
    EulerIntegrater(&x, &y, &dx, &dy, dt, F, m, k, tf);

    // Print the result
    double t1 = 0;
    for (int i = 0; i < x.size(); i++) {
        printf("%2.2lf, %2.4lf, %2.4lf, %2.4lf, %2.4lf\n", t1, x[i], y[i], dx[i], dy[i]);
        t1 += dt;
   }
}

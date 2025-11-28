#include <iostream>
#include <random>
#include <vector>
#include <fstream>
using namespace std;

void save_path(const vector<double>& A, const string& filename) {
    ofstream out(filename);
    for (int i = 0; i < A.size(); ++i) {
        out << i << "," << A[i] << "\n";
    }
}
vector<double> brownian_bridge(int n, double drift, double diffusion_coefficient){

    random_device rd;
    mt19937 gen(rd());
    int steps = pow(2,n);
    double dt = 1.0/steps;

    vector<double> Z(steps, 0.0);


    normal_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < steps; i++) {
        double z = dist(gen);
        Z[i] = z;
    }
    vector<double> BM(steps+1,0.0);

    vector<double> W(steps+1,0.0);
    W[steps]= sqrt(steps*dt)*Z[steps-1];
    
    int inc = pow(2,n);
    for (int i = 1; i<n+1; i++){
        int l = 0, u= inc;
        for (int j = inc/2;j<pow(2,n);j=j+inc){
            double a = ((u-j)*W[l]+(j-l)*W[u])/(u-l);
            double b = sqrt((u-j)*(j-l)*dt/(u-l));
            W[j]=a+b*Z[j];
            l+=inc;
            u+=inc;
        }
        inc=inc/2;
    }

    for (int i = 0; i<steps+1; i++){
        BM[i]=drift*i*dt + diffusion_coefficient*W[i];
    }

    return BM;
}


int main() {

    auto BM = brownian_bridge(15, 1.0, 0.5);
    save_path(BM, "plot.csv");
    return 0;
}
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
vector<double> brownian_motion(int n, double drift, double diffusion_coefficient){

    random_device rd;
    mt19937 gen(rd());
    vector<double> Z(n, 0.0);
    double dt = 1.0/n;

    normal_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        double z = dist(gen);
        Z[i] = z;
    }

    vector<double> W(n+1,0.0);

    for (int i = 1; i<n+1; i++){
        W[i]=W[i-1]+sqrt(dt)*Z[i-1];
    }

    vector<double> BM(n+1,0.0);

    for (int i = 0; i<n+1; i++){
        BM[i]=drift*i*dt + diffusion_coefficient*W[i];
    }

    return BM;
}

int main() {

    auto BM = brownian_motion(50, 1.0, 0.5);
    save_path(BM, "plot.csv");
    return 0;
}
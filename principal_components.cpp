#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void save_path(const vector<double> &A, const string &filename)
{
    ofstream out(filename);
    for (int i = 0; i < A.size(); ++i)
    {
        out << i << "," << A[i] << "\n";
    }
}
vector<double> brownian_motion(int n, int k, double drift, double diffusion_coefficient)
{

    random_device rd;
    mt19937 gen(rd());
    vector<double> Z(k, 0.0);
    double dt = 1.0 / n;

    normal_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < k; ++i)
    {
        double z = dist(gen);
        Z[i] = z;
    }

    vector<double> W(n + 1, 0.0), lambda(k, 0.0);
    vector<vector<double>> v(n, vector<double>(k, 0.0)), a(n, vector<double>(k, 0.0));

    for (int i = 0; i < k; ++i)
    {
        lambda[i] = dt / (4 * pow(sin((2 * i + 1) * M_PI / (2.0 * (2 * n + 1))), 2));
    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            v[j][i] = (2 * sin(((2 * i + 1) * (j + 1) * M_PI) / (2 * n + 1))) / sqrt(2 * n + 1);
        }
    }
    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            a[j][i] = sqrt(lambda[i]) * v[i][j];
        }
    }
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < k; ++i)
        {
            W[j + 1] += a[j][i] * Z[i];
        }
    }
    vector<double> BM(n + 1, 0.0);

    for (int i = 0; i < n + 1; i++)
    {
        BM[i] = drift * i * dt + diffusion_coefficient * W[i];
    }

    return BM;
}

int main()
{

    auto BM = brownian_motion(250, 50, 1.0, 0.5);
    save_path(BM, "plot.csv");
    return 0;
}
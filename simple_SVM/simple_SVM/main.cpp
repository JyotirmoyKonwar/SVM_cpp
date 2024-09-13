#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // for std::max and std::min
#include <numeric>   // for std::accumulate
#include <cstdlib>   // for std::rand
#include <ctime>     // for std::time
#include <functional> // for std::function

using namespace std;

class SVM {
public:
    SVM(string kernel = "linear", double C = 10000.0, int max_iter = 100000, int degree = 3, double gamma = 1.0) {
        this->C = C;
        this->max_iter = max_iter;
        this->degree = degree;
        this->gamma = gamma;
        setKernel(kernel);
    }

    void fit(const vector<vector<double>>& X, const vector<int>& y) {
        this->X = X;
        this->y.resize(y.size());
        for (size_t i = 0; i < y.size(); i++) {
            this->y[i] = y[i] * 2 - 1;
        }
        this->lambdas = vector<double>(y.size(), 0.0);
        this->K = kernel(this->X, this->X);
        
        for (int iter = 0; iter < max_iter; iter++) {
            for (size_t idxM = 0; idxM < lambdas.size(); idxM++) {
                int idxL = rand() % lambdas.size();
                vector<vector<double>> Q(2, vector<double>(2));
                Q[0][0] = K[idxM][idxM];
                Q[0][1] = K[idxM][idxL];
                Q[1][0] = K[idxL][idxM];
                Q[1][1] = K[idxL][idxL];
                vector<double> v0 = { lambdas[idxM], lambdas[idxL] };
                vector<double> k0 = { 1.0 - dotProduct(lambdas, K[idxM]), 1.0 - dotProduct(lambdas, K[idxL]) };
                vector<double> u = { -y[idxL], y[idxM] };
                double t_max = (dotProduct(k0, u)) / (dotProduct(dotProduct(Q, u), u) + 1E-15);
                vector<double> t_u = scalarMultiply(u, restrictToSquare(t_max, v0, u));
                lambdas[idxM] = v0[0] + t_u[0];
                lambdas[idxL] = v0[1] + t_u[1];
            }
        }

        vector<int> idx;
        for (size_t i = 0; i < lambdas.size(); i++) {
            if (lambdas[i] > 1E-15) {
                idx.push_back(i);
            }
        }
        double sum = 0.0;
        for (int i : idx) {
            sum += (1.0 - dotProduct(lambdas, K[i])) * y[i];
        }
        b = sum / idx.size();
    }

    vector<double> decisionFunction(const vector<vector<double>>& X) {
        vector<vector<double>> Kx = kernel(X, this->X);
        vector<double> decisions(X.size(), b);
        for (size_t i = 0; i < X.size(); i++) {
            for (size_t j = 0; j < this->X.size(); j++) {
                decisions[i] += Kx[i][j] * y[j] * lambdas[j];
            }
        }
        return decisions;
    }

    vector<int> predict(const vector<vector<double>>& X) {
        vector<double> decisions = decisionFunction(X);
        vector<int> predictions(X.size());
        for (size_t i = 0; i < decisions.size(); i++) {
            predictions[i] = (sign(decisions[i]) + 1) / 2;
        }
        return predictions;
    }

private:
    double C;
    int max_iter;
    int degree;
    double gamma;
    vector<vector<double>> X;
    vector<int> y;
    vector<double> lambdas;
    vector<vector<double>> K;
    double b;

    function<vector<vector<double>>(const vector<vector<double>>&, const vector<vector<double>>&) > kernel;

    void setKernel(const string& kernelType) {
        if (kernelType == "linear") {
            kernel = [this](const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
                return linearKernel(X1, X2);
            };
        } else if (kernelType == "poly") {
            kernel = [this](const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
                return polyKernel(X1, X2);
            };
        } else if (kernelType == "rbf") {
            kernel = [this](const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
                return rbfKernel(X1, X2);
            };
        }
    }

    vector<vector<double>> linearKernel(const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
        vector<vector<double>> K(X1.size(), vector<double>(X2.size(), 0.0));
        for (size_t i = 0; i < X1.size(); i++) {
            for (size_t j = 0; j < X2.size(); j++) {
                K[i][j] = inner_product(X1[i].begin(), X1[i].end(), X2[j].begin(), 0.0);
            }
        }
        return K;
    }

    vector<vector<double>> polyKernel(const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
        vector<vector<double>> K(X1.size(), vector<double>(X2.size(), 0.0));
        for (size_t i = 0; i < X1.size(); i++) {
            for (size_t j = 0; j < X2.size(); j++) {
                K[i][j] = pow(inner_product(X1[i].begin(), X1[i].end(), X2[j].begin(), 0.0), degree);
            }
        }
        return K;
    }

    vector<vector<double>> rbfKernel(const vector<vector<double>>& X1, const vector<vector<double>>& X2) {
        vector<vector<double>> K(X1.size(), vector<double>(X2.size(), 0.0));
        for (size_t i = 0; i < X1.size(); i++) {
            for (size_t j = 0; j < X2.size(); j++) {
                double sum = 0.0;
                for (size_t k = 0; k < X1[i].size(); k++) {
                    sum += pow(X1[i][k] - X2[j][k], 2);
                }
                K[i][j] = exp(-gamma * sum);
            }
        }
        return K;
    }

    double restrictToSquare(double t, const vector<double>& v0, const vector<double>& u) {
        vector<double> clipped = clipVector({ v0[0] + t * u[0], v0[1] + t * u[1] }, 0, C);
        return (clipped[1] - v0[1]) / u[1];
    }

    vector<double> clipVector(const vector<double>& vec, double minVal, double maxVal) {
        vector<double> clipped(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            clipped[i] = max(min(vec[i], maxVal), minVal);
        }
        return clipped;
    }

    vector<double> dotProduct(const vector<double>& a, const vector<vector<double>>& B) {
        vector<double> result(B.size(), 0.0);
        for (size_t i = 0; i < B.size(); i++) {
            result[i] = inner_product(a.begin(), a.end(), B[i].begin(), 0.0);
        }
        return result;
    }

    double dotProduct(const vector<double>& a, const vector<double>& b) {
        return inner_product(a.begin(), a.end(), b.begin(), 0.0);
    }

    vector<double> dotProduct(const vector<vector<double>>& A, const vector<double>& b) {
        vector<double> result(A.size(), 0.0);
        for (size_t i = 0; i < A.size(); i++) {
            result[i] = inner_product(A[i].begin(), A[i].end(), b.begin(), 0.0);
        }
        return result;
    }

    vector<double> scalarMultiply(const vector<double>& vec, double scalar) {
        vector<double> result(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            result[i] = vec[i] * scalar;
        }
        return result;
    }

    int sign(double x) {
        return (x > 0) - (x < 0);
    }
};

int main() {
    srand(time(0)); // Seed for random number generation

    // Example usage
    vector<vector<double>> X = {
        {1.0, 2.0},
        {2.0, 3.0},
        {3.0, 3.0},
        {2.0, 1.0},
        {3.0, 2.0}
    };

    vector<int> y = {0, 0, 1, 1, 1};

    SVM svm("linear");
    svm.fit(X, y);

    vector<vector<double>> testX = {
        {2.5, 3.0},
        {3.0, 2.0}
    };

    vector<int> predictions = svm.predict(testX);
    for (int pred : predictions) {
        cout << "Prediction: " << pred << endl;
    }

    return 0;
}

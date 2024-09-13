#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>

using namespace std;

double getHingeLoss(double x1, double x2, int y, double w1, double w2, double b) {
    double loss = (y == 1) ? 1 - (w1 * x1 + w2 * x2 + b) : 1 + (w1 * x1 + w2 * x2 + b);
    return (loss < 0) ? 0 : loss;
}

double getSVMCost(vector<double> &x1, vector<double> &x2, vector<int> &y, double w1, double w2, double b, double &dw1, double &dw2, double &db) {
    int n = static_cast<int>(y.size());
    double cost = 0;
    dw1 = 0;
    dw2 = 0;
    db = 0;
    for (int i = 0; i < n; i++) {
        double loss = getHingeLoss(x1[i], x2[i], y[i], w1, w2, b);
        cost += loss;
        if (loss > 0) {
            dw1 += (-x1[i] * y[i]);
            dw2 += (-x2[i] * y[i]);
            db += (-y[i]);
        }
    }
    cost /= n;
    dw1 /= n;
    dw2 /= n;
    db /= n;
    return cost;
}

void trainSVM(vector<double> &x1, vector<double> &x2, vector<int> &y, double &w1, double &w2, double &b) {
    double lrate = 0.005;
    double threshold = 0.005;
    w1 = 1;
    w2 = 1;
    b = 0;
    double dw1 = 0, dw2 = 0, db = 0;
    int iter = 0;
    double prev_cost = 0;
    const int max_iter_no_change = 100000;

    while (true) {
        double cost = getSVMCost(x1, x2, y, w1, w2, b, dw1, dw2, db);
        if (iter % 1000 == 0) {
            cout << "Iter: " << iter << " cost = " << cost << " dw1 = " << dw1 << " dw2 = " << dw2 << " db = " << db << endl;
        }
        if (iter >= max_iter_no_change && abs(cost - prev_cost) < threshold) {
            cout << "Cost has not changed significantly in the last " << max_iter_no_change << " iterations. Stopping training." << endl;
            break;
        }
        
        iter++;
        if (abs(dw1) < threshold && abs(dw2) < threshold && abs(db) < threshold) {
            break;
        }
        w1 -= lrate * dw1;
        w2 -= lrate * dw2;
        b -= lrate * db;
    }
}

void readData(const string &filename, vector<double> &x1, vector<double> &x2, vector<int> &y, int label, int max_points = 100) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    int count = 0;
    while (getline(file, line) && count < max_points) {
        stringstream ss(line);
        double val1, val2;
        ss >> val1 >> val2;
        x1.push_back(val1);
        x2.push_back(val2);
        y.push_back(label);
        count++;
    }
    file.close();
}

int main() {
    vector<double> X1;
    vector<double> X2;
    vector<int> Y;
    unordered_map<int, string> label_map;

    // label map
    label_map[0] = "A";
    label_map[1] = "E";
    label_map[2] = "I";
    label_map[3] = "O";
    label_map[4] = "U";

    
    //readData("C:\\Users\\Jyo\\Downloads\\OneDrive_1_14-06-2024\\a.txt", X1, X2, Y, 0);
    //readData("C:\\Users\\Jyo\\Downloads\\OneDrive_1_14-06-2024\\e.txt", X1, X2, Y, 1);
    readData("C:\\Users\\Jyo\\Downloads\\OneDrive_1_14-06-2024\\i.txt", X1, X2, Y, 2);
    readData("C:\\Users\\Jyo\\Downloads\\OneDrive_1_14-06-2024\\o.txt", X1, X2, Y, 3);
    readData("C:\\Users\\Jyo\\Downloads\\OneDrive_1_14-06-2024\\u.txt", X1, X2, Y, 4);

    int num_classes = 5; 
    vector<double> W1(num_classes), W2(num_classes), B(num_classes);

    
    for (int i = 0; i < num_classes; i++) {
        vector<int> binary_y(Y.size());
        for (int j = 0; j < Y.size(); j++) {
            binary_y[j] = (Y[j] == i) ? 1 : -1;
        }
        cout << "Training for class " << label_map[i] << endl;
        trainSVM(X1, X2, binary_y, W1[i], W2[i], B[i]);
        double m = -W1[i] / W2[i];
        double c = -B[i] / W2[i];
        cout << "Class " << label_map[i] << ": y = " << m << " * x + " << c << endl;
		cout<< "(-2,"<< m*(-2) +c<<") " <<"(4,"<< m*4 +c<<") "<<endl;
    }
	cin.get();
    return 0;
}

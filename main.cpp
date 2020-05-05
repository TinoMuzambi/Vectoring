#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

void printVector(string name, const vector<int>* nums) {
    cout << name << endl;
    for (int i = 0; i < nums->size(); ++i) {
        cout << i << " = " << nums->at(i) << endl;
    }
    cout << endl;
}

double vecDistance(vector<int> vec, vector<int> oVec) {
    double sum = 0;
    for (int i = 0; i < 3; ++i) {
        int diff = vec[i] - oVec[i];
        sum += pow(diff, 2.0);
    }
    return sqrt(sum);
}

struct vec {
    int clusterID;
    double minDist;
    vector<int> x;

    vec(int clusterID, double minDist, vector<int> x):
        clusterID(clusterID),
        minDist(minDist),
        x(move(x)) {}
};

int main() {
    vector<int> x1 = {1, 5, 7};
    vector<int> x2 = {9, 2, 1};
    vector<int> x3 = {5, 5, 1};
    vector<int> x4 = {0, 1, 3};
    vector<int> x5 = {9, 8, 6};
    vector<int> x6 = {2, 7, 1};

    vector<int> c0 = {1, 5, 7};
    vector<int> c1 = {2, 7, 1};
    vector<int> c2 = {9, 8, 6};

    vector<vector<int>> centroids;
    centroids.reserve(3);
    centroids.push_back(c0);
    centroids.push_back(c1);
    centroids.push_back(c2);

    vector<vec> hists;
    hists.reserve(6);
    hists.emplace_back(-1, __DBL_MAX__, x1);
    hists.emplace_back(-1, __DBL_MAX__, x2);
    hists.emplace_back(-1, __DBL_MAX__, x3);
    hists.emplace_back(-1, __DBL_MAX__, x4);
    hists.emplace_back(-1, __DBL_MAX__, x5);
    hists.emplace_back(-1, __DBL_MAX__, x6);

    for (auto& hist : hists) {
        for (int i = 0; i < centroids.size(); ++i) {
            double dist = vecDistance(hist.x, centroids[i]);
            if (dist < hist.minDist) {
                hist.minDist = dist;
                hist.clusterID = i;
            }
        }
    }

    for (int i = 0; i < centroids.size(); ++i) {
        printVector("centroid" + to_string(i), &centroids[i]);
    }

    vector<vector<int>> newCentroids;
    newCentroids.reserve(3);
    vector<int> newCentroid;
    newCentroid.reserve(3);
    newCentroid.push_back(0);
    newCentroid.push_back(0);
    newCentroid.push_back(0);
    newCentroids.push_back(newCentroid);
    newCentroids.push_back(newCentroid);
    newCentroids.push_back(newCentroid);
    vector<int> noCentroids;
    noCentroids.reserve(3);
    noCentroids.push_back(0);
    noCentroids.push_back(0);
    noCentroids.push_back(0);
    for (auto& hist : hists) {
        for (int i = 0; i < centroids.size(); ++i) {
            if (hist.clusterID == i) {
                noCentroids[i]++;
                for (int j = 0; j < centroids.size(); ++j) {
                    newCentroids[i][j] += hist.x[j];
                }
            }
        }
    }

    for (auto& nCentroid : newCentroids) {
        for (int i = 0; i < nCentroid.size(); ++i) {
            nCentroid[i] /= noCentroids[i];
        }
    }

    for (int k = 0; k < newCentroids.size(); ++k) {
        centroids[k] = newCentroids[k];
    }

    for (int i = 0; i < centroids.size(); ++i) {
        printVector("after. centroid" + to_string(i), &centroids[i]);
    }

    return 0;
}

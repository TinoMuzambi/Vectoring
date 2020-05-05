#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

void printVector(string name, const vector<unsigned int>* nums) {
    cout << name << endl;
    for (int i = 0; i < nums->size(); ++i) {
        cout << i << " = " << nums->at(i) << endl;
    }
    cout << endl;
}

double vecDistance(vector<unsigned int> vec, vector<unsigned int> oVec) {
    double sum = 0;
    for (int i = 0; i < 3; ++i) {
        int diff = vec[i] - oVec[i];
        sum += pow(diff, 2.0);
    }
    return sqrt(sum);
}

struct hist {
    int clusterID;
    double minDist;
    vector<unsigned int> x;

    hist(int clusterID, double minDist, vector<unsigned int> x):
        clusterID(clusterID),
        minDist(minDist),
        x(move(x)) {}
};

int main() {
    // HISTOGRAMS
    vector<unsigned int> x1 = {1, 5, 7};
    vector<unsigned int> x2 = {9, 2, 1};
    vector<unsigned int> x3 = {5, 5, 1};
    vector<unsigned int> x4 = {0, 1, 3};
    vector<unsigned int> x5 = {9, 8, 6};
    vector<unsigned int> x6 = {2, 7, 1};

    // CENTROIDS
    vector<unsigned int> c0 = {1, 5, 7};
    vector<unsigned int> c1 = {2, 7, 1};
    vector<unsigned int> c2 = {9, 8, 6};

    vector<vector<unsigned int>> centroids;
    centroids.reserve(3);
    centroids.push_back(c0);
    centroids.push_back(c1);
    centroids.push_back(c2);

    vector<hist> hists; //  VECTOR OF HISTOGRAMS
    hists.reserve(6);
    hists.emplace_back(-1, __DBL_MAX__, x1);
    hists.emplace_back(-1, __DBL_MAX__, x2);
    hists.emplace_back(-1, __DBL_MAX__, x3);
    hists.emplace_back(-1, __DBL_MAX__, x4);
    hists.emplace_back(-1, __DBL_MAX__, x5);
    hists.emplace_back(-1, __DBL_MAX__, x6);

    // BEGIN OF K-MEANS
    for (int l = 0; l < 10 ; ++l) {
        for (auto& hist : hists) {
            for (int i = 0; i < centroids.size(); ++i) {
                double dist = vecDistance(hist.x, centroids[i]);
                if (dist < hist.minDist) {
                    hist.minDist = dist;
                    hist.clusterID = i;
                }
            }
        }

        vector<vector<unsigned int>> newCentroids;
        newCentroids.reserve(3);
        vector<unsigned int> newCentroid;
        newCentroid.reserve(3);
        vector<int> noCentroids;
        noCentroids.reserve(3);
        for (int m = 0; m < 3; ++m) {
            newCentroid.push_back(0);
        }
        for (int n = 0; n < 3; ++n) {
            newCentroids.push_back(newCentroid);
        }
        for (int i1 = 0; i1 < 3; ++i1) {
            noCentroids.push_back(0);
        }

        // SUMMING UP CENTROIDS
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

        // GETTING MEAN OF CENTROIDS
        for (auto& nCentroid : newCentroids) {
            for (int i = 0; i < nCentroid.size(); ++i) {
                nCentroid[i] /= noCentroids[i];
            }
        }

        // UPDATING CENTROIDS
        for (int k = 0; k < newCentroids.size(); ++k) {
            centroids[k] = newCentroids[k];
        }

        for (int i = 0; i < centroids.size(); ++i) {
            printVector("after. centroid" + to_string(i), &centroids[i]);
        }
    }

    return 0;
}

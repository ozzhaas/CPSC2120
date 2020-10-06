#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;




void cross(vector<pair<double, double> >vec, int n) {
    int p = 0;

    for (unsigned int i = 0; i < vec.size(); i++) {
        for (unsigned int j = 0; j < vec.size(); j++) {
            if ((vec[j].second < vec[i].first) && (vec[i].first < vec[j].first) && (vec[j].first < vec[i].second)) {
                p++;
            }
            else if ((vec[j].second < vec[i].second) && (vec[i].second < vec[j].first) && (vec[j].first < vec[i].first)) {
                p++;
            }
            else if ((vec[j].first < vec[i].first) && (vec[i].first < vec[j].second) && (vec[j].second < vec[i].second)) {
                p++;
            }
            else if ((vec[j].first < vec[i].second) && (vec[i].second < vec[j].second) && (vec[j].second < vec[i].first)) {
                p++;
            }
            else {
                //do nothing
            }
        }
    }

    cout << "P = " << p << endl;
    cout << "Number of pieces = " << n + 1 + p << endl;

}



void readInput(ifstream& input) {
    int N = 0;
    pair<double, double> interval;
    input.open("cuts.txt");
    vector<pair<double, double> > vec;

    string tmp1, tmp2 = "";
    double point1, point2 = 0.0;

    while (input >> tmp1) {
        input >> tmp2;
        point1 = stod(tmp1);
        point2 = stod(tmp2);
        interval = make_pair(point1, point2);
        vec.push_back(interval);
        N++;
    }
    cross(vec, N);
}




int main (void) {
    ifstream input;

    readInput(input);

    input.close();


    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

long  string_to_number (string &word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

int main() {
    long long res = 1;

    ifstream file("input.txt");

    map <long, long> data;

    //store times and distance
    string line, line2, time, distance;
    getline(file, line); getline(file, line2);

    istringstream times(line); istringstream distances(line2);

    times >> time; distances >> distance;

    while(times >> time && distances >> distance) {
        data.insert({string_to_number(time), string_to_number(distance)});
    }

    for (auto d : data) {
        //calculate number of ways to beat the record
        int ways = 0;
        for (long i = 1; i < d.first; i++) {
            if (i * (d.first -i) > d.second) ways ++;
        }
        res *= ways;
    }

    cout << res << endl;

    return 0;
}
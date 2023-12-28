#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

long long string_to_number (string &word) {
    char* output;
    return strtoll(word.c_str(), &output, 10);
}

int main() {
    long long res = 0;

    ifstream file("input.txt");

    string line, line2, time, distance, final_time, final_distance;
    getline(file, line); getline(file, line2);

    istringstream times(line); istringstream distances(line2);

    times >> time; distances >> distance;

    while(times >> time && distances >> distance) {
        final_time.append(time);
        final_distance.append(distance);
    }

    //get time and distance
    long long time_val = string_to_number(final_time);
    long long distance_val = string_to_number(final_distance);

    for (long long i = 1; i < time_val; i++) {
        if (i * (time_val - i) > distance_val) res ++;
    }

    cout << res << endl;

    return 0;
}
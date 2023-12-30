#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define expansion 1000000

//global variables
vector<string> image;

struct location {
    int x; int y;
};

long real_x (int x) {
    //calculate number of empty rows before actual row x
    int empty_rows_before = 0;

    for (int i = 0; i < x; i++) {
        if (all_of(image[i].begin(), image[i].end(), [](char c)  { return c == '.'; }) ) {
            empty_rows_before ++;
        }
    }

    return (x + (expansion -1)*empty_rows_before); 
}

long real_y (int y) {
    //calculate number of empty columns before actual column y
    int empty_columns_before = 0;

    for (int j = 0; j < y; j++) {
        if (all_of (image.begin(), image.end(), [j](string &s) { return s[j] == '.';})) {
            empty_columns_before ++;
        }
    }

    return (y + (expansion-1)*empty_columns_before);
}

int main () {
    long long res = 0;

    ifstream file("input.txt");
    string line;
    
    //save image
    image.clear();

    while ( getline(file, line) ) {
        image.push_back(line);
    }

    //save location of each galaxy
    vector<location> galaxy;

    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            if (image[i][j] == '#') galaxy.push_back( { real_x(i), real_y(j) });
        }
    }

    //calculate distance for all pair of galaxy
    int galaxies = galaxy.size();

    for (int i = 0; i < galaxies; i ++) {
        for (int j = i+1; j < galaxies; j ++) {
            long x_variation = abs(galaxy[i].x - galaxy[j].x); 
            long y_variation = abs(galaxy[i].y - galaxy[j].y); 

            res += (x_variation + y_variation);
        }
    }

    cout << res << endl;

    return 0;
}
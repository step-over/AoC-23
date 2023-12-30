#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct location {
    int x; int y;
};

int main () {
    long res = 0;

    ifstream file("input.txt");
    string line;
    
    //save image with row expanded
    vector<string> image;

    while ( getline(file, line) ) {
        image.push_back(line);

        if (all_of(line.begin(), line.end(), [](char c)  { return c == '.'; }) ) {
            image.push_back(line); //expand row
        }
    }

    //expand image by column 
    for (int i = 0; i < image[0].size(); i++) {

        if (all_of (image.begin(), image.end(), [i](string &s) { return s[i] == '.';})) {

            for_each(image.begin(), image.end(), [i] (string &s) { s = s.replace(i, 1, ".."); });
            i++;
        }
    }

    //save location of each galaxy
    vector<location> galaxy;

    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            if (image[i][j] == '#') galaxy.push_back({i, j});
        }
    }

    //calculate distance for all pair of galaxy
    int galaxies = galaxy.size();

    for (int i = 0; i < galaxies; i ++) {
        for (int j = i+1; j < galaxies; j ++) {
            int x_variation = abs(galaxy[i].x - galaxy[j].x); 
            int y_variation = abs(galaxy[i].y - galaxy[j].y); 

            res += (x_variation + y_variation);
        }
    }

    cout << res << endl;

    return 0;
}
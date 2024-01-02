#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> vertical_pattern (vector<string> &pattern) {
    vector<string> res = vector<string>(pattern[0].size());

    for (int i = 0; i < pattern[0].size(); i++) {
        for_each(pattern.begin(), pattern.end(), [i, &res](string s) {
            res[i].push_back(s[i]);
        });
    }

    return res;
}

//returns sum of index of all horizontal reflections or 0 if there is not
int reflection (vector<string> &pattern) {
    int res = 0;

    //iterate through all adjacent rows in pattern
    for (auto it = adjacent_find(pattern.begin(), pattern.end()); it != pattern.end(); 
    it = adjacent_find(next(it,1), pattern.end()) ){
        bool reflection = true;

        //check if all the remaining rows match
        for (auto [it_beg, it_end] = tuple{reverse_iterator(it), next(it,2) }; 
        it_beg != pattern.rend() && it_end != pattern.end(); it_beg ++, it_end ++) {
            reflection &= (*it_beg == *it_end);
        }

        if (reflection) res += distance(pattern.begin(), it) +1;
    }

    return res;
}


int main() {
    long res = 0;
    
    fstream file("input.txt");
    string line;

    vector<string> pattern;

    while ( getline(file, line) ) {
        if (line != "") {
            pattern.push_back(line);
        } else {
            //calculate horizontal and vertical reflection of actual pattern
            long horizontal = reflection(pattern)*100;
            
            vector<string> vertical_pat = vertical_pattern(pattern);
            long vertical = reflection(vertical_pat);
            
            res += (vertical + horizontal);

            pattern.clear();
        }
    }

    cout << res << endl;

    return 0;
}
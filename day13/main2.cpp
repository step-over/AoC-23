#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

//global variables
bool smudge_found;

struct coord { int x; int y; };

//get vector of columns of pattern
vector<string> vertical_pattern (vector<string> &pattern) {
    vector<string> res = vector<string>(pattern[0].size());

    for (int i = 0; i < pattern[0].size(); i++) {
        for_each(pattern.begin(), pattern.end(), [i, &res](string s) { 
            res[i].push_back(s[i]); });
    }

    return res;
}

bool differ_at_one (string &s, string &s2) {
    auto it = mismatch(s.begin(), s.end(), s2.begin());
    auto it2 = mismatch(next(it.first,1), s.end(), next(it.second,1));

    smudge_found = (it.first != s.end() && it2.first == s.end());
    return smudge_found;
}

bool equal_or_differ_at_one (string &s, string &s2) { 
    if (smudge_found) return s == s2;
    else return s == s2 || differ_at_one(s,s2);
}

//returns index of all new horizontal reflection lines
vector<int> reflection (vector<string> &pattern, vector<int> diff) {
    vector<int> res;

    //iterate through all adjacent rows in pattern
    for (auto it = adjacent_find(pattern.begin(), pattern.end()); it != pattern.end(); 
    it = adjacent_find(next(it,1), pattern.end()) ){
        bool reflection = true;

        //check if all the remaining rows match
        for (auto [it_beg, it_end] = tuple{reverse_iterator(it), next(it,2) }; 
        it_beg != pattern.rend() && it_end != pattern.end(); it_beg ++, it_end ++) {
            reflection &= (*it_beg == *it_end);
        }

        int horizontal = distance(pattern.begin(), it) +1;

        if (reflection && find(diff.begin(), diff.end(), horizontal) == diff.end()) {
            res.push_back(horizontal); //new horizontal reflection line
        } 
    }

    return res;
}

coord coordinates_mismatch (vector<string> &pattern, vector<string>::iterator it, int dist) {
    int x = distance(pattern.begin(), it)-dist;

    auto it2 = mismatch(pattern[x].begin(), pattern[x].end(), pattern[x+dist].begin());

    int y = distance(pattern[x].begin(), it2.first);

    return {x, y};
}

coord find_smudge (vector<string> &pattern) {
    
    //iterate through all adjacent rows in pattern or rows that differ in only one char
    for (auto it = adjacent_find(pattern.begin(), pattern.end(), equal_or_differ_at_one); it != pattern.end(); 
    it = adjacent_find(next(it,1), pattern.end(), equal_or_differ_at_one) ){
        bool reflection = true;
        coord res = {-1, -1};

        if (smudge_found && res.x == -1) res = coordinates_mismatch(pattern, next(it,1), 1);

        //check if all the remaining rows match or differ in only one char
        for (auto [it_beg, it_end, i] = tuple{reverse_iterator(it), next(it,2), 3}; 
        it_beg != pattern.rend() && it_end != pattern.end(); it_beg ++, it_end ++, i+=2) {
            reflection &= equal_or_differ_at_one(*it_beg, *it_end);

            if (smudge_found && res.x == -1) res = coordinates_mismatch(pattern, it_end, i);
        }

        if (reflection && smudge_found) return res;
        else smudge_found = false;
    }

    return {-1, -1};
}

void fix_smudge (vector<string> &pattern) {
    smudge_found = false;

    coord smudge_hor = find_smudge(pattern);
    bool horizontal = smudge_found;

    //horizontal smudge
    if (horizontal) {
        pattern[smudge_hor.x][smudge_hor.y] = (pattern[smudge_hor.x][smudge_hor.y] == '.') ? '#' : '.';
    }

    vector<string> vert_pattern = vertical_pattern(pattern);

    coord smudge_ver = find_smudge(vert_pattern);

    //vertical smudge
    if (! horizontal) {
        pattern[smudge_ver.y][smudge_ver.x] = (pattern[smudge_ver.y][smudge_ver.x] == '.') ? '#' : '.';
    }
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
            //save original horizontal and vertical reflection line
            vector<int> hor_or = reflection(pattern, {});
            
            vector<string> vertical_pat = vertical_pattern(pattern);
            vector<int> vert_or = reflection(vertical_pat, {});

            fix_smudge(pattern);

            //calculate new reflection line
            vector<int> horiz = reflection(pattern, hor_or);
            
            vertical_pat = vertical_pattern(pattern);
            vector<int> vert = reflection(vertical_pat, vert_or);

            int horizontal_value = accumulate(horiz.begin(), horiz.end(), 0);
            int vertical_value = accumulate(vert.begin(), vert.end(), 0);

            res += (vertical_value + horizontal_value*100);

            pattern.clear();
        }
    }

    cout << res << endl;

    return 0;
}
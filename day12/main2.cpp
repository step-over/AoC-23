#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

//global variables
vector<vector<long long>> memo;

struct spring {
    string record;
    vector<long> damaged;
};

long string_to_number (string &word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

vector<long> repeat(vector<long> orig, int amount) {
    vector<long> res(orig.size()*amount);

    auto it = res.begin();

    for (int i = 0; i < amount; i++) {
        it = copy(orig.begin(), orig.end(), it);
    }

    return res; 
}

//implemented with DP 
long long arrangements (string & rec, vector<long> &dam, int pos, int dam_pos) {
    if (pos >= rec.size()) {
        return dam_pos == dam.size();
    } else {
        if (memo[pos][dam_pos] != -1) return memo[pos][dam_pos];

        long long res = 0;

        string rest = rec.substr(pos);

        //if there can't be more groups of '#', the rest of the string has to be '?' or '.'
        if (dam_pos >= dam.size()) res += all_of(rest.begin(), rest.end(), [](char &c) { return c != '#' ;});

        else {if (rec[pos] == '.') {res += arrangements(rec, dam, pos+1, dam_pos); //not allocating in pos
        } else {
            string group = rec.substr(pos, dam[dam_pos]);

            if (all_of(group.begin(), group.end(), [](char c) {return c != '.';}) 
            && pos + dam[dam_pos] -1 < rec.size() 
            && (pos + dam[dam_pos] >= rec.size() || rec[pos + dam[dam_pos]] != '#')) {
                //it is valid to allocate next group of '#' since pos 
                res += arrangements(rec, dam, pos + dam[dam_pos] +1, dam_pos +1); 
            }

            if (rec[pos] == '?') res += arrangements(rec, dam, pos +1, dam_pos); //not allocating in pos
        }}

        memo[pos][dam_pos] = res;

        return res;
    }
}

int main () {
    long long res = 0;

    ifstream file("input.txt");
    string line;

    //save each record and its contiguous group of damaged springs
    vector<spring> springs;

    while ( getline(file, line) ) {
        istringstream record(line);
        string spr, dam, original;

        record >> spr; //save record

        vector<long> damaged;

        //save numbers (separated by ,)
        while (getline(record, dam, ',')) {
            damaged.push_back(string_to_number(dam));
        }

        //unfold the records
        original = spr;
        for (int i = 0; i < 4; i++) {
            spr += '?';
            spr += original;
        }

        damaged = repeat(damaged, 5);

        springs.push_back( {spr, damaged}) ;
    }

    //calculate arrangements por each spring
    for (spring s : springs ) {
        memo = vector<vector<long long>>(s.record.size(), vector<long long>(s.damaged.size()+1,-1));
        res += arrangements(s.record, s.damaged, 0, 0);
    }

    cout << res << endl;

    return 0;
}
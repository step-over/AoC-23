#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct spring {
    string record;
    vector<long> damaged;
};

long string_to_number (string &word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

bool valid_arrang (string &rec, vector<long> &dam, long pos) {
    bool valid = true;
    int it = 0;

    for (int i = rec.find('#'); i < pos && i != rec.npos; 
    i = rec.find('#', rec.find_first_not_of('#', i))) {
        int end = (rec.find_first_not_of('#', i) == rec.npos) ? rec.size() : rec.find_first_not_of('#', i);
        
        if (end > pos) continue;

        if (it > dam.size()) return false;

        valid &= (end - i == dam[it]); 

        it ++;
    }

    return valid && (pos < rec.size() || it == dam.size());
}

long arrangements (string & rec, vector<long> &dam, int changed, int pos) {
    if (pos == rec.npos) {
        return valid_arrang(rec, dam, rec.size());
    } else {
        if (! valid_arrang(rec, dam, changed)) return 0;

        int next_unknown = rec.find('?', pos+1);
        long res = 0;
        
        //operational
        rec[pos] = '.';
        res += arrangements(rec, dam, pos, next_unknown);

        //broken
        rec[pos] = '#';
        res += arrangements(rec, dam, pos, next_unknown);

        rec[pos] = '?';

        return res;
    }
}

int main () {
    long res = 0;

    ifstream file("input.txt");
    string line;

    //save each record and its contiguous group of damaged springs
    vector<spring> springs;

    while ( getline(file, line) ) {
        istringstream record(line);
        string spr, dam;

        record >> spr; //save record

        vector<long> damaged;

        //save numbers (separated by ,)
        while (getline(record, dam, ',')) {
            damaged.push_back(string_to_number(dam));
        }

        springs.push_back( {spr, damaged}) ;
    }

    //calculate arrangements por each spring
    for (spring s : springs) {
        res += arrangements(s.record, s.damaged , 0, s.record.find('?'));
    }

    cout << res << endl;

    return 0;
}
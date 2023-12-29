#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

long string_to_number (string &word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

int main(){
    long res = 0;

    ifstream file("input.txt");
    string line;
    
    while(getline(file, line)) {
        istringstream history_line(line);
        string number;
        vector<long> history;

        //save each number of history
        while (history_line >> number){
            history.push_back(string_to_number(number));
        }

        long next_value = history.back(); //save last digit of history

        //calculate difference of each number until is all zeroes
        while (! all_of(history.begin(), history.end(), [](long &l) { return l == 0 ;} )){

            for (int i = 0; i < history.size() -1; i++) {
                history[i] = (history[i+1] - history[i]); 
            }
            history.pop_back(); 
            next_value += history.back();
        } 

        res += next_value;
    }

    cout << res << endl;

    return 0;
}
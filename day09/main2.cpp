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

        long next_value = history.front(); //save first digit of history
        int factor = -1;

        //calculate difference of each number until is all zeroes
        //next value can be calculated adding alternated the first number of every difference
        //next value = history1.front - history2.front + history3.front - history4.front + ...

        while (! all_of(history.begin(), history.end(), [](long &l) { return l == 0 ;} )){

            for (int i = 0; i < history.size() -1; i++) {
                history[i] = (history[i+1] - history[i]); 
            }
            
            history.pop_back(); 
            next_value += history.front() * factor;
            factor *= (-1);
        }

        res += next_value;
    }

    cout << res << endl;

    return 0;
}
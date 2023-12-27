#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long string_to_number (string word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

int size_of_intersection (vector<long> &v, vector<long> &v2){
    sort(v.begin(), v.end());
    sort(v2.begin(), v2.end());

    vector<long> intersection;

    set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), back_inserter(intersection));

    return intersection.size();
}

int number_lines (ifstream &file, string line) {
    int lines = 0;

    while (getline(file,line)) lines++;

    file.clear(); //to return to beginning of file
    file.seekg(0);

    return lines;
}

int main(){
    long res = 0;

    ifstream file("input.txt");

    string line;

    vector<int> number_cards(number_lines(file,line), 1);
    int actual_card = 0;
    
    while(getline(file, line)) {
        //to read line word by word
        istringstream card(line);
        string word;

        bool reading_winning = true;

        vector<long> winning_numbers, my_numbers;
    
        while (card >> word) {
            if (word == "|") reading_winning = false;

            //if actual word isn't a digit continues to next word
            if (! isdigit(word.back())) continue;

            //save actual word as number
            if (reading_winning) winning_numbers.push_back(string_to_number(word));

            else my_numbers.push_back(string_to_number(word));
        }

        //calculate amount of elements in common between my_numbers and winning_numbers
        int matching_numbers = size_of_intersection(my_numbers, winning_numbers);

        //copies won by points
        for (int i = 1; i <= matching_numbers; i++) {
            //you win one card for each copy of actual card
            number_cards[actual_card + i] += number_cards[actual_card];
        }

        res += number_cards[actual_card];

        actual_card ++;

        //clean vectors
        my_numbers.clear(); winning_numbers.clear();
    }

    cout << res << endl;

    return 0;
}
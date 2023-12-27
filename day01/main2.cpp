#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int find_minimum_index(vector<size_t> digit, string line){  //return index of min
    int min = -1; 
    for (int i = 0; i <= 9; i++){
        if (min == -1 || digit[i] < digit[min])
            min = i;
    }
    return min;
}

int find_maximum_index(vector<size_t> digit, string line){  //return index of max
    int max = -1 ; 
    for (int i = 0; i <= 9; i++){
        if (digit[i] <= line.size() && (max == -1 || digit[i] > digit[max]))
            max = i;
    }
    return max;
}

char index_to_char(vector<size_t> digit, int index, string line){
    if (index == 0) return line[digit[index]];
    if (index == 1) return '1';
    if (index == 2) return '2';
    if (index == 3) return '3';
    if (index == 4) return '4';
    if (index == 5) return '5';
    if (index == 6) return '6';
    if (index == 7) return '7';
    if (index == 8) return '8';
    if (index == 9) return '9';
}

int main() {
    long sum = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while(getline(file,line)){

            //find first digit in line
            size_t pos_first = line.find_first_of("123456789");

            vector<size_t> find_first = {
                pos_first, line.find("one"), line.find("two"), line.find("three"), line.find("four"), line.find("five"),
                line.find("six"), line.find("seven"), line.find("eight"), line.find("nine")
            };

            //keep the char that appears first
            int first_index = find_minimum_index(find_first, line);

            char first = index_to_char(find_first, first_index, line);

            //find last digit in line
            size_t pos_second = line.find_last_of("123456789");

            vector<size_t> find_second = {
                pos_second, line.rfind("one"), line.rfind("two"), line.rfind("three"), line.rfind("four"), line.rfind("five"),
                line.rfind("six"), line.rfind("seven"), line.rfind("eight"), line.rfind("nine")
            };

            //keep the char that appears first
            int second_index = find_maximum_index(find_second, line);

            char second = index_to_char(find_second, second_index, line);

            char dig[3] = {first,second, 0};
            char* output;
            long digit = strtol(dig, &output,10);
            sum += digit;
        }

        file.close();
    }

    cout << sum << endl;

    return 0;
}
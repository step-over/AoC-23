#include <iostream>
#include <fstream>
#include <string>
#include "cstdlib"
#include <algorithm>
#include <vector>

using namespace std;

char find_minimum(vector<size_t> digit, string line){
    int min = -1; 
    for (int i = 0; i <= 9; i++){
        if (min == -1 || digit[i] < digit[min])
            min = i;
    }
    if (min == 0) return line[digit[min]];
    if (min == 1) return '1';
    if (min == 2) return '2';
    if (min == 3) return '3';
    if (min == 4) return '4';
    if (min == 5) return '5';
    if (min == 6) return '6';
    if (min == 7) return '7';
    if (min == 8) return '8';
    if (min == 9) return '9';
}

char find_maximum(vector<size_t> digit, string line){
    int max = -1 ; 
    for (int i = 0; i <= 9; i++){
        if (digit[i] <= line.size() && (max == -1 || digit[i] > digit[max]))
            max = i;
    }
    if (max == 0) return line[digit[max]]; //digit
    if (max == 1) return '1';
    if (max == 2) return '2';
    if (max == 3) return '3';
    if (max == 4) return '4';
    if (max == 5) return '5';
    if (max == 6) return '6';
    if (max == 7) return '7';
    if (max == 8) return '8';
    if (max == 9) return '9';
}

int main() {
    long sum = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while(getline(file,line)){

            //find first ocurrence
            size_t pos_digit = line.find_first_of("123456789");

            //updated version for second part
            size_t one = line.find("one");
            size_t two = line.find("two");
            size_t three = line.find("three");
            size_t four = line.find("four");
            size_t five = line.find("five");
            size_t six = line.find("six");
            size_t seven = line.find("seven");
            size_t eight = line.find("eight");
            size_t nine = line.find("nine");

            vector<size_t> find = {pos_digit, one, two, three, four, five, six, seven, eight, nine};

            //keep only the first apeareance
            char first = find_minimum(find, line);

            //find second ocurrence
            size_t second_pos_dig = line.find_last_of("123456789");

            one = line.rfind("one");
            two = line.rfind("two");
            three = line.rfind("three");
            four = line.rfind("four");
            five = line.rfind("five");
            six = line.rfind("six");
            seven = line.rfind("seven");
            eight = line.rfind("eight");
            nine = line.rfind("nine");

            vector<size_t> find_second = {second_pos_dig, one, two, three, four, five, six, seven, eight, nine};

            char second = find_maximum(find_second, line);

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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long find_number(string line, size_t pos){
    size_t beg = line.find_last_not_of("1234567890", pos)+1;
    size_t end = line.find_first_not_of("1234567890", pos)-1;

    string number = line.substr(beg,end-beg+1);

    char* output;
    return strtol(number.c_str(), &output, 10);
}

int main(){
    long res = 0;

    ifstream file("input.txt"), file2("input.txt");
    string line, next_line, prev_line;

    //count number of lines
    int lines = 0;
    while(getline(file,line)) lines++;

    file.clear(); //to return to beginning of the file
    file.seekg(0);

    int actual_line = 0;

    getline(file2, next_line); //to get next line

    while(getline(file, line)){
        if (actual_line != lines) getline(file2, next_line);

        //find ocurrences of *
        for(size_t star = line.find("*"); star != line.npos; star = line.find("*", star+1)){
            vector<long> numbers_adjacents;

            //find number adjacent at left
            if (star != 0 && isdigit(line[star-1])){ // d * ?
                numbers_adjacents.push_back(find_number(line, star-1));
            }

            //find number adjacent at right
            if (star <= line.length()-2 && isdigit(line[star+1])){  // ? * d
                numbers_adjacents.push_back(find_number(line, star+1));
            }

            //find numbers adjacents in the upper line
            if (actual_line != 0){

                if (isdigit(prev_line[star-1]) && isdigit(prev_line[star]) && isdigit(prev_line[star+1])){ // d d d
                    numbers_adjacents.push_back(find_number(prev_line, star+1));                           // ? * ?

                } else { if (! isdigit(prev_line[star])) {
                    if (isdigit(prev_line[star-1])) {                                  //d . ?
                        numbers_adjacents.push_back(find_number(prev_line, star-1));   //? * ?
                    }
                    if (isdigit(prev_line[star+1])) {                                  //? . d
                        numbers_adjacents.push_back(find_number(prev_line, star+1));   //? * ?
                    }   
                } else {                                                        //? d ?
                    numbers_adjacents.push_back(find_number(prev_line, star));  //? * ?
            }}}

            //find number adjacents in the next line
            if (actual_line != lines){

                if (isdigit(next_line[star-1]) && isdigit(next_line[star]) && isdigit(next_line[star+1])){ // ? * ?
                    numbers_adjacents.push_back(find_number(next_line, star+1));                           // d d d

                } else { if (! isdigit(next_line[star])) {
                    if (isdigit(next_line[star-1])) {                                  //? * ?
                        numbers_adjacents.push_back(find_number(next_line, star-1));   //d . ?
                    }
                    if (isdigit(next_line[star+1])) {                                  //? * ?
                        numbers_adjacents.push_back(find_number(next_line, star+1));   //? . d
                    }   
                } else {                                                        //? * ?
                    numbers_adjacents.push_back(find_number(next_line, star));  //? d ?
            }}}

            //check * is a gear
            if (numbers_adjacents.size() == 2){
                res += (numbers_adjacents[0] * numbers_adjacents[1]);
            }
        }

        actual_line ++;
        prev_line = line;
        
    }

    file.close();

    cout << res << endl;

    return 0;
}
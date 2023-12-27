#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool contain_symbol(string data){
    bool res = false;
    for(char c : data){
        res |= (!isdigit(c) && c != '.');
    }
    return res;
}


int main(){
    long res = 0;

    ifstream file("input.txt");
    ifstream file2("input.txt");

    if (file.is_open()){
        string line;

        //count number of lines
        int lines = 0;
        while(getline(file,line)) lines++;

        int actual_line = 0;

        file.clear(); //to return to beginning of the file
        file.seekg(0);

        string prev_line;

        string next_line; 
        getline(file2, next_line);

        while(getline(file,line)){
            if (actual_line != lines) getline(file2,next_line);

            //find ocurrences of digits in actual line
            for(size_t digit = line.find_first_of("123456789"); 
            digit != line.npos; 
            digit = line.find_first_of("123456789", line.find_first_not_of("0123456789", digit))){
                size_t digit_end = line.find_first_not_of("0123456789", digit);

                //check if there is a symbol at left
                bool symbol_left = (digit != 0) ? contain_symbol(line.substr(digit-1,1)) : false;
                
                //check if there is a symbol at right
                bool symbol_right = (digit_end <= line.length()-1) ? contain_symbol(line.substr(digit_end, 1)) : false;

                //check if there is a symbol in the upper line 
                bool symbol_up = false;

                if(actual_line != 0){
                    //also checks if there is a symbol in the two diagonals
                    string up;

                    //only works because line is wider than the up substring
                    if (digit != 0 && digit_end <= line.length()-1) up = prev_line.substr(digit-1, digit_end -digit +2); 
                    
                    else {if (digit == 0) up = prev_line.substr(digit, digit_end-digit +1);
                    
                    else up = prev_line.substr(digit-1, digit_end - digit+1); }

                    symbol_up = contain_symbol(up);
                }

                //check if there is a symbol in the next line
                bool symbol_down = false;

                if(actual_line != lines){
                    //also checks if there is a symbol in the two diagonals
                    string down;

                    //only works because line is wider than the down substring
                    if (digit != 0 && digit_end <= line.length()-1) down = next_line.substr(digit-1, digit_end -digit +2); 
                    
                    else {if (digit == 0) down = next_line.substr(digit, digit_end-digit +1);

                    else down = next_line.substr(digit-1, digit_end - digit+1); }

                    symbol_down = contain_symbol(down);
                }

                if (symbol_down || symbol_left || symbol_right || symbol_up){
                    string number = line.substr(digit, digit_end-digit);

                    char* output;
                    long digit = strtol(number.c_str(), &output, 10);

                    res += digit;
                }
            }

            prev_line = line;
            actual_line ++;
        }

        file.close();
    }

    cout << res << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include "cstdlib"
#include <vector>

using namespace std;

int main() {
    long sum = 0;

    ifstream file("input.txt");

    vector<pair<char,string>> letters = {{'1',"one"},{'2',"two"}, {'3',"three"}, {'4',"four"}, {'5',"five"}, {'6',"six"}, {'7',"seven"}, {'8',"eight"}, {'9',"nine"}};

    if (file.is_open()){
        string line;
        while(getline(file,line)){
            char first, second;
            first = -1;
            int pos = 0;
            for(auto c : line){
                bool esta = false;
                if (isdigit(c)){
                    first = (first == -1) ? c : first;
                    second = c;
                } else {
                    for (int i = 0; i < 9 && ! esta; i++){
                        if (pos < letters[i].second.length()){
                            for (int j = 0; j < pos; j++ ){
                            }
                            pos ++;
                            esta = true;
                            if (pos == letters[i].second.length()){
                                first = (first == -1) ? letters[i].first : first;
                                second = letters[i].first;
                                esta = false;
                                break;
                            }
                        }
                    }
                    if (! esta) pos = 0;
                }
            }

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
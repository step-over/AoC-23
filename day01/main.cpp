#include <iostream>
#include <fstream>
#include <string>
#include "cstdlib"

using namespace std;

int main() {
    long sum = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while(getline(file,line)){
            char first, second;
            first = -1;
            for(auto c : line){
                if (isdigit(c)){
                    first = (first == -1) ? c : first;
                    second = c;
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

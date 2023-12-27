#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    long sum = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while(getline(file,line)){
            //find first digit in line
            size_t pos_first = line.find_first_of("123456789");
    
            //find last digit in line
            size_t pos_second = line.find_last_of("123456789");

            char dig[3] = {line[pos_first],line[pos_second], 0};
            char* output;
            long digit = strtol(dig, &output,10);
            
            sum += digit;
        }

        file.close();
    }

    cout << sum << endl;

    return 0;
}
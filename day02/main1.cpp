#include <iostream>
#include <fstream>
#include <string>

using namespace std;

long find_digit(size_t pos, string line, char c){ //return digit after char
    size_t begin = line.rfind(c, pos);
    size_t end = line.find(c,pos);

    string number = line.substr(begin, end-begin);

    char* output;
    return strtol(number.c_str(),&output, 10);
}

int main(){
    long res = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while (getline(file,line)){

            //check if red is impossible
            bool possible_red = true;

            for (size_t red = line.find("red"); red != line.npos; red = line.find("red", red+1)) {
                long digit = find_digit(red-2, line, ' ');

                possible_red &= (digit <= 12);
            }

            //check if green is impossible
            bool possible_green = true;

            for (size_t green = line.find("green"); green != line.npos; green = line.find("green", green+1)) {
                long digit = find_digit(green-2, line, ' ');

                possible_green &= (digit <=13);
            }

            //check if blue is impossible
            bool possible_blue = true;

            for (size_t blue = line.find("blue"); blue != line.npos; blue = line.find("blue", blue+1)) {
                long digit = find_digit(blue-2, line, ' ');

                possible_blue &= (digit <=14);
            }

            if (possible_blue && possible_green && possible_red) {
                //get id of game
                size_t id_end = line.find(':', 5);

                string number = line.substr(4, id_end-4);

                char* output;
                long id = strtol(number.c_str(), &output, 10);

                res += id;
            }
        }
    
        file.close();
    }

    cout << res << endl;

    return 0;
}
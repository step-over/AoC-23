#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    long res = 0;

    ifstream file("input.txt");

    if (file.is_open()){
        string line;
        while (getline(file,line)){

            //check if red is impossible
            bool possible_red = true;

            for (size_t red = line.find("red"); red != line.npos; red = line.find("red", red+1)) {
                size_t begin = line.rfind(' ', red-2);

                string number = line.substr(begin, red-begin);

                char* output;
                long digit = strtol(number.c_str(),&output, 10);

                if (digit >12) {
                    possible_red = false;
                    break;
                }
            }

            //check if green is impossible
            bool possible_green = true;

            for (size_t green = line.find("green"); green != line.npos; green = line.find("green", green+1)) {
                size_t begin = line.rfind(' ', green-2);

                string number = line.substr(begin, green-begin);

                char* output;
                long digit = strtol(number.c_str(),&output, 10);
                
                if (digit > 13) {
                    possible_green = false;
                    break;
                }
            }

            //check if blue is impossible
            bool possible_blue = true;

            for (size_t blue = line.find("blue"); blue != line.npos; blue = line.find("blue", blue+1)) {
                size_t begin = line.rfind(' ', blue-2);

                string number = line.substr(begin, blue-begin);

                char* output;
                long digit = strtol(number.c_str(),&output, 10);
                
                if (digit >14) {
                    possible_blue = false;
                    break;
                }
            }

            if (possible_blue && possible_green && possible_red) {
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
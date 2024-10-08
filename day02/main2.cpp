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

            //calculate fewest number of red cubes 
            long min_red = -1;

            for (size_t red = line.find("red"); red != line.npos; red = line.find("red", red+1)) {
                long red_amount = find_digit(red-2, line, ' ');

                if (min_red == -1 || red_amount > min_red) min_red = red_amount;
            }

            //calculate fewest number of green cubes 
            long min_green = -1;

            for (size_t green = line.find("green"); green != line.npos; green = line.find("green", green+1)) {
                long green_amount = find_digit(green-2, line, ' ');
                
                if (min_green == -1|| green_amount > min_green) min_green = green_amount;
            }

            //calculate fewest number of blue cubes 
            long min_blue = -1;

            for (size_t blue = line.find("blue"); blue != line.npos; blue = line.find("blue", blue+1)) {
                long blue_amount = find_digit(blue-2, line, ' ');
                
                if (min_blue == -1 || blue_amount > min_blue) min_blue = blue_amount;
            }

            res += (min_red * min_blue * min_green);
        }
    
        file.close();
    }

    cout << res << endl;

    return 0;
}
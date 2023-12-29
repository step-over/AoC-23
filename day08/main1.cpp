#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct node {
    string left;
    string right;
};

int main () {
    int res = 0;

    ifstream file("input.txt");
    string instruction, line;

    getline(file, instruction); //save left/right instruction

    getline(file, line); //ignore second line

    //save left/right of each node 
    map<string, node> dicc; 

    while(getline(file, line)) {
        dicc[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }

    //count steps required to reach ZZZ starting at AAA
    string actual = "AAA";
    int i = 0;

    while (actual != "ZZZ"){
        i = (i == instruction.size()) ? 0 : i;

        actual = (instruction[i] == 'R') ? dicc[actual].right : dicc[actual].left;
        
        i++;
        res ++;
    }

    cout << res << endl;

    return 0;
}
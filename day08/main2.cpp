#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct node {
    string left;
    string right;
};

int main () {
    long long res = 1;

    ifstream file("input.txt");
    string instruction, line;

    getline(file, instruction); //save left/right instruction

    getline(file, line); //ignore second line

    //save left/right of each node 
    map<string, node> dicc; 
    vector<string> actual; 

    while(getline(file, line)) {
        dicc[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};

        //save al nodes that end with A
        if (line[2] == 'A') actual.push_back(line.substr(0,3));
    }

    //the steps required to reach again a node that ends with Z repeats 
    //so it is enough to count the min steps required for each node and then the lcm of them
    
    int i = 0; long long step = 0;
    vector<long long> steps(actual.size()); //min number of steps for every starting node

    while (any_of(steps.begin(), steps.end(), [](long long &l){ return l == 0;} )) {
        i = (i == instruction.size()) ? 0 : i;

        for (int j = 0; j < actual.size(); j++){
            if (steps[j] != 0) continue; //to only save the min number of steps

            if (actual[j][2] == 'Z') steps[j] = step;
        }

        for_each(actual.begin(), actual.end(), [&instruction, &dicc, i](string &s)
        { s = (instruction[i] == 'R') ? dicc[s].right : dicc[s].left ;} );

        i++; step ++;
    }

    //calculate lcm of all steps
    for (long long l : steps){
        res = lcm(res, l);
    }

    cout << res << endl;

    return 0;
}
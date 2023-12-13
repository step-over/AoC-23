#include <iostream>
#include <fstream>
#include <string>
#include "cstdlib"
#include <vector>

using namespace std;

struct Trie {
    bool end = false;
    vector<Trie*> nodes = vector<Trie*>(127,nullptr);
    char key = ' ';
};

void insert(Trie* &trie, string word, char key){
    Trie* node = trie;
    for (auto c : word){
        if (node->nodes[c] == nullptr) node->nodes[c] = new Trie;
        node = node->nodes[c];
    }
    node->end = true;
    node->key = key;
}

int main() {
    long sum = 0;

    Trie* trie = new Trie;

    vector<string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<char> keys = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (int i = 0; i < 9; i++) {
        insert(trie,words[i],keys[i]);
    }

    ifstream file("input.txt");



     if (file.is_open()){
        string line;
        while(getline(file,line)){
            Trie* node = trie;
            char first, second;
            first = -1;
            for(auto c : line){
                if (isdigit(c)){
                    first = (first == -1) ? c : first;
                    second = c;
                } else {
                    node = node->nodes[c]; 
                    if (node != nullptr && node->end ){
                        first = (first == -1) ? node->key : first;
                        second = node->key;
                        node = trie;
                    }
                    if (node == nullptr) {
                        node = trie;
                    }
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


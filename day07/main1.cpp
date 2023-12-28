#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct card {
    string hand;
    int type;
    long bid;
};

long string_to_number (string &word) {
    char* output;
    return strtol(word.c_str(), &output, 10);
}

int calculate_type (string card_) {
    //count number of appearances of each label
    vector<int> app;

    for (char c : card_){
        app.push_back(count(card_.begin(), card_.end(), c));
    }

    if (all_of(app.begin(), app.end(), [](int i){ return i == 1;} )) return 0; //high card

    if (all_of(app.begin(), app.end(), [](int i){ return i == 2 || i == 1;} ) 
        && count(app.begin(), app.end(), 2) == 2) return 1; //one pair

    if (all_of(app.begin(), app.end(), [](int i){ return i == 2 || i == 1;} )) return 2; //two pair

    if (all_of(app.begin(), app.end(), [](int i){ return i == 3 || i == 1;} )) return 3; //three of a kind

    if (all_of(app.begin(), app.end(), [](int i){ return i == 3 || i == 2;} )) return 4; //full house

    if (all_of(app.begin(), app.end(), [](int i){ return i == 4 || i == 1;} )) return 5; //four of a kind

    if (all_of(app.begin(), app.end(), [](int i){ return i == 5;} )) return 6; //five of a kind
}

int strength(char c){
    if (c == '2') return 1;
    if (c == '3') return 2;
    if (c == '4') return 3;
    if (c == '5') return 4;
    if (c == '6') return 5;
    if (c == '7') return 6;
    if (c == '8') return 7;
    if (c == '9') return 8;
    if (c == 'T') return 9;
    if (c == 'J') return 10;
    if (c == 'Q') return 11;
    if (c == 'K') return 12;
    if (c == 'A') return 13;
}

bool is_weaker(string & s1, string & s2) {
    bool res;

    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[i]) continue; 

        res = (strength(s1[i]) < strength(s2[i]));
        break;
    }

    return res;
}

int main () {
    long res = 0;

    ifstream file("input.txt");
    string number1, number2;

    vector<card> cards;
    
    //save info of each card
    while (file >> number1) {
        file >> number2;
        
        cards.push_back({ number1, calculate_type(number1), string_to_number(number2)});
    }

    //sort cards by rank
    sort(cards.begin(), cards.end(), 
    [] (card &c1, card &c2) 
    { return c1.type < c2.type || (c1.type == c2.type && is_weaker(c1.hand,c2.hand));});    

    //calculate winning of each card
    for (int i = 0; i < cards.size(); i++) {
        res += (i+1) * cards[i].bid;
    }

    cout << res << endl;

    return 0;
}
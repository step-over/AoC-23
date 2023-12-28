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

string replace_char(char new_v, char old, string str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == old) str[i] = new_v; 
    }
    return str;
}

//return most repeated char in str different to dif
char most_repetead_char(string str, char dif) {
    int max_ocurrences = -1; 
    char res;

    for (char c : str){
        if (c == dif) continue;

        int ocurrences_actual = count(str.begin(), str.end(), c);

        if (ocurrences_actual > max_ocurrences) {
            res = c; max_ocurrences = ocurrences_actual;
        }
    }

    return res;
}

int calculate_type (string hand) {
    //replace J with one of the most repeated label
    hand = replace_char(most_repetead_char(hand, 'J'), 'J', hand);

    //count number of appearances of each label
    vector<int> app;

    for (char c : hand){
        app.push_back(count(hand.begin(), hand.end(), c));
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
    switch (c){
        case 'J': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'T': return 10;
        case 'Q': return 11;
        case 'K': return 12;
        case 'A': return 13;
    }
}

bool is_weaker(string & s1, string & s2) {
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[i]) continue; 

        return (strength(s1[i]) < strength(s2[i]));
    }
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
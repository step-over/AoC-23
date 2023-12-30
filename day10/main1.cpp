#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int i;
    int j;
};

//global variables
int n, m;
vector<string> board;

bool move_up (int i, int j) {
    return (i != 0 && (board[i-1][j] == '7' || board[i-1][j] == 'F' || board[i-1][j] == '|'));
}

bool move_down (int i, int j) {
    return (i != n && (board[i+1][j] == 'L' || board[i+1][j] == 'J' || board[i+1][j] == '|'));
}

bool move_left (int i, int j) {
    return (j != 0 && (board[i][j-1] == '-' || board[i][j-1] == 'L' || board[i][j-1] == 'F'));
}

bool move_right (int i, int j) {
    return (j != m && (board[i][j+1] == '-' || board[i][j+1] == 'J' || board[i][j+1] == '7'));
}

vector<node> adjacent (int i, int j){
    vector<node> res;
            
    if (board[i][j] == '|') {
        if (move_up(i,j)) res.push_back({i-1, j}); 
        if (move_down(i,j)) res.push_back({i+1, j});
    }

    if (board[i][j] == '-') {
        if (move_left(i,j)) res.push_back({i, j-1});
        if (move_right(i,j)) res.push_back({i, j+1});
    }

    if (board[i][j] == 'L') {
        if (move_up(i,j)) res.push_back({i-1, j}); 
        if (move_right(i,j)) res.push_back({i, j+1});
    }

    if (board[i][j] == 'J') {
        if (move_up(i,j)) res.push_back({i-1, j});
        if (move_left(i,j)) res.push_back({i, j-1});
    }

    if (board[i][j] == '7') {
        if (move_left(i,j)) res.push_back({i, j-1});
        if (move_down(i,j)) res.push_back({i+1, j});
    }

    if (board[i][j] == 'F') {
        if (move_right(i,j)) res.push_back({i, j+1});
        if (move_down(i,j)) res.push_back({i+1, j});
    }

    if (board[i][j] == 'S') {
        if (move_up(i,j)) res.push_back({i-1, j});
        if (move_down(i,j)) res.push_back({i+1, j});

        if (move_left(i,j)) res.push_back({i, j-1});
        if (move_right(i,j)) res.push_back({i, j+1});
    }

    return res;
}

int main(){
    long res = 0;

    ifstream file("input.txt");
    string line; 

    //save board and position of s
    node s;
    n = 0; 
    board.clear();

    while(getline(file, line)) {
        board.push_back(line);

        if (line.find('S') != line.npos) s = { n, (int)line.find('S') };

        n ++;
    }

    m = board[0].size();

    //calculate distance from s to all reachable node with bfs
    vector<vector<long>> distances = vector<vector<long>>(n, vector<long>(m));
    n--; m--;
    queue<node> nodes; 

    nodes.push(s);

    while (! nodes.empty()) {
        node actual = nodes.front();
        nodes.pop();

        vector<node> adj = adjacent(actual.i, actual.j);

        for (node neighbor : adj) {
            if (distances[neighbor.i][neighbor.j] != 0) continue;

            nodes.push(neighbor);
            distances[neighbor.i][neighbor.j] = distances[actual.i][actual.j] + 1;

            //save max distance
            if (distances[neighbor.i][neighbor.j] > res) res = distances[neighbor.i][neighbor.j];
        }
    }

    cout << res << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct node {
    int i;
    int j;
};

//global variables
int n, m;
vector<string> board;
vector<vector<bool>> loop;

bool move_up (int i, int j) {
    return (i != 0 && (board[i-1][j] == '7' || board[i-1][j] == 'F' || board[i-1][j] == '|'));
}

bool move_down (int i, int j) {
    return (i != n-1 && (board[i+1][j] == 'L' || board[i+1][j] == 'J' || board[i+1][j] == '|'));
}

bool move_left (int i, int j) {
    return (j != 0 && (board[i][j-1] == '-' || board[i][j-1] == 'L' || board[i][j-1] == 'F'));
}

bool move_right (int i, int j) {
    return (j != m-1 && (board[i][j+1] == '-' || board[i][j+1] == 'J' || board[i][j+1] == '7'));
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

bool is_odd (int i) { return i % 2 == 1 ; }

int count_intersections (int i, int from) {
    int res = 0;

    for (int j = from +1; j < m; j++) {
        if (! loop[i][j]) continue;

        if (board[i][j] != '-') res ++;

        if (board[i][j] == 'L') {
            string between = board[i].substr(j+1, board[i].find('7', j)-j-1);

            if (all_of (between.begin(), between.end(), [](char c) { return c == '-' ;} )) {
                board[i][board[i].find('7', j)] = '-'; //it's a diagonal, so it counts as one intersection
            }
        }

        if (board[i][j] == 'F') {
            string between = board[i].substr(j+1, board[i].find('J', j) -j-1);

            if (all_of (between.begin(), between.end(), [](char c) { return c == '-' ;} )) {
                board[i][board[i].find('J', j)] = '-'; //it's a diagonal, so it counts as one intersection
            }
        }
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

    //find all nodes in the loop
    loop = vector<vector<bool>>(n, vector<bool>(m));
    queue<node> nodes; 

    nodes.push(s);
    loop[s.i][s.j] = 1;

    while (! nodes.empty()) {
        node actual = nodes.front();
        nodes.pop();

        vector<node> adj = adjacent(actual.i, actual.j);

        for (node neighbor : adj) {
            if (loop[neighbor.i][neighbor.j] != 0) continue;

            nodes.push(neighbor);
            loop[neighbor.i][neighbor.j] = 1;
        }
    }

    //find all tiles enclosed by the loop using the ray casting algorithm
    //the ray casting algorithm check if a point lies in the interior of a polygon

    for (int i = 1; i < n-1; i++) {
        for (int j = 0; j < m-1; j++) {

            if (loop[i][j]) continue; //is in the loop

            //count number of intersections from point to end of polygon
            //if the number is odd the point is inside
            if (is_odd(count_intersections(i, j))) res ++;
        }
    }

    cout << res << endl;

    return 0;
}
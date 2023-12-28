#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

long long string_to_number (string word) {
    char* output;
    return strtoll(word.c_str(), &output, 10);
}

long long find_file (ifstream &file, string begin, string end, long long value) {
    file.clear(); 
    file.seekg(0);

    string line;

    bool begin_reached, end_reached = false;

    while (getline(file,line) && ! end_reached) {
        if (line == begin) begin_reached = true;
        if (line == end && begin_reached) end_reached = true;

        if (! begin_reached || line == begin) continue;

        //reached data block
        istringstream data(line);
        string dest, source, length;

        data >> dest;
        data >> source;
        data >> length;

        long long dest_range_start = string_to_number(dest);
        long long source_range_start = string_to_number(source);
        long long range_length = string_to_number(length);

        //value is mapped
        if (source_range_start <= value && value <= (source_range_start + range_length)){
            return dest_range_start + (value - source_range_start);
        } 
    }

    //value isn't mapped
    return value;
}

struct seed {
    long long number;
    long long soil;
    long long fertilizer;
    long long water;
    long long light;
    long long temperature;
    long long humidity;
    long long location;
};

int main(){
    long long res = -1;

    ifstream file("input.txt");
    string line;

    vector<seed> seeds;

    //save number of all seeds
    getline(file, line);

    istringstream line_seeds(line);
    string word;

    while (line_seeds >> word) {
        if (! isdigit (word.front()) ) continue;

        seeds.push_back({});
        seeds.back().number = string_to_number(word);
    }

    //get info of all seeds
    for (int i = 0; i < seeds.size(); i++) {
        seeds[i].soil = find_file(file, "seed-to-soil map:", "soil-to-fertilizer map:", seeds[i].number);
        seeds[i].fertilizer = find_file(file, "soil-to-fertilizer map:", "fertilizer-to-water map:", seeds[i].soil);
        seeds[i].water = find_file(file, "fertilizer-to-water map:", "water-to-light map:", seeds[i].fertilizer);
        seeds[i].light = find_file(file, "water-to-light map:", "light-to-temperature map:", seeds[i].water);
        seeds[i].temperature = find_file(file, "light-to-temperature map:", "temperature-to-humidity map:", seeds[i].light);
        seeds[i].humidity = find_file(file, "temperature-to-humidity map:", "humidity-to-location map:", seeds[i].temperature);
        seeds[i].location = find_file(file, "humidity-to-location map:", "", seeds[i].humidity);
    }

    //calculate lowest location number
    for (int i = 0; i < seeds.size(); i++) {
        if (res == -1 || seeds[i].location < res) res = seeds[i].location; 
    }

    cout << res << endl;

    return 0;
}
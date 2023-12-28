#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

long long string_to_number (string &word) {
    char* output;
    return strtoll(word.c_str(), &output, 10);
}

//insert in v data between begin and end in file 
void fill_data (ifstream &file, string begin, string end, map<long long, pair<long long, long long>> &v) {
    file.clear(); file.seekg(0);

    string line;

    bool begin_reached, end_reached = false;

    while (! end_reached && getline(file,line)) {
        if (line == begin) begin_reached = true;
        if (line == end && begin_reached) end_reached = true;

        if (end_reached || ! begin_reached || line == begin) continue;

        //reached data block
        istringstream data(line);
        string dest, source, length;

        data >> dest >> source >> length;

        long long source_num = string_to_number(source);
        long long length_num = string_to_number(length);
        long long dest_num = string_to_number(dest);

        v.insert({ dest_num + length_num - 1 , {dest_num , source_num}}); //last in range, init range, init dest range
    }
}

long long find_map (long long & value, map<long long, pair<long long, long long>> & data) {
    map<long long, pair<long long, long long>>::iterator it;

    //find the first element in key greater or equal to value
    it = data.lower_bound(value); 
    
    if (it != data.end() && (it->second).first <= value){
        return (it->second).second + value - (it->second).first;  //value is mapped
    } else {
        return value; 
    }
}

//check if value is mapped in data 
bool find_in (long long & value, map<long long, long long> & data) {
    map<long long, long long>::iterator it;

    it = data.lower_bound(value);
    
    return (it != data.end() && it->second <= value);
}

int main(){
    long long res = 0;

    ifstream file("input.txt");
    string line;

    //save info of seeds
    map<long long, pair<long long, long long>> soil, fertilizer, water, light, temperature, humidity, location;

    fill_data(file, "seed-to-soil map:", "", soil);
    fill_data(file, "soil-to-fertilizer map:", "", fertilizer);
    fill_data(file, "fertilizer-to-water map:", "", water);
    fill_data(file, "water-to-light map:", "", light);
    fill_data(file, "light-to-temperature map:", "", temperature);
    fill_data(file, "temperature-to-humidity map:", "", humidity);
    fill_data(file, "humidity-to-location map:", "", location);

    file.clear(); file.seekg(0); //return to beginning

    //save number of all seeds
    map<long long, long long> seeds;

    getline(file, line);

    istringstream line_seeds(line);
    string start;

    line_seeds >> start; // to ignore first word

    while (line_seeds >> start) {
        //get range of seed
        string length;
        line_seeds >> length;
        
        long long start_num = string_to_number(start);
        long long length_num = string_to_number(length);

        seeds.insert({start_num + length_num - 1, start_num});
    }

    //calculate minimum by reverse
    bool minimum_find = false;

    while (! minimum_find) {
        long long humidity_l = find_map(res, location);
        long long temperature_l = find_map(humidity_l, humidity);
        long long light_l = find_map(temperature_l, temperature);
        long long water_l = find_map(light_l, light);
        long long fertilizer_l = find_map(water_l, water);
        long long soil_l = find_map(fertilizer_l, fertilizer);
        long long seed_l = find_map(soil_l, soil);

        minimum_find = find_in(seed_l, seeds);

        if (! minimum_find) res ++;
    }

    cout << res << endl;

    return 0;
}
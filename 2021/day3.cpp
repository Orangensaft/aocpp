//
// Created by NicolasMeisberger on 03.12.2021.
//

#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <iostream>
#include "day3.h"
#include "../utils.h"

#define INPUT_LEN 12

using namespace std;

map<int, int> get_most_common(vector<string> *inputs){
    map<int,int> zeroes;
    map<int,int> ones;
    map<int,int> most_common;
    int charpos;
    // Count the ones and zeroes
    for (string s: *inputs){
        charpos = 0;
        for (char c: s){
            if (c == '0')
                zeroes[charpos++]++;
            else
                ones[charpos++]++;
        }
    }
    for (int i=0; i<INPUT_LEN; i++) {
        if (ones[i] >= zeroes[i])
            most_common[i] = 1;
        else
            most_common[i] = 0;
    }
    return most_common;
}

void y2021::day3::solve_part_1() {
    vector<string> strings = read_puzzle_input_as_lines(2021,3);
    map<int,int> most_common = get_most_common(&strings);
    // Calculate gamma
    int gamma_bin = 0;
    int shiftpos;
    for (int i=0; i<INPUT_LEN; i++){
        shiftpos = (INPUT_LEN - 1)-i;
        if (most_common[i] == 1) {
            gamma_bin|=(1 << shiftpos);
        }
    }
    // Calculate epsilon
    int epsilon_bin = gamma_bin ^ 0b111111111111;
    cout << "Day 2021.3.1: " << gamma_bin * epsilon_bin << endl;
}


vector<string> filter_out(vector<string> *f_strings, int index, bool invert=false){
    vector<string> out;
    int most_common = get_most_common(f_strings)[index];
    if (invert)
        most_common = !most_common;
    char searched = to_string(most_common).at(0); // '0' or '1'
    for (string s: *f_strings){
        if (s.at(index) == searched)
            out.push_back(s);
    }
    return out;

}

void get_ratings(vector<string> *strings){
    vector<string> oxygen_strings; // keep most_common
    vector<string> co2_strings; // keep least_common
    copy(strings->begin(), strings->end(),back_inserter(oxygen_strings));
    copy(strings->begin(), strings->end(),back_inserter(co2_strings));
    string oxy_level;
    string co2_level;
    for (int i=0; i<INPUT_LEN; i++) {
        oxygen_strings = filter_out(&oxygen_strings, i, false);
        if (oxygen_strings.size() == 1) {
            oxy_level = oxygen_strings.at(0);
            break;
        }
    }
    for (int i=0; i<INPUT_LEN; i++) {
        co2_strings = filter_out(&co2_strings, i, true);
        if (co2_strings.size() == 1) {
            co2_level = co2_strings.at(0);
            break;
        }
    }

    cout << "Day 2021.3.2: " << bin_to_int(&oxy_level) * bin_to_int(&co2_level) << endl;
}

void y2021::day3::solve_part_2() {
    vector<string> strings = read_puzzle_input_as_lines(2021,3);
    get_ratings(&strings);
}

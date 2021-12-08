//
// Created by NicolasMeisberger on 08.12.2021.
//

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "day8.h"
#include "../utils.h"

using namespace std;


void y2021::day8::solve_part_1() {
    vector<string> inputs = read_puzzle_input_as_lines(2021,8);
    vector<string> first_split;
    string right;
    vector<string> right_parts;
    for (string s : inputs){
        // split by |
        first_split = split(&s,'|');
        // take the right part and split it
        right = first_split.at(1);
        for (string t: split(&right,' ',true)){
            right_parts.push_back(t);
        }
    }

    int count = 0;
    for (string s: right_parts){
        if (s.size()==2 || s.size()==3 || s.size()==4 || s.size() == 7)
            count++;
    }

    cout << "Day 2021.8.1: " << count << endl;
}


/*
 *     aaaaaa
 *    b      c
 *    b      c
 *     dddddd
 *    e      f
 *    e      f
 *     gggggg
 */
int segment_to_int(string *s){
    map<int, int> mapping;
    mapping[0b1110111] = 0;
    mapping[0b0010010] = 1;
    mapping[0b1011101] = 2;
    mapping[0b1011011] = 3;
    mapping[0b0111010] = 4;
    mapping[0b1101011] = 5;
    mapping[0b1101111] = 6;
    mapping[0b1010010] = 7;
    mapping[0b1111111] = 8;
    mapping[0b1111011] = 9;

    int tmp = 0;
    for (char c: *s){
        switch (c){
            case 'a':
                tmp |= (1 << 6);
                break;
            case 'b':
                tmp |= (1<<5);
                break;
            case 'c':
                tmp |= (1<<4);
                break;
            case 'd':
                tmp |= (1<<3);
                break;
            case 'e':
                tmp |= (1<<2);
                break;
            case 'f':
                tmp |= (1<<1);
                break;
            case 'g':
                tmp |= (1<<0); //=1
                break;
            default:
                break;
        }
    }
    return mapping[tmp];
}

// How often is each segment used for 0-9?
map <char, int> count_segments(vector<string> *signals){
    map<char, int> out;
    for (string s: *signals){
        for (char c: s){
            out[c]++;
        }
    }
    return out;
}

// Unscramble signal and decode to int
int code_signal_to_int(map<char,char> *mapping, string *signal){
    string realsignal;
    for (char c: *signal){
        realsignal += (*mapping)[c];
    }
    int result = segment_to_int(&realsignal);
    return result;
}

// Get 4-digit number for given line (get mapping + decode)
int calculate_line(string *input_str){
    vector<string> lr = split(input_str,' ');
    vector<string> signals;
    vector<string> code;
    for (int i=0; i<lr.size(); i++){
        if (i<10)
            signals.push_back(lr.at(i));
        if (i>10)
            code.push_back(lr.at(i));
    }

    auto counts = count_segments(&signals);

    map<char,char> mapping;

    map<char, bool> matched;

    for (auto it: counts){
        switch (it.second){
            case 4:
                mapping[it.first] = 'e'; // bot left
                break;
            case 6:
                mapping[it.first] = 'b'; // top left
                break;
            case 9:
                mapping[it.first] = 'f'; // bot right
                break;
        }
    }

    string one;
    string four;
    string seven;
    string eight;

    for (const string& s: signals){
        if (s.size() == 2)
            one = s;
        if (s.size() == 4)
            four = s;
        if (s.size() == 3)
            seven = s;
        if (s.size() == 7)
            eight = s;
    }

    // checking one to see which segment is
    // one
    for (char c: one){
        if (!mapping.contains(c)) // segment is not in the mapping yet, has to be top right (c)
            mapping[c] = 'c';
    }

    for (char c: four){
        if (!mapping.contains(c)) //only segment not in mapping is d (mid)
            mapping[c] = 'd';
    }

    for (char c: seven){
        if (!mapping.contains(c)) // only one missing in 7 is the top (a)
            mapping[c] = 'a';
    }

    for (char c: eight){
        if (!mapping.contains(c))
            mapping[c] = 'g'; // bot one
    }
    // mapping is now complete!

    int total = 0;
    int factor = 1000;
    int cur;

    for (string c : code){
        cur = code_signal_to_int(&mapping, &c);
        total += factor*cur;
        factor = factor/10;
    }

    return total;
}

void y2021::day8::solve_part_2() {
    vector<string> lines = read_puzzle_input_as_lines(2021,8);
    int total = 0;
    for (string line: lines){
        total += calculate_line(&line);
    }

    cout << "Day 2021.8.2: " << total << endl;

}

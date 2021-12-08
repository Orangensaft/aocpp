//
// Created by NicolasMeisberger on 08.12.2021.
//

#include <vector>
#include <string>
#include <iostream>
#include "day8.h"
#include "../utils.h"

using namespace std;


// by length of signal give possible numbers
vector<int> get_possible_numbers(string *signal){
    vector<int> out;
    switch (signal->size()){
        case 2:
            out.push_back(1);
            break;
        case 3:
            out.push_back(7);
            break;
        case 4:
            out.push_back(4);
            break;
        case 5:
            out.push_back(2);
            out.push_back(3);
            out.push_back(5);
            break;
        case 6:
            out.push_back(0);
            out.push_back(6);
            out.push_back(9);
            break;
        case 7:
            out.push_back(8);
            break;
    }
    return out;
}


vector<char> get_segments(int i){
    switch (i){
        case 0:
            return {'a', 'b','c','e','f','g'};
        case 1:
            return {'c', 'f'};
        case 2:
            return {'a', 'c', 'd', 'e', 'g'};
        case 3:
            return {'a', 'c', 'd', 'f', 'g'};
        case 4:
            return {'b', 'c', 'd', 'f'};
        case 5:
            return {'a', 'b', 'd', 'f', 'g'};
        case 6:
            return {'a', 'b', 'd', 'e', 'f', 'g'};
        case 7:
            return {'a', 'c', 'f'};
        case 8:
            return {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        case 9:
            return {'a', 'b', 'c', 'd', 'f', 'g'};
        default:
            return {};
    }
}


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
        if (get_possible_numbers(&s).size()==1)
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
void y2021::day8::solve_part_2() {
    // TODO
}

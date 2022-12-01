//
// Created by NicolasMeisberger on 01.12.2022.
//

#include <iostream>
#include <algorithm>
#include "day1.h"
#include "../utils.h"

using namespace std;


vector<long> fill_bags(vector<string> *lines){
    vector<long> bags;
    long total = 0;
    for (string line: *lines){
        if (line.empty()){
            bags.push_back(total);
            total=0;
            continue;
        }
        total += stoi(line);
    }
    return bags;
}


void y2022::day1::solve_part_1() {
    vector<string> lines = read_puzzle_input_as_lines(2022,1);
    auto bags = fill_bags(&lines);
    long biggest = max_elem_long(bags);
    print_solution(2022,1,1,biggest);
}

void y2022::day1::solve_part_2() {
    vector<string> lines = read_puzzle_input_as_lines(2022,1);
    auto bags = fill_bags(&lines);
    sort(bags.begin(), bags.end());
    auto idx = bags.size()-1;
    auto total = bags[idx] + bags[idx-1] + bags[idx-2];
    print_solution(2022,1,2,total);
}

//
// Created by NicolasMeisberger on 01.12.2021.
//

#include <string>
#include <vector>
#include <iostream>
#include "day1.h"
#include "../utils.h"

using namespace std;

int get_increases(vector<int> *depths){
    int total = 0;
    int last = 9999999;
    for (int cur : *depths){
        if (cur > last){
            total++;
        }
        last = cur;
    }
    return total;
}

vector<int> get_depths(){
    string input = read_puzzle_input(2021,1);
    vector<string> splitted = split_old(input, '\n');
    vector<int> depths = map_to_int(splitted);
    return depths;
}

int get_window_increases(vector<int> *depths){
    const int last_index = (int)depths->size()-1;
    const int last_window_index = last_index - 2;
    int first, second, third;
    int prev_sum = 999999;
    int sum;
    int increases = 0;
    for (int i=0; i<=last_window_index; i++){
        first = depths->at(i);
        second = depths->at(i+1);
        third = depths->at(i+2);
        sum = first + second + third;
        if (sum > prev_sum){
            increases++;
        }
        prev_sum=sum;
    }
    return increases;
}

void y2021::day1::solve_part_1() {
    vector<int> depths = get_depths();
    cout << "Day 2021.1.1: " << get_increases(&depths) << "\n";
}

void y2021::day1::solve_part_2() {
    vector<int> depths = get_depths();
    //vector<int> depths = {199,200,208,210,200,207,240,269,260,263};
    int increases = get_window_increases(&depths);
    cout << "Day 2021.1.2: " << increases << endl;
}

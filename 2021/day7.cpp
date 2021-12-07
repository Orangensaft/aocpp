//
// Created by NicolasMeisberger on 07.12.2021.
//
#include <iostream>
#include <map>
#include <algorithm>
#include "day7.h"
#include "../utils.h"

using namespace std;

vector<int> get_crabs(){
    string input = read_puzzle_input(2021,7); //"16,1,2,0,4,2,7,1,2,14";
    vector<string> input_lst = split(&input, ',', true);
    vector<int> positions = map_to_int(input_lst);
    return positions;
}

int get_fuel_cost(vector<int> *positions, int target){
    int out = 0;
    for (int p: *positions){
        out += abs(target-p);
    }
    return out;
}

int gauss(int n){
    return (n*(n+1))/2;
}

int get_fuel_cost_v2(vector<int> *positions, int target){
    int out = 0;
    int distance;
    for (int p: *positions){
        distance = abs(target-p);
        out += gauss(distance);
    }
    return out;
}

// brute force the shit out of it
void y2021::day7::solve_part_1() {
    auto positions = get_crabs();
    int start_pos = *min_element(positions.begin(), positions.end());
    int end_pos = *max_element(positions.begin(), positions.end());
    int cost;
    int found_cost=INT_MAX;
    for (int pos=start_pos; pos<=end_pos; pos++){
        cost = get_fuel_cost(&positions, pos);
        if (cost < found_cost) {
            found_cost = cost;
        }
    }

    cout << "Day 2021.7.1: " << found_cost << endl;
}

void y2021::day7::solve_part_2() {
    auto positions = get_crabs();
    int start_pos = *min_element(positions.begin(), positions.end());
    int end_pos = *max_element(positions.begin(), positions.end());
    int cost;
    int found_cost=INT_MAX;
    for (int pos=start_pos; pos<=end_pos; pos++){
        cost = get_fuel_cost_v2(&positions, pos);
        if (cost < found_cost) {
            found_cost = cost;
        }
    }
    cout << "Day 2021.7.2: " << found_cost << endl;
}

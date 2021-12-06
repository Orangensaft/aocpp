//
// Created by NicolasMeisberger on 06.12.2021.
//
#include <iostream>
#include <vector>
#include "day6.h"
#include "../utils.h"

// datatype to use for counting, int was a *bit* small :D
#define COUNT_TYPE long long

using namespace std;

vector<int> get_jelly_ints(){
    string jellystr = read_puzzle_input(2021,6); // "3,4,3,1,2";
    vector<string> jellyinput = split(&jellystr,',');
    vector<int> jelly_int = map_to_int(jellyinput);
    return jelly_int;
}


void tick(vector<COUNT_TYPE> *states){
    vector<COUNT_TYPE> temp;  // counts
    temp.reserve(9);
    COUNT_TYPE count;
    int newstate;
    for (int i=0; i<9; i++){
        temp.push_back(0ll);
    }
    for (int state_idx=0; state_idx<temp.size(); state_idx++){
        count = states->at(state_idx);
        if (count == 0){ //nothing to do in this state.
            continue;
        }
        newstate = (state_idx-1);
        if (newstate == -1) {
            newstate = 6; // reset internal timer to 6
            temp[8] = count; // give birth jellyfish
        }
        temp[newstate] += count; // update states
    }
    // now temp contains our new jellyfish counts
    // update the map
    for (int i=0; i<temp.size(); i++){
        (*states)[i]=temp[i];
    }
}


COUNT_TYPE count_jelly(vector<COUNT_TYPE> *states){
    COUNT_TYPE count = 0;
    for (COUNT_TYPE c : *states){
        count += c;
    }
    return count;
}


COUNT_TYPE simulate(int days){
    // init
    COUNT_TYPE solution = 0ll;
    vector<COUNT_TYPE> states;
    states.reserve(9);
    for (int i=0; i<9; i++){
        states.push_back(0ll);
    }

    // load jelly
    auto jelly_ints = get_jelly_ints(); // initial states

    // convert to list of counts
    for (auto jelly : jelly_ints){
        states[jelly] += 1ll;
    }

    // Simulate
    for (int i=1; i<=days; i++){
        tick(&states);
    }

    // count
    solution = count_jelly(&states);
    return solution;
}


void y2021::day6::solve_part_1() {
    cout << "Day 2021.6.1: " << simulate(80) << endl;
}


void y2021::day6::solve_part_2() {
    cout << "Day 2021.6.2: " << simulate(256) << endl;
}

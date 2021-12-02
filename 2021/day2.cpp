//
// Created by NicolasMeisberger on 02.12.2021.
//

#include <string>
#include <vector>
#include <iostream>
#include "day2.h"
#include "../utils.h"

using namespace std;

struct position{
    int horizontal;
    int depth;
    int aim;
};


void update_position(string *line, position *p){
    vector<string> parts = split(*line, ' ');
    string cmd = parts.at(0);
    int value = atoi(parts.at(1).c_str());
    if (cmd == "forward")
        p->horizontal += value;
    if (cmd == "down")
        p->depth += value;
    if (cmd =="up")
        p->depth -= value;
}


void update_position_v2(string *line, position *p){
    vector<string> parts = split(*line, ' ');
    string cmd = parts.at(0);
    int value = atoi(parts.at(1).c_str());
    if (cmd == "down")
        p->aim += value;
    if (cmd == "up")
        p->aim -= value;
    if (cmd == "forward") {
        p->horizontal += value;
        p->depth += p->aim * value;
    }
}


void y2021::day2::solve_part_1() {
    string inputs = read_puzzle_input(2021,2);
    vector<string> lines = split(inputs, '\n');
    position p;
    p.horizontal = 0;
    p.depth = 0;
    for (string line: lines){
        update_position(&line, &p);
    }
    cout << "Day 2021.2.1: " << p.horizontal * p.depth << endl;
}

void y2021::day2::solve_part_2() {
    string inputs = read_puzzle_input(2021,2);
    vector<string> lines = split(inputs, '\n');
    position p;
    p.horizontal = 0;
    p.depth = 0;
    p.aim = 0;
    for (string s: lines){
        update_position_v2(&s, &p);
    }
    cout << "Day 2021.2.2: " << p.horizontal * p.depth << endl;
}

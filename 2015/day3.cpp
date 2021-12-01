//
// Created by NicolasMeisberger on 23.11.2021.
//

#include <string>
#include <map>
#include <iostream>
#include "day3.h"
#include "../utils.h"

struct Coord{
    int x=0;
    int y=0;
};

void update_position(Coord* c, char* command){
    switch (*command) {
        case '^':
            c->y++;
            break;
        case '>':
            c->x++;
            break;
        case '<':
            c->x--;
            break;
        case 'v':
            c->y--;
            break;
    }
}

std::string pos_to_string(Coord* c){
    std::string out;
    out += std::to_string(c->x) + ',' + std::to_string(c->y);
    return out;
}

void day3::solve_part_1(){
    std::string input = read_puzzle_input(2015,3);
    std::map<std::string, int> visited;
    Coord pos;
    pos.x = 0;
    pos.y = 0;
    visited[pos_to_string(&pos)]++;
    for (char cmd : input){
        update_position(&pos, &cmd);
        visited[pos_to_string(&pos)]++;
    }
    int total = (int) visited.size();
    std::cout << "Day 2015.3.1: " << total << "\n";
}

void day3::solve_part_2(){
    std::string input = read_puzzle_input(2015, 3);
    std::map<std::string, int> visited;
    Coord santa;
    santa.x = 0;
    santa.y = 0;
    Coord robo;
    robo.x = 0;
    robo.y = 0;
    Coord* active;
    visited[pos_to_string(&santa)]++;

    int pos = 0;
    for (char c : input){
        // take turns
        if (pos++ % 2 == 0){
            active = &santa;
        } else {
            active = &robo;
        }
        update_position(active, &c);
        visited[pos_to_string(active)]++;
    }

    int total = (int) visited.size();
    std::cout << "Day 2015.3.2: " << total << "\n";
}
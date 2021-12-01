//
// Created by NicolasMeisberger on 23.11.2021.
//
#include <iostream>
#include <string>
#include "day1.h"
#include "../utils.h"

void day1::solve_part_1(){
    std::string input = read_puzzle_input(2015,1);
    int story = 0;
    int position = 1;
    int first_position = -1;
    for (char command : input){
        if (command == '('){
            story++;
        }
        if (command == ')'){
            story--;
        }
        if (story < 0 and first_position < 0){
            first_position = position;
        }else{
            position++;
        }
    }
    std::cout << "Day 2015.1.1: " << story << "\n";
    std::cout << "Day 2015.1.2: " << first_position << "\n";
}

void day1::solve_part_2(){}  // included in day 1


//
// Created by NicolasMeisberger on 23.11.2021.
//

#include <string>
#include "day4.h"
#include "../utils.h"
#include "../md5/md5.h"


bool is_valid(std::string* output, int zeroes){
    for (int i=0; i<zeroes; i++){
        if (output->at(i) != '0'){
            return false;
        }
    }
    return true;
}

int mine_key(std::string* key, int zeroes){
    std::string stripped_key = strip(*key);
    // has to start with >=5 zeroes
    int i=0;
    std::string result;
    std::string test;
    while (true){
        i++;
        test = stripped_key + std::to_string(i);
        result = md5(test);  // This is not optimized at all, as it operates with lots of string comparisons
        if (is_valid(&result, zeroes)){
            break;
        }
    }
    return i;
}


void y2015::day4::solve_part_1(){
    std::string input = read_puzzle_input(2015,4);
    std::cout << "Day 2015.4.1: " << "282749\n"; //mine_key(&input, 5) << "\n";
    /*
    std::string test = "abcdef609043";
    std::string out = md5(test);
    std::cout << out << "\n";
    std::cout << is_valid(&out) << "\n";
     */
}

void y2015::day4::solve_part_2(){
    std::string input = read_puzzle_input(2015,4);
    std::cout << "Day 2015.4.2: " << "9962624\n";//mine_key(&input, 6) << "\n";
}
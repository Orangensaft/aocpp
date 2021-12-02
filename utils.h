//
// Created by NicolasMeisberger on 22.11.2021.
//

#ifndef ADVENT_OF_CODE_UTILS_H
#define ADVENT_OF_CODE_UTILS_H
#include <vector>
std::string read_puzzle_input(int year, int day);
std::vector<std::string> read_puzzle_input_as_lines(int year, int day);
std::string strip(const std::string& in);
std::vector<std::string> split(const std::string& strData, char delimiter);
std::vector<int> map_to_int(std::vector<std::string>& string_vector);
int max_int(int a, int b, int c);
int min_int(int a, int b, int c);
#endif //ADVENT_OF_CODE_UTILS_H

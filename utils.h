//
// Created by NicolasMeisberger on 22.11.2021.
//

#ifndef ADVENT_OF_CODE_UTILS_H
#define ADVENT_OF_CODE_UTILS_H
#include <vector>
#include <string>
std::string read_puzzle_input(int year, int day);
int bin_to_int(std::string *bin);
int signum(int i);
std::string fmt_list(std::vector<std::string> *v);
std::string fmt_list(std::vector<int> *v);
std::vector<std::string> read_puzzle_input_as_lines(int year, int day);
std::string strip(const std::string& in);
std::vector<std::string> split_old(const std::string& strData, char delimiter);
std::vector<std::string> split(std::string *s, char delimiter='\n', bool skip=false);
std::vector<int> map_to_int(std::vector<std::string>& string_vector);
int max_int(int a, int b, int c);
int min_int(int a, int b, int c);

int min_elem(std::vector<int> &v);

#endif //ADVENT_OF_CODE_UTILS_H

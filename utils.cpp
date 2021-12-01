//
// Created by NicolasMeisberger on 22.11.2021.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <locale>

#include "utils.h"

std::string strip(const std::string& in) {
    // Removes ALL special chars
    char final[2000];
    char* cursor = final;
    for(std::string::const_iterator c = in.begin(), end = in.end(); c != end; ++c) {
        char cc = *c;
        if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
        {
            *cursor = cc;
            ++cursor;
        }
    }
    *cursor = 0;
    return final;
}

std::vector<std::string> split(const std::string& strData, char delimiter)
{;
    //Define contant data that will be worked as delimiter
    //Define the dynamic array variable of strings
    std::vector<std::string> outputArray;
    //Construct a stream from the string
    std::stringstream streamData(strData);
    /*
    Declare string variable that will be used
    to store data after split
    */
    std::string val;
    /*
    The loop will iterate the splitted data and
    insert the data into the array
    */
    while (std::getline(streamData, val, delimiter)) {
        if ((int)val.at(0) == -1){
            continue;
        }
        outputArray.push_back(val);
    }
    return outputArray;
}

// Converting a string vector to an int vector -> assuming casting works, will segfault else.
std::vector<int> map_to_int(std::vector<std::string>& string_vector){
    std::vector<int> out;
    int cur = 0;
    for (const std::string& s : string_vector){
        cur = std::stoi(s);
        out.push_back(cur);
    }
    return out;
}

std::string generate_path(int year, int day){
    std::string out = "inputs/";
    out += std::to_string(year) + "/" + std::to_string(day);
    return out;
}


std::string read_puzzle_input(int year, int day) {
    std::string path = generate_path(year, day);
    // std::cout << "Reading " << path << "\n";
    std::ifstream inputfile(path);
    std::string out;
    while (inputfile){
        out += (char)inputfile.get();
    }
    inputfile.close();
    return out;
}


int max_int(int a, int b, int c){
    if (a > b){
        if (a>c){
            return a;
        } else {
            return c;
        }
    } else {
        if (b > c){
            return b;
        } else {
            return c;
        }
    }
}

int min_int(int a, int b, int c){
    if (a < b){
        if (a<c){
            return a;
        } else {
            return c;
        }
    } else {
        if (b < c){
            return b;
        } else {
            return c;
        }
    }
}
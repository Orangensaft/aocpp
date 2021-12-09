//
// Created by NicolasMeisberger on 22.11.2021.
//
#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "utils.h"

int signum(int i){
    if (i>0)
        return 1;
    if (i<0)
        return -1;
    return 0;
}

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

std::vector<std::string> split(std::string *s, char delimiter, bool skip){
    /**
     * Splits given string into an vector of strings by given delimiter
     * if skip is true, then empty substrings will be skipped
     * "1,2,,3,4" will result in {"1", "2", "", "3", "4"} when skip is false
     * otherwise {"1","2","3","4"} will be the result.
     */
    std::vector<std::string> lines;
    std::string cur;
    for (char c: *s){
        if (c==delimiter){
            if (skip and cur.empty())
                continue;
            lines.push_back(cur);
            cur = "";
            continue;
        }
        cur += c;
    }
    if (!cur.empty()){
        lines.push_back(cur);
    }
    return lines;
}

//deprecated
std::vector<std::string> split_old(const std::string& strData, char delimiter)
{;
    //Define contant data that will be worked as delimiter
    //Define the dynamic array variable of strings
    std::vector<std::string> outputArray;
    //Construct a stream from the string
    std::stringstream streamData(strData);
    /*
    Declare string variable that will be used
    to store data after split_old
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


std::vector<std::string> read_puzzle_input_as_lines(int year, int day){
    std::string input = read_puzzle_input(year, day);
    return split_old(input, '\n');
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

std::string fmt_list(std::vector<std::string> *v){
    std::string o;
    for (std::string s: *v){
        o+=s + ", ";
    }
    return o;
}

int min_elem(std::vector<int> &v){
    int out = INT_MAX;
    for (int i: v){
        if (i<=out)
            out=i;
    }
    return out;
}

std::string fmt_list(std::vector<int> * v){
    std::string o;
    for (int i: *v){
        o+= std::to_string(i)+", ";
    }
    return o;
}

int bin_to_int(std::string *bin){
    int len = (int)bin->size();
    int out = 0;
    int shiftvalue;
    for (int i=0; i<len; i++){
        shiftvalue = (len-i)-1;
        if (bin->at(i)=='1') {
            out |= (1 << shiftvalue);
        }
    }
    return out;
}
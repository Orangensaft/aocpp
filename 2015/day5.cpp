//
// Created by NicolasMeisberger on 01.12.2021.
//

#include <string>
#include <iostream>
#include "day5.h"
#include "../utils.h"

using namespace std;

bool is_vovel(char c){
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' )
        return true;
    return false;
}

bool has_three_vovels(string *s){
    int vovelcount = 0;
    for (char c: *s){
        if (is_vovel(c))
            vovelcount++;
        if (vovelcount>=3)
            return true;
    }
    return false;
}

vector<string> get_double_letters(string *s){
    vector<string> out;
    string checking;
    for (int i=0; i<=s->size()-2; i++){
        checking = s->at(i) + s->at(i+1);
        if (s->at(i) == s->at(i+1))
            out.push_back(checking);
    }
    return out;
}

bool has_double_letter(string *s){
    vector<string> doubles = get_double_letters(s);
    if (!doubles.empty()){
        return true;
    }
    return false;
}

bool has_no_forbidden_substrings(string *s){
    for (string sub: {"ab", "cd", "pq", "xy"}){
        if (s->find(sub) != -1)  // substring is contained
            return false; // Forbidden string found
    }
    return true;
}

bool is_nice(string *s){
    if (has_three_vovels(s) && has_double_letter(s) && has_no_forbidden_substrings(s))
        return true;
    return false;
}

// Part 2
bool has_double_with_sep(string *s){
    for (int i=0; i<=s->size()-3; i++){
        if (s->at(i) == s->at(i+2)){
            return true;
        }
    }
    return false;
}

// Please look away from this monstrosity :<
bool has_non_overlap_pair(string *s){
    string cur;
    string other;
    char i_0, i_1;
    const int max_index = (int)s->size()-2;
    for (int i=0; i<=max_index; i++){
        // this is the substring we are searching
        cur = "";
        cur += s->at(i);
        cur += s->at(i+1);
        // now starting from i+2 (no overlap) search.
        for (int j=i+2; j<=max_index; j++){
            other = "";
            other += s->at(j);
            other += s->at(j+1);
            if (cur == other)
                return true;
        }
    }
    return false;
}

bool is_really_nice(string *s){
    if (has_non_overlap_pair(s) && has_double_with_sep(s))
        return true;
    return false;
}

void y2015::day5::solve_part_1(){
    std::string input = read_puzzle_input(2015,5);
    std::vector<std::string> strings = split_old(input, '\n');
    int total = 0;
    for (string s: strings){
        if (is_nice(&s))
            total++;
    }
    cout << "Day 2015.5.1: " << total << endl;
}

void y2015::day5::solve_part_2(){
    string input = read_puzzle_input(2015,5);
    vector<string> strings = split_old(input, '\n');
    int total = 0;
    for (string s: strings){
        if (is_really_nice(&s))
            total++;
    }
    cout << "Day 2015.5.2: " << total << endl;
}
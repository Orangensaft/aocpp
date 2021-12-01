//
// Created by NicolasMeisberger on 23.11.2021.
//

#include <string>
#include <iostream>
#include "day2.h"
#include "../utils.h"

struct Parcel{
    int l;
    int w;
    int h;
};


Parcel read_parcel(std::string* line){
    /**
     * Parsing a single line (LxWxH) into a Parcel struct
     */
    Parcel p;
    p.l = 0;
    p.w = 0;
    p.h = 0;
    std::string current_part;
    int to_set = 0; // l, w, h
    for (char c : *line){
        if (c=='\n')
            continue;
        if (c=='x'){ //2x3x4
            switch (to_set++) {
                case 0:
                    p.l = std::stoi(current_part);
                    break;
                case 1:
                    p.w = std::stoi(current_part);
                    break;
            }
            current_part = "";
        } else {
            current_part += c;
        }
    }
    p.h = std::stoi(current_part); // last part will not be created, as it does not end with an "x"
    return p;
}


int calculate_ribbon(Parcel* p){
    int volume = p->h*p->l*p->w;
    // Just add all sides, and remove the max one again
    //std::cout << "Volume is " << volume << "\n";
    int len = (2*p->h + 2*p->l + 2*p->w) - 2* max_int(p->h, p->w, p->l);
    //std::cout << "Len is " << len << "\n";
    int total = len + volume;
    //std::cout << "Total is " << total << "\n";
    return total;
}


int calculate_paper(Parcel* p){
    int side_a = p->l * p->w;
    int side_b = p->w * p->h;
    int side_c = p->h * p->l;
    int slack = min_int(side_a, side_b, side_c);
    int paper = 2*side_a + 2*side_b + 2*side_c;
    return paper + slack;
}


void day2::solve_part_1(){
    std::string input = read_puzzle_input(2015,2);
    std::string current;
    int total_paper = 0;
    int total_ribbon = 0;
    for (char c: input){
        if (c == '\n'){
            //std::cout << "Current is " << current << "\n";
            Parcel p = read_parcel(&current);
            total_paper += calculate_paper(&p);
            total_ribbon += calculate_ribbon(&p);
            current = "";
        }
        current += c;
    }
    // File ends in \n, so nothing to do here anymore
    std::cout << "Day 2015.2.1: " << total_paper << "\n";
    std::cout << "Day 2015.2.2: " << total_ribbon << "\n";
    // parse lines
    // f.e. line:
    // line -> parcel
    // f.e. parcel:
    // sum paper needed

    //std::string line = "2x3x4";
    //Parcel p = read_parcel(&line);
    //std::cout << p.l << " " << p.w << " " << p.h << "\n";
    //int ribbon = calculate_ribbon(&p);
    //std::cout << "Ribbon " << ribbon << "\n";
    //int paper = calculate_paper(&p);
    //std::cout << "Paper: " << paper << "\n";
}

void day2::solve_part_2(){

}
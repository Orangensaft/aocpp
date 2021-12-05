//
// Created by NicolasMeisberger on 05.12.2021.
//
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "day5.h"
#include "../utils.h"

using namespace std;

struct point{
    int x;
    int y;

    string fmt(){
        return to_string(this->x)+","+ to_string(this->y);
    }
};

struct line{
    point start;
    point end;

    bool is_h_v(){
        return (this->start.x == this->end.x || this->start.y == this->end.y);
    }

    vector<point> get_diag_inbetween(){
        vector<point> out;
        // As we are only getting 45° sign(dx) and sign(dy) is fine for the discrete steps
        int dx = signum(this->end.x - this->start.x);
        int dy = signum(this->end.y - this->start.y);
        point cur{this->start.x, this->start.y};
        out.push_back(cur);
        while (cur.x != this->end.x || cur.y != this->end.y){
            cur.x += dx;
            cur.y += dy;
            out.push_back(cur);
        }
        return out;
    }

    string fmt(){
        return this->start.fmt() + " -> " + this->end.fmt();
    }
};


point create_point(string *p_str){
    vector<string> str_parts = split(p_str, ',');
    vector<int> parts = map_to_int(str_parts);
    point p{};
    p.x = parts.at(0);
    p.y = parts.at(1);
    return p;
}

line create_line(point *start, point *end){
    line l{};
    l.start = *start;
    l.end = *end;
    return l;
}

line parse_line(string *l){
    vector<string> parts = split(l,' ');
    point start = create_point(&parts.at(0));
    point end = create_point(&parts.at(2));
    line li = create_line(&start, &end);
    return li;
}

vector<line> read_vent_lines(bool skip_diag){
    vector<string> input = read_puzzle_input_as_lines(2021,5);
    vector<line> lines;
    lines.reserve(input.size());
    for (string s: input) {
        line l = parse_line(&s);
        if (skip_diag && !l.is_h_v())
            continue;
        lines.push_back(l);
    }

    return lines;
}


int count_overlaps(map<string,int> *hits){
    int overlap = 0;
    int count;
    for (auto iter = hits->begin(); iter!=hits->end(); ++iter){
        count = iter->second;
        if (count >= 2)
            overlap++;
    }
    return overlap;
}


void y2021::day5::solve_part_1() {
    vector<line> lines = read_vent_lines(true);
    map<string,int> hit;
    for (line l: lines){
        vector<point> points = l.get_diag_inbetween();
        for (auto p: points){
            hit[p.fmt()]++;  // where are vents?
        }
    }

    cout << "Day 2021.5.1: " << count_overlaps(&hit) << endl;

}

void y2021::day5::solve_part_2() {
    vector<line> lines = read_vent_lines(false);
    map<string,int> hit;
    for (line l: lines) {
        vector<point> points = l.get_diag_inbetween();
        for (auto p: points) {
            hit[p.fmt()]++;  // where are vents?
        }
    }

    cout << "Day 2021.5.2: " << count_overlaps(&hit) << endl;
}

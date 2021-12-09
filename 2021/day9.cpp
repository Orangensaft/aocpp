//
// Created by NicolasMeisberger on 09.12.2021.
//

#include "day9.h"
#include <iostream>
#include "../utils.h"

using namespace std;

struct Heightmap{
    int heights [100*100];
    /*
     * (0,0) ..... (100,0)
     *   .            .
     *   .            .
     * (100,0) .... (100,100)
     */

    Heightmap(){
        for (int i=0; i<100*100; i++){
            this->heights[i] = 0;
        }
    }

    int get(int x, int y){
        if (x<0 || x> 99 || y<0 || y > 99)
            return -1; // outside the field
        int idx = 100*y + x;
        return this->heights[idx];
    }

    vector<int> get_neighbors(int x, int y){
        vector<int> out;
        int val;
        for (int y_i = y - 1; y_i <= y + 1; y_i++) {
            for (int x_i=x-1; x_i <= x+1; x_i++) {
                if (x_i==x-1 && y_i==y-1) // top left diag
                    continue;
                if (x_i==x+1 && y_i==y+1) // bot right
                    continue;
                if (x_i==x-1 && y_i==y+1) // bot left
                    continue;
                if (x_i==x+1 && y_i==y-1) // top right
                    continue;
                if (x==x_i && y==y_i)
                    continue; // skip center
                val = this->get(x_i, y_i);
                if (val != -1) {
                    out.push_back(val);
                }
            }
        }
        return out;
    }
};

void y2021::day9::solve_part_1() {
    auto lines = read_puzzle_input_as_lines(2021,9);
    Heightmap h;
    int i=0;
    // reading in the heightmap
    for (const auto& line: lines){
        for (char c: line){
            h.heights[i++] = atoi(&c);
        }
    }

    int total = 0;
    int cur;
    vector<int> neighbors;
    for (int y=0; y<100; y++){
        for (int x=0; x<100; x++){
            cur = h.get(x,y);
            neighbors = h.get_neighbors(x,y);
            if (cur < min_elem(neighbors))
                total += (cur+1);

        }
    }
    cout << "Day 2021.9.1: " << total << endl;
}

void y2021::day9::solve_part_2() {
    /*
     * Recursive method, but iterative with a stack instead:
     *
     * Find low points
     * For each low point
     *  add low point to basin
     *  stack = []
     *  put all neighbors that are bigger then the current point != 9 to the stack
     *  while stack not empty:
     *      put point to basin
     *      put all neighbors that are bigger then the current point != 9 to the stack
     *  We now have the basin for each low point
     *  -> If basins overlap add a check that a point may be only in one basin at a time.
     *
     */
}

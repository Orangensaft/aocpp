//
// Created by NicolasMeisberger on 22.11.2022.
//

#include <iostream>
#include <regex>
#include "day6.h"
#include "../utils.h"

using namespace std;

enum Action {off, on, toggle, undef};

struct Command{
    Action action;
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

void print_command(Command* c){
    cout << "Command: " << c->action << " " << c->from_x << "," << c->from_y << "->" <<c->to_x << "," << c->to_y <<endl;
}

const int SIZE_X = 1000;
const int SIZE_Y = 1000;

struct Lights {
    vector<int> states;

    Lights() {
        for (int i=0; i<SIZE_X*SIZE_Y; i++) {
            this->states.push_back(0);
        }
    }

    int count_value(int value){
        int total = 0;
        for (int &state : this->states){
            if (value == state)
                total++;
        }
        return total;
    }

    int sum_values(){
        int out = 0;
        for (int &state: this->states){
            out+=state;
        }
        return out;
    }

    static int get_idx(int x, int y){
        return x + SIZE_X*y;
    }

    void set(int x, int y, int value){
        this->states[Lights::get_idx(x,y)] = value;
    }

    int get(int x, int y){
        return this->states[Lights::get_idx(x,y)];
    }

    void issue_command(Command* cmd){
        for (int x = cmd->from_x; x<= cmd->to_x; x++){
            for (int y = cmd->from_y; y<= cmd->to_y; y++){
                int to_set = -1;
                if (cmd->action == on)
                    to_set = 1;
                if (cmd->action == off)
                    to_set = 0;
                if (cmd->action == toggle)
                    to_set = !this->get(x,y);
                this->set(x,y,to_set);
            }
        }
    }

    void issue_command_bright(Command* cmd){
        for (int x = cmd->from_x; x<= cmd->to_x; x++){
            for (int y = cmd->from_y; y<= cmd->to_y; y++){
                int value = this->get(x,y);
                if (cmd->action == on)
                    value++;
                if (cmd->action == off){
                    if (value > 0)  // dont go below 0
                        value--;
                }
                if (cmd->action == toggle)
                    value+=2;
                this->set(x,y,value);
            }
        }
    }
};



Command parse_line(string* line){
    regex exp = regex(R"((turn off|toggle|turn on)\s(\d+,\d+)\sthrough\s(\d+,\d+))");
    Command c{undef,0,0,0,0};
    smatch sm;
    regex_match(*line, sm, exp);

    // Parse command
    string command = sm[1].str();
    if (command == "turn off")
        c.action = off;
    if (command == "toggle")
        c.action = toggle;
    if (command == "turn on")
        c.action = on;

    // From coord
    string from_xy = sm[2].str();
    vector<string> from_xy_split = split(&from_xy, ',');
    c.from_x = stoi(from_xy_split[0]);
    c.from_y = stoi(from_xy_split[1]);

    // To coord
    string to_xy = sm[3].str();
    vector<string> to_xy_split = split(&to_xy, ',');
    c.to_x = stoi(to_xy_split[0]);
    c.to_y = stoi(to_xy_split[1]);

    return c;
}

void y2015::day6::solve_part_1() {
    vector<string> input = read_puzzle_input_as_lines(2015, 6);

    Lights lights;

    for (string s: input){
        auto cmd = parse_line(&s);
        //print_command(&cmd);
        lights.issue_command(&cmd);
    }

    print_solution(2015,6,1, lights.count_value(1));

}


void y2015::day6::solve_part_2() {
    Lights lights;
    for (string s: read_puzzle_input_as_lines(2015, 6)){
        auto cmd = parse_line(&s);
        //print_command(&cmd);
        lights.issue_command_bright(&cmd);
    }
    print_solution(2015,6,2, lights.sum_values());

}



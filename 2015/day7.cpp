//
// Created by NicolasMeisberger on 23.11.2022.
//

#include <iostream>
#include "day7.h"
#include "../utils.h"
#include <regex>
#include <map>

using namespace std;

typedef unsigned short signal;

enum Operator {ASSIGN,AND,OR,LSHIFT,RSHIFT,NOT, ASSIGN_MEM};
enum WireNodeType {WIRE, CONSTANT, OP};

struct WireNode{
    WireNodeType type;
    signal value;
    string name;
    Operator op;
    vector<WireNode> children;
    vector<WireNode> parents;

    signal get_value(){
        switch (this->type){
            case CONSTANT:
                return this->value;
            case WIRE:
                return this->parents[0].get_value();
            case OP:
                // evaluate op with ALL parent (one or two, depending on)
                return 0;
        }

    }

    /*
     * Rest: Pseudocode:
     * Einmal alles einlesen
     * map mit knoten machen
     * wenn neu: hinzufügen
     * wenn alt: updaten (kinder und eltern)
     * danach A knoten aus der map holen und get_value() aufrufen
     * ????
     * PROFIT
     */

};

struct WireCommand{
    signal value;
    Operator op;
    string operand_1;
    string operand_2;
    string target;
};

WireCommand parse_line(string *line){
    WireCommand c{0,ASSIGN,"a","a","a"};
    smatch sm;

    regex and_one = regex(R"(^1\sAND\s([a-z]+)\s->\s([a-z]+)$)");
    regex_match(*line, sm, and_one);
    auto size = sm.size();
    if (size == 3){
        // 1 and X -> Y   Equals    X --> Y
        c.op = ASSIGN_MEM;
        c.operand_1 = sm[1];
        c.target = sm[2];
        return c;
    }

    regex regex_mem_assign = regex(R"(^([a-z]+)\s->\s([a-z]+)$)");
    regex_match(*line, sm, regex_mem_assign);
    if (sm.size() == 3){
        c.op = ASSIGN_MEM;
        c.operand_1 = sm[1];
        c.target = sm[2];
        return c;
    }
    // Assignment
    regex regex_assign = regex(R"(^(\d+)\s->\s([a-z]+)$)");
    regex_match(*line, sm, regex_assign);
    size = sm.size();
    if (size == 3){
        signal value = (signal)stoi(sm[1]);
        auto target = sm[2];
        c.value = value;
        c.op = ASSIGN;
        c.target = target;
        return c;
    }

    regex regex_not = regex(R"(^NOT\s([a-z]+)\s->\s([a-z]+)$)");
    regex_match(*line, sm, regex_not);
    size = sm.size();
    if (size == 3){
        c.op = NOT;
        c.operand_1 = sm[1];
        c.target = sm[2];
        return c;
    }

    regex regex_op = regex(R"(^([a-z]+)\s(AND|OR|LSHIFT|RSHIFT)\s([a-z]+|\d+)\s->\s([a-z]+)$)");
    regex_match(*line, sm, regex_op);
    size = sm.size();
    if (size == 5){ //op1, OP, op2, target
        string op = sm[2];
        c.target = sm[4];
        c.operand_1 = sm[1];

        if (op=="AND") {
            c.op = AND;
            c.operand_2 = sm[3];
        }
        if (op=="OR") {
            c.op = OR;
            c.operand_2 = sm[3];
        }
        if (op=="LSHIFT") {
            c.op = LSHIFT;
            c.value = (signal)stoi(sm[3]);
        }
        if (op=="RSHIFT") {
            c.op = RSHIFT;
            c.value = (signal)stoi(sm[3]);
        }
        return c;
    }
    cout << *line << endl;
    cout << size << endl;
    return c;
}

class WireNet{
    public:
        void add_cmd(WireCommand *cmd){
            switch(cmd->op){
                case ASSIGN:
                    // NUM -> X
                    WireNode num = {CONSTANT, cmd->value, "_", cmd->op};
                    WireNode tar = {};
            }
        }
    private:
        vector<WireNode> nodes;
        map<string, WireNode> signals;  // to easily access the signals
};

map<string, signal> exec_cmds(vector<WireCommand> *cmds){
    map<string, signal> wires;
    for (WireCommand cmd : *cmds){
        switch (cmd.op){
            case ASSIGN:
                wires[cmd.target] = cmd.value;
                break;
            case NOT:
                wires[cmd.target] = wires[cmd.operand_1] ^ 0xFFFF;
                break;
            case AND:
                wires[cmd.target] = wires[cmd.operand_1] & wires[cmd.operand_2];
                break;
            case OR:
                wires[cmd.target] = wires[cmd.operand_1] | wires[cmd.operand_2];
                break;
            case LSHIFT:
                wires[cmd.target] = wires[cmd.operand_1] << cmd.value;
                break;
            case RSHIFT:
                wires[cmd.target] = wires[cmd.operand_1] >> cmd.value;
                break;
            case ASSIGN_MEM:
                wires[cmd.target] = wires[cmd.operand_1];
        }
    }
    return wires;
}



void y2015::day7::solve_part_1() {
    vector<string> lines = read_puzzle_input_as_lines(2015,7);
    vector<WireCommand> commands;
    for (string si: lines){
        auto cmd = parse_line(&si);
        commands.push_back(cmd);
    }
    cout << "Read " << commands.size() << " Commands" << endl;

    map<string, signal> signals = exec_cmds(&commands);

    cout << signals["a"] << endl;
    cout << signals["lx"] << endl;

}

void y2015::day7::solve_part_2() {

}

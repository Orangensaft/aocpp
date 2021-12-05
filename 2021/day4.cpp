//
// Created by NicolasMeisberger on 04.12.2021.
//

#include <string>
#include <vector>
#include <iostream>
#include "day4.h"
#include "../utils.h"

using namespace std;

// 0,0 being top left, 24,24 bot right
struct bingo{
    vector<int> _values;
    vector<bool> _hit;

    void init(){
        _values.clear();
        _hit.clear();
        for (int i=0; i<25; i++){
            _values.push_back(0);
            _hit.push_back(false);
        }
    }

    void set_line(vector<int> *values, int y){

        for (int x=0; x<values->size(); x++){
            set_value(x,y,values->at(x));
        }
    }

    void print_hits(){
        char to_print;
        for (int y=0; y<5; y++){
            for (int x=0; x<5; x++){
                if (is_hit(x,y))
                    to_print = 'X';
                else
                    to_print = '_';
                cout << to_print << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    static int _get_idx(int x, int y){
        return 5*y + x;
    }

    void set_value(int x, int y, int value){
        _values[_get_idx(x,y)] = value;
    }

    int get_value(int x,int y){
        return _values[_get_idx(x,y)];
    }

    bool hit(int value){
        for (int i=0; i<5*5; i++){
            if (_values[i]==value){
                _hit[i] = true;
                return true;
            }
        }
        return false;
    }

    bool is_hit(int x, int y){
        return _hit[_get_idx(x,y)];
    }

    bool has_won(){ // look away please
        //hoizontal
        int a,b,c,d,e;
        for (int i=0; i<(5*(5-1)); i+=5){ //offset
            a = _hit[i];
            b = _hit[i+1];
            c = _hit[i+2];
            d = _hit[i+3];
            e = _hit[i+4];
            if (a && b && c && d && e)
                return true;
        }

        // vertical
        bool pos_hits[5];
        for (int x=0; x<5; x++){
            for (int y=0; y<5; y++){
                pos_hits[y] = is_hit(x,y);
            }
            if (pos_hits[0] && pos_hits[1] && pos_hits[2] && pos_hits[3] && pos_hits[4])
                return true;
        }

        // diagonals
        if (is_hit(0,0) && is_hit(1,1) && is_hit(2,2) && is_hit(3,3) && is_hit(4,4))
            return true;
        if (is_hit(4,0) && is_hit(3,1) && is_hit(2,2) && is_hit(1,3) && is_hit(0,4))
            return true;
        return false;
    }

    void print(){
        for (int y=0; y<5; y++){
            for (int x=0; x<5; x++){
                cout << get_value(x,y) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    int sum_unmarked(){
        int sum = 0;
        for (int i=0; i<25; i++){
            if (!_hit[i]) {
                 sum += _values[i];
            }
        }
        return sum;
    }

};


vector<string> split_v2(string *s, char delimiter='\n', bool skip=false){
    vector<string> lines;
    string cur;
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


bingo create_bingo(vector<string> *lines){
    bingo b{};
    b.init();
    vector<string> curline;
    vector<int> bingoline;
    string curstring;
    for (int y=0; y<lines->size(); y++){
        curstring = lines->at(y);
        curline = split_v2(&curstring,' ',true);
        bingoline = map_to_int(curline);
        b.set_line(&bingoline,y);
    }
    return b;
}


vector<bingo> create_bingos(vector<string> *lines){
    vector<bingo> out;
    vector<string> collected;
    int total = 0;



    for (string line : *lines){
        collected.push_back(line);
        if (collected.size()==5){
            // enough lines for a bingo
            bingo b = create_bingo(&collected);
            out.push_back(b);
            collected.clear();
        }

    }
    return out;
}

string strip_left(string *s){
    string out = "";
    // from start
    char cur;
    for (int i=0; i<s->size(); i++){
        cur = s->at(i);
        if (out.empty() && cur == ' ')
            continue;
        out += cur;
    }
    return out;
}




void y2021::day4::solve_part_1() {
    string content = read_puzzle_input(2021,4);
    auto lines = split_v2(&content,'\n',true);
    vector<string> calls_str;
    vector<string> bingolines;
    for (int i=0; i<lines.size(); i++){
        if (i==0){
            calls_str = split_v2(&lines.at(i),',',true);
        }else{
            bingolines.push_back(lines.at(i));
        }
    }
    auto calls = map_to_int(calls_str);
    auto bingos = create_bingos(&bingolines);
    int solution=-1;


    bool break_all=false;

    int bingo_idx;

    int just_called = 0;

    for (int c: calls){
        just_called = c;
        for (int i=0; i<bingos.size(); i++){
            bingos.at(i).hit(c);
            if (bingos.at(i).has_won()){
                bingo_idx = i;
                break_all = true;
                break;
            }
        }
        if (break_all)
            break;
    }

    bingo winner = bingos.at(bingo_idx);

    int sum_uncalled = winner.sum_unmarked();

    solution = just_called * sum_uncalled;
    cout << "Day 2021.4.1: " << solution << endl;

}

void y2021::day4::solve_part_2() {
    // copy paste i know. Meh.
    string content = read_puzzle_input(2021,4);
    auto lines = split_v2(&content,'\n',true);
    vector<string> calls_str;
    vector<string> bingolines;
    for (int i=0; i<lines.size(); i++){
        if (i==0){
            calls_str = split_v2(&lines.at(i),',',true);
        }else{
            bingolines.push_back(lines.at(i));
        }
    }
    auto calls = map_to_int(calls_str);
    auto bingos = create_bingos(&bingolines);


    int just_called, bingo_idx;
    bool break_all = false;

    int wins = 0;

    for (int c: calls){
        just_called = c;
        for (int i=0; i<bingos.size(); i++){
            if (bingos.at(i).has_won()) // this one has won already, skip it.
                continue;

            bingos.at(i).hit(c);
            if (bingos.at(i).has_won()){
                wins++;
                if (wins == bingos.size()){  //the last bingo has won
                    bingo_idx = i;
                    break_all = true;
                    break;
                }
            }
        }
        if (break_all)
            break;
    }

    bingo last_winner = bingos.at(bingo_idx);
    int unmarked = last_winner.sum_unmarked();
    int solution = just_called * unmarked;
    cout << "Day 2021.4.2: " << solution << endl;
}

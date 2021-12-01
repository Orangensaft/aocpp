#include "2015/day1.h"
#include "2015/day2.h"
#include "2015/day3.h"
#include "2015/day4.h"
#include "2021/day1.h"
#include "2015/day5.h"

void year2015(){
    y2015::day1::solve_part_1();
    y2015::day1::solve_part_2();
    y2015::day2::solve_part_1();
    y2015::day2::solve_part_2();
    y2015::day3::solve_part_1();
    y2015::day3::solve_part_2();
    y2015::day4::solve_part_1();
    y2015::day4::solve_part_2();
    y2015::day5::solve_part_1();
    y2015::day5::solve_part_2();
}

void year2021(){
    y2021::day1::solve_part_1();
    y2021::day1::solve_part_2();
}

int main() {
    year2015();
    year2021();
    return 0;
}

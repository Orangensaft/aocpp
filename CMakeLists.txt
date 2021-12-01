cmake_minimum_required(VERSION 3.20)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent_of_code main.cpp utils.cpp utils.h 2015/day1.cpp 2015/day1.h 2015/day2.cpp 2015/day2.h 2015/day3.cpp 2015/day3.h md5/md5.cpp md5/md5.h 2015/day4.cpp 2015/day4.h 2021/day1.cpp 2021/day1.h 2015/day5.cpp 2015/day5.h)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/grabinputs.py)

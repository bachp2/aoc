//
//  aoc.h
//  advent_of_code
//
//  Created by Bach Phan on 12/23/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#ifndef aoc_h
#define aoc_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <memory.h>
#include <map>
typedef std::string String;
class aoc{
    struct Tower{
        int weight = 0;
        std::string name;
        int level = 0;
        std::shared_ptr<Tower> lower_tower_ptr;
        std::vector<std::shared_ptr<Tower>> upper_towers_ptrs;
        Tower(){}
        bool operator ==(const Tower& t){
            return this->weight == t.weight;
        }
    };
    
    enum Direction {right = 0, up, left, down};
public:
    void day1();
    void day2();
    void day3(int n);
    void day4();
    void day5();
    void day6();
    void day7();
    void day8();
    void day9();
    void day10();
private:
    Direction directions[4] = {right,up,left,down};
    int aux_check_ints_divisible(int a, int b);
    void get_direction(Direction d, int& y, int& x);
    void turn(Direction& d);
    void prevturn(Direction& d);
    bool is_within_boundary(int py, int px, int oy, int ox, int layer);
    bool is_duplicate(std::vector<std::string>& words);
    std::string get_state(std::vector<int>& ints);
    void day6_wrapper(std::vector<int>& ints);
    bool is_number(const std::string& s);//useful function!
    std::vector<std::string> getTowersAtLevel(std::map<std::string, std::shared_ptr<Tower>>& map,int level);
    int getStackWeight(std::shared_ptr<Tower> t, int &stackWeight);
    bool vcompare(const int& var, const int& num, const String &comp);
    void voperate(int& var, int num, const String &op);
};

#endif /* aoc_h */

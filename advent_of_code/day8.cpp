//
//  day8.cpp
//  advent_of_code
//
//  Created by Bach Phan on 12/28/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#include <stdio.h>
#include "aoc.h"
#include <map>

struct Variable{
    int value;
    String name;
    Variable(){
        value = 0;
        name = "";
    }
    Variable(String name){
        this->name = name;
        value = 0;
    }
    Variable(const Variable& var){
        this->name = var.name;
        this->value = var.value;
    }
};

void aoc::day8(){
    typedef std::map<String, Variable> MapVar;
    MapVar mapVar;
    std::ifstream inFile;
    inFile.open("day8_input.txt");
    if(!inFile.is_open()) std::cout << "Error\n";
    std::string line;
    int highest = 0;
    while( getline(inFile, line) ) {
        std::istringstream ls(line);
        std::string var1, op, cond, var2, comparator;
        int num1, num2;
        while (ls >> var1 >> op >> num1 >> cond >> var2 >> comparator >> num2) {
            if( mapVar.find(var1) == mapVar.end() ) mapVar[var1] = Variable(var1);
            if( mapVar.find(var2) == mapVar.end() ) mapVar[var2] = Variable(var2);
            if( vcompare(mapVar[var2].value, num2, comparator) ) {
                voperate(mapVar[var1].value, num1, op);
                if (mapVar[var1].value > highest) highest = mapVar[var1].value;
            }
        }
    }
    int max = 0;
    String maxVar;
    for (const auto& v : mapVar){
        if (v.second.value > max) {
            max = v.second.value;
            maxVar = v.first;
        }
    }
    //part1
    std::cout << max << ' ' << maxVar << std::endl;
    //part2
    std::cout << highest << std::endl;
}

bool aoc::vcompare(const int& var, const int& num, const String& comp){
    if(comp == "<") return var < num;
    else if(comp == ">") return var > num;
    else if(comp == ">=") return var >= num;
    else if(comp == "<=") return var <= num;
    else if(comp == "==") return var == num;
    else return var != num;
}

void aoc::voperate(int &var, int num, const String& op){
    if(op == "inc") var += num;
    else var -= num;
}

//
//  day9.cpp
//  advent_of_code
//
//  Created by Bach Phan on 12/28/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#include <stdio.h>
#include "aoc.h"

void aoc::day9(){
    int level(0), score(0), rubbish(0) ;
    char ch;
    bool ignore = false;
    std::fstream fin("day9_input.txt", std::fstream::in);
    while (fin >> std::noskipws >> ch) {
        if(ch == '!') {
            fin >> ch;
            continue;
        }
        else if(ch == '<') {
            if(ignore) rubbish++;
            ignore = true;
        }
        //else if(ch == '>' && !ignore) std::cout << "Error parsing" << std::endl;//test
        else if(ch == '>') {
            ignore = false;
        }
        else if(ignore) {
            rubbish++;
            continue;
        }
        
        if(ch == '{') level++;
        else if(ch == '}'){
            score += level;
            level--;
        }
    }
    std::cout << score << std::endl;
    std::cout << rubbish << std::endl;
}

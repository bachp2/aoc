//
//  day5.cpp
//  advent_of_code
//
//  Created by Bach Phan on 12/25/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#include <stdio.h>
#include "aoc.h"

void aoc::day5(){
    std::ifstream inFile;
    inFile.open("input_day5.txt");
    
    if(!inFile.is_open()) std::cout << "Error\n";
    
    std::vector<int16_t> ints;
    int16_t in;
    while( inFile >> in ) {
        ints.push_back(in);
    }
    
    int index = 0;
    int steps = 0;
    int tmp;
    while(index >= 0 && index < ints.size()){
        tmp = ints[index];
        if(ints[index]>=3) ints[index] -= 1;
        else ints[index] += 1;
        index += tmp;
        steps++;
    }
    std::cout << steps << std::endl;
    inFile.close();
}

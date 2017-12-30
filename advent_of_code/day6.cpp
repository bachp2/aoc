//
//  day6.cpp
//  advent_of_code
//
//  Created by Bach Phan on 12/25/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#include <stdio.h>
#include "aoc.h"
#include <set>
void aoc::day6(){
    std::ifstream inFile;
    inFile.open("input_day6.txt");
    
    if(!inFile.is_open()) std::cout << "Error\n";
    std::vector<int> testcase = {0,2,7,0};
    std::vector<int> ints;
    int in;
    while( inFile >> in ) {
        ints.push_back(in);
    }
    day6_wrapper(ints);
    inFile.close();
}

std::string aoc::get_state(std::vector<int> &ints){
    std::string state;
    for(int i = 0; i < ints.size(); i++){
        state.append(std::to_string(ints[i]));
        if(i!=ints.size()-1) state.append("-");
    }
    return state;
}
void aoc::day6_wrapper(std::vector<int> &ints){
    int cycles = 0;
    //for(auto c : ints) std::cout << c << ' ' << std::endl;
    std::set<std::string> states_container;
    //std::cout << ints.size() << std::endl;
    //std::cout << get_state(ints) << std::endl;
    //is_duplicate not good enough!
    size_t before = 0;
    size_t after = 1;
    std::string state;
    //part1
    while(before != after){
        before = states_container.size();
        size_t max_index = std::max_element( ints.begin(), ints.end() ) - ints.begin();
        int q = ints[max_index]/ints.size();
        unsigned long r = ints[max_index] - q*ints.size();
        ints[max_index] = 0;
        for(auto& i : ints){
            i += q;//distribute quotient evenly across banks
        }
        size_t i = max_index+1;
        //distribute the remainder;
        while(r > 0){
            if(i == ints.size()) i = 0;
            ints[i] += 1;
            i++;
            r--;
        }
        //std::cout << get_state(ints) << std::endl;
        state = get_state(ints);
        states_container.insert( state );
        after = states_container.size();//if succeed size will increment 1
        cycles++;
    }
    //part2
    cycles = 0;
    std::string new_state = " ";
    while(state!=new_state){
        size_t max_index = std::max_element( ints.begin(), ints.end() ) - ints.begin();
        int q = ints[max_index]/ints.size();
        unsigned long  r = ints[max_index] - q*ints.size();
        ints[max_index] = 0;
        for(auto& i : ints){
            i += q;//distribute quotient evenly across banks
        }
        size_t i = max_index+1;
        //distribute the remainder;
        while(r > 0){
            if(i == ints.size()) i = 0;
            ints[i] += 1;
            i++;
            r--;
        }
        //std::cout << get_state(ints) << std::endl;
        new_state = get_state(ints);
        //states_container.insert( new_state );
        cycles++;
    }
    std::cout << cycles << std::endl;
}


//
//  day7.cpp
//  advent_of_code
// 
//  Created by on 12/26/17.
//  Copyright © 2017. All rights reserved.
//

#include <stdio.h>
#include "aoc.h"
#include <map>
#include <memory.h>
#include <assert.h>

void aoc::day7(){
    //simplified input
    char ch;
    std::string content;
    std::fstream fin("input_day7.txt", std::fstream::in);
    while (fin >> std::noskipws >> ch) {
        if( isalnum(ch) ||  ch == ' ' || ch == '\n' || ch == '-' || ch == '>' )
            content += ch;
    }
    std::ofstream file;
    file.open("simplified_input_day7.txt");
    if(!file.is_open()) std::cout << "Error" << std::endl;
    file << content;
    file.close();
    
    //actual proccesing
    std::map< std::string, std::shared_ptr<Tower> > mapTowers;
    
    
    std::vector<std::string> towers_container;
    
    std::ifstream inFile;
    inFile.open("simplified_input_day7.txt");
    if(!inFile.is_open()) std::cout << "Error\n";
    std::string line;
    
    while( getline(inFile, line) ) {
        //std::cout << line << std::endl;
        std::string tower_name;//name of current tower
        std::string tmp;//string for checking purpose
        int weight = 0;
        int processingRef = 0;//check if we're processing list of upper towers
        
        std::istringstream ls(line);
        while(ls >> tmp)
        {
            //std::cout << weight;
            if(tmp == "->"){
                processingRef = 1;
            }
            else if(processingRef){
                towers_container.push_back(tmp);
            }
            else if(is_number(tmp)) weight = atoi(tmp.c_str());
            else {
                tower_name = tmp;
            }
            //std::cout << weight << ' ' << tower_name << std::endl;
        }
        //create tower structs
        if(mapTowers.find(tower_name) == mapTowers.end()){
            std::shared_ptr<Tower> tower_ptr(new Tower());
            mapTowers[tower_name] = tower_ptr;
            //mapTowers.emplace(tower_name, tower_ptr);
            //assert(mapTowers[tower_name] != nullptr);
            //assert(tower_ptr->level == 0);
            //tower_ptr->name = "abc";
            //assert(tower_ptr->name == "abc");
            tower_ptr.reset();
        }
        assert(mapTowers[tower_name] != nullptr);
        mapTowers[tower_name]->weight = weight;
        mapTowers[tower_name]->name = tower_name;
        mapTowers[tower_name]->level = 0;
        if(processingRef){
            for(const auto& t : towers_container){
                if(mapTowers.find(t) == mapTowers.end()){
                    std::shared_ptr<Tower> tower_ptr(new Tower());
                    mapTowers[t] = tower_ptr;
                    tower_ptr.reset();
                }
                mapTowers[t]->lower_tower_ptr = mapTowers[tower_name];
                mapTowers[tower_name]->upper_towers_ptrs.push_back(mapTowers[t]);
            }
        }
        
        //reset for new line
        towers_container.clear();
        //weight = 0;
    }
    
    for ( auto &t : mapTowers )
    {
        std::shared_ptr<Tower> next;
        std::shared_ptr<Tower> prev;
        if(t.second->lower_tower_ptr != nullptr){
            prev = t.second;
            next = t.second->lower_tower_ptr;
            //assert(prev->level <=10 );
            while(next!=nullptr){
                if(prev->level + 1 >= next->level)
                    next->level = prev->level + 1;
                prev = next;
                next = next->lower_tower_ptr;
            }
        }
    }
    //part1
//    int max_depth = 0;
//    std::string lowest_tower;
//    for (auto &t : mapTowers)
//    {
//        //std::cout << t.first << ' ' << t.second->weight << ' ' << t.second->level << std::endl;
//        if(t.second->level > max_depth) {
//            max_depth = t.second->level;
//            lowest_tower = t.first;
//        }
//    }
//    std::cout << lowest_tower << std::endl;
    //part2
    //std::cout << mapTowers["cvwsj"]->level << std::endl;
    std::vector<std::string> Towers1 = getTowersAtLevel(mapTowers, 1);
    for(const auto& t : Towers1){
        //get towers at zero from level 1
        std::vector<std::shared_ptr<Tower>> t0 = mapTowers[t]->upper_towers_ptrs;
        //for(const auto& i : t0) assert(i->level == 0);
        //for(const auto& i : t0) std::cout << i->weight << std::endl;
        for(const auto& tp : t0){
            if( tp->weight != t0[0]->weight ){
                std::cout << "imbalance at level 0" << std::endl;
                //std::cout << tp->name << ' ' << t0[0]->name << std::endl;
            }
        }
        //std::cout << std::endl;
    }
    std::shared_ptr<Tower> lowest_tower = mapTowers["fbgguv"];
    std::vector<std::shared_ptr<Tower>> second_lowest_towers =  lowest_tower->upper_towers_ptrs;
    //std::vector<int> stackWeights;
//    for(const auto& t : second_lowest_towers){
//        int stackWeight = 0;
//        //stackWeights.push_back(getStackWeight(t, stackWeight));
//        std::cout << getStackWeight(t, stackWeight) << std::endl;
//    }
    second_lowest_towers = second_lowest_towers[2]->upper_towers_ptrs;
//    for(const auto& t : second_lowest_towers){
//        int stackWeight = 0;
//        //stackWeights.push_back(getStackWeight(t, stackWeight));
//        std::cout << getStackWeight(t, stackWeight) << std::endl;
//    }
    second_lowest_towers = second_lowest_towers[4]->upper_towers_ptrs;
//    for(const auto& t : second_lowest_towers){
//        int stackWeight = 0;
//        //stackWeights.push_back(getStackWeight(t, stackWeight));
//        std::cout << getStackWeight(t, stackWeight) << std::endl;
//    }
    //second_lowest_towers = second_lowest_towers[2]->upper_towers_ptrs;
    for(const auto& t : second_lowest_towers){
        int stackWeight = 0;
        //stackWeights.push_back(getStackWeight(t, stackWeight));
        std::cout << getStackWeight(t, stackWeight) << std::endl;
    }
    const auto& wrongWeightTower = second_lowest_towers[2];
    std::cout << wrongWeightTower->weight << std::endl;
}
bool aoc::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

std::vector<std::string> aoc::getTowersAtLevel(std::map<std::string, std::shared_ptr<Tower>> &map,int level)
{
    std::vector<std::string> v;
    for(const auto &t : map){
        if(t.second->level == level){
            v.push_back(t.second->name);
        }
    }
    return v;
}
int aoc::getStackWeight(std::shared_ptr<Tower> t, int& stackWeight){
    stackWeight += t->weight;
    if(!t->upper_towers_ptrs.empty()){
        for( const auto& tp : t->upper_towers_ptrs){
            getStackWeight(tp, stackWeight);
        }
    }
    return stackWeight;
}

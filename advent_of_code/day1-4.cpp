//
//  day1.cpp
//  advent_of_code
//
//  Created by Bach Phan on 12/23/17.
//  Copyright © 2017 Bach Phan. All rights reserved.
//

#include "aoc.h"
void aoc::day1(){
    // insert code here...
    //advent of code day 1
    // part 1 1044
    // part 2
    std::string str = "111831362354551173134957758417849716877188716338227121869992652972154651632296676464285261171625892888598738721925357479249486886375279741651224686642647267979445939836673253446489428761486828844713816198414852769942459766921928735591892723619845983117283575762694758223956262583556675379533479458964152461973321432768858165818549484229241869657725166769662249574889435227698271439423511175653875622976121749344756734658248245212273242115488961818719828258936653236351924292251821352389471971641957941593141159982696396228218461855752555358856127582128823657548151545741663495182446281491763249374581774426225822474112338745629194213976328762985884127324443984163571711941113986826168921187567861288268744663142867866165546795621466134333541274633769865956692539151971953651886381195877638919355216642731848659649263217258599456646635412623461138792945854536154976732167439355548965778313264824237176152196614333748919711422188148687299757751955297978137561935963366682742334867854892581388263132968999722366495346854828316842352829827989419393594846893842746149235681921951476132585199265366836257322121681471877187847219712325933714149151568922456111149524629995933156924418468567649494728828858254296824372929211977446729691143995333874752448315632185286348657293395339475256796591968717487615896959976413637422536563273537972841783386358764761364989261322293887361558128521915542454126546182855197637753115352541578972298715522386683914777967729562229395936593272269661295295223113186683594678533511783187422193626234573849881185849626389774394351115527451886962844431947188429195191724662982411619815811652741733744864411666766133951954595344837179635668177845937578575117168875754181523584442699384167111317875138179567939174589917894597492816476662186746837552978671142265114426813792549412632291424594239391853358914643327549192165466628737614581458189732579814919468795493415762517372227862614224911844744711698557324454211123571327224554259626961741919243229688684838813912553397698937237114287944446722919198743189848428399356842626198635297851274879128322358195585284984366515428245928111112613638341345371";
    std::vector<int> integers;
    int integer;
    for(char& c : str){
        integer = c - '0';
        integers.push_back(integer);
    }
    std::int16_t sum = 0;
    std::int16_t half_length = integers.size()/2;
    for(int i = 0; i < half_length; i++){
//        if(i == integers.size() - 1 && integers[i] == integers[0]){
//            sum += integers[i];
//        }
//        else if(integers[i] == integers[i+1]){
//            sum += integers[i];
//        }
        if(integers[i] == integers[half_length + i])
            sum += 2*integers[i];
    }
    for (std::vector<int>::const_iterator i = integers.begin(); i != integers.end(); ++i)
        std::cout << *i << ' ';
    std::cout << '\n';
    std::cout << "capcha: " << sum << '\n';
}

void aoc::day2(){
    std::ifstream inFile;
    inFile.open("spreadsheet.txt");
    
    if(!inFile) std::cout << "Error\n";
    
    std::string line;
    std::vector<int32_t> ints;
    std::int32_t sum = 0;
    //int32_t max, min, diff;
    int32_t in;
    while( getline(inFile, line) ) {
        //std::cout << line;
        std::istringstream ls(line);
        while(ls >> in)
        {
            ints.push_back(in);
        }
//        max = *std::max_element(std::begin(ints), std::end(ints));
//        min = *std::min_element(std::begin(ints), std::end(ints));
//        diff = max - min;
//        std::cout << max << " " << min << " " << diff << std::endl;
//        sum += diff;
        std::int16_t div;
        for(int i = 0; i < ints.size()-1; i++){
            for(int j = i+1; j < ints.size(); j++){
                div = aux_check_ints_divisible(ints[i], ints[j]);
                if(div){
                    sum += div;
                }
            }
        }
        ints.clear();
    }
    std::cout << "\ncapcha " << sum << '\n';
    inFile.close();
}

int aoc::aux_check_ints_divisible(int a, int b){
    int tmp;
    if(a < b){
        tmp = b/a;
        if(tmp*a != b) return 0;
        else return tmp;
    }
    else if(a>b){
        tmp = a/b;
        if(tmp*b != a) return 0;
        else return tmp;
    }
    return 1;
}

void aoc::day3(int n){
    int side = sqrt(n);
    if(side%2 == 0) side += 1;
    else if(side*side != n && side%2 == 1) side += 2;
    //std::cout << side << '\n';
    //part2
    int matrix[side][side];
    int curr;
    int oy = side/2;
    int ox = side/2;
    int pos[2] = {oy, ox};
    matrix[oy][ox] = 1;
    curr = 1;
    Direction d = Direction::right;
    int dy = 0;
    int dx = 0;
    int layer = 1;
    while(curr < n){
        get_direction(d, dy, dx);
        int tmpy = pos[0];
        int tmpx = pos[1];
        tmpy += dy;
        tmpx += dx;
        if(is_within_boundary(tmpy, tmpx, oy, ox, layer) && matrix[tmpy][tmpx] == 0){
            pos[0] = tmpy;
            pos[1] = tmpx;
            int sum = 0;
            for(int j = pos[0]-1; j <= pos[0]+1; ++j){
                for(int i = pos[1]-1; i <= pos[1]+1; ++i){
                    sum += matrix[j][i];
                }
            }
            matrix[pos[0]][pos[1]] = sum;
            curr = sum;
        }
        else if (is_within_boundary(tmpy, tmpx, oy, ox, layer) && matrix[tmpy][tmpx] != 0){
            prevturn(d);
            layer++;
        }
        else{
            turn(d);
        }
    }
    std::cout << curr;
    //part1
    //    int steps = side/2;//steps to penetrate the layers
    //    //std::cout << (side-1)^2;
    //    int cpoint1 = (int) pow(side-2, 2) + (side+1)/2;
    //    int cpoints [4] = {cpoint1};
    //    for(int i=1; i<4; i++){
    //        cpoints[i] = cpoints[i-1]+side-1;
    //    }
    //    std::vector<int> diff(4);
    //    std::cout << cpoints[0] << " " << cpoints[1] << " " << cpoints[2] << " " << cpoints[3] << '\n';
    //    for(int i=0; i<4; i++){
    //        diff[i] = cpoints[i] - n;
    //        if(diff[i]<0) diff[i] *= -1;
    //    }
    //    for (std::vector<int>::const_iterator i = diff.begin(); i != diff.end(); ++i)
    //        std::cout << *i << ' ';
    //    int min = *std::min_element(std::begin(diff), std::end(diff));
    //    steps += min+1;//steps to reallign to the centerpoint
    //    std::cout << '\n' << steps <<std::endl;
}
void aoc::get_direction(aoc::Direction d, int& y, int& x){
    switch(d){
        case aoc::Direction::right : y = 0; x = 1; break;
        case aoc::Direction::left : y = 0; x = -1; break;
        case aoc::Direction::up : y = 1; x = 0; break;
        case aoc::Direction::down : y = -1; x = 0; break;
    }
}

void aoc::turn(aoc::Direction& d){
    int i = static_cast<int>(d);
    if(i == 3) d = directions[0];
    else d = directions[i+1];
}
void aoc::prevturn(aoc::Direction& d){
    int i = static_cast<int>(d);
    if(i == 0) d = directions[3];
    else d = directions[i-1];
}
bool aoc::is_within_boundary(int py, int px, int oy, int ox, int nlayer){
    int rel_disty = py-oy;
    int rel_distx = px-oy;
    if(rel_disty < 0) rel_disty *= -1;
    if(rel_distx < 0) rel_distx *= -1;
    if(rel_disty > nlayer || rel_distx > nlayer) return false;
    return true;
}

void aoc::day4(){
    std::ifstream inFile;
    //inFile.open("input_day4.txt");
    inFile.open("simplified_input_day7.txt");
    if(!inFile.is_open()) std::cout << "Error\n";
    int passes = 0;
    std::string line;
    int i;
    std::vector<std::string> words;
    std::string in;
    while( getline(inFile, line) ) {
        //std::cout << line;
        std::istringstream ls(line);
        while(ls >> in >> i)
        {
            //std::cout << in;
            words.push_back(in);
        }
        std::cout << in;
        for (std::vector<std::string>::iterator iw = words.begin(); iw != words.end(); ++iw){
            std::sort((*iw).begin(), (*iw).end());
        }
        if(!is_duplicate(words)){
            passes++;
//            for (std::vector<std::string>::iterator iw = words.begin(); iw != words.end(); ++iw){
//                std::cout << *iw << ' ';
//            }
        }
        words.clear();
        std::cout << '\n';
    }
    std::cout << "count " << passes << '\n';
    inFile.close();
}

bool aoc::is_duplicate(std::vector<std::string> &words){
    for(int i = 0; i < words.size(); ++i){
        for(int j = i+1; j < words.size(); ++j){
            if(words[i].compare(words[j]) == 0) return true;
        }
    }
    return false;
}

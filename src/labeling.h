#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define BRANCH_NUM 21

std::vector<std::string> stringSplitter(std::string &line, char splitter){
    std::string tmpString;
    std::vector<std::string> seglist;
    std::stringstream lineStream;
    lineStream.str(line);
    while(std::getline(lineStream, tmpString, splitter)){
        seglist.push_back(tmpString);
    }
    return seglist;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to){
    size_t startPos = 0;
    std::string space = " ";
    std::string doubleDot = ":";
    std::string tag = "#";

    while((startPos = str.find(from, startPos)) != std::string::npos){
        str.replace(startPos, from.length(), to);
        if(startPos == 0 && str.at(0) == space.at(0))
            str.replace(startPos, space.length(), "");
        startPos += to.length();
    }
    
    str.shrink_to_fit();

    return str;
}

bool labelExist(std::vector<std::string> &usedLabels, std::string &PcToCheck){
    bool finded = false;
    for(int i = 0; i<usedLabels.size() && !finded; i++)
        if(PcToCheck == usedLabels.at(i))
            finded = true;
    return finded;
}

bool isBranch(const char* branches[], std::string &instructionToCheck){
    bool finded = false;
    for(int i = 0; i<BRANCH_NUM && !finded; i++)
        if(instructionToCheck == branches[i])
            finded = true;
    return finded;
}

std::vector<std::string> labeling(std::vector<std::string> buff){
    const char* branch[BRANCH_NUM] = {"BRCC", "BRCS", "BRGE", "BRHC", "BRHS", "BRID", "BRIE", "BRLT", "BRMI", "BRNE", "BRPL", "BRSH", "BRTC", "BRTS", "BRVC", "BRVS", "BREQ", "CALL", "RCALL", "JMP", "RJMP"};
    
    std::vector<std::string> usedProgramCounters;

    for (auto& e : buff){
        std::vector<std::string> seglist = stringSplitter(e, '#'); // PC # instruction
        std::string pc = seglist.at(0);
        std::vector<std::string> instruction = stringSplitter(seglist.at(1), '_'); // instruction _ operands
        if(isBranch(branch, instruction.at(0))){
                std::string k;
                if (instruction.at(1).at(0) == '0' && instruction.at(1).length() > 1){
                    k = instruction.at(1);
                }
                else {
                    int offset = std::stoi(instruction.at(1), nullptr, 10) + 1;
                    int instructionPC = std::stoi(pc, nullptr, 16);
                    k = std::format("{:#06X}", instructionPC + (offset*2));
                }
                if (!labelExist(usedProgramCounters, k)) {
                    usedProgramCounters.push_back(k);
            }
            e = replaceAll(e, "_" + instruction.at(1), k);
        }
    }
    #ifndef DEBUG
    for (auto& e : buff) {
        for (int i = 0; i < usedProgramCounters.size(); i++) {
            e = replaceAll(e, usedProgramCounters.at(i), " label" + std::to_string(i) + ":");
            if (e.at(0) == 'l') {
                e = replaceAll(e, ":#", "#");
            }
            if (e.at(e.length() - 1) == ':')
                e = replaceAll(e, ":", "");
            if (e.at(0) == 'l')
                e = replaceAll(e, "#", ": ");
        }
        if (stringSplitter(e, '#').at(0).at(0) == '0') e = replaceAll(e, stringSplitter(e, '#').at(0) + '#', "");
    }
    #endif
    #ifdef DEBUG
    for (auto& e : usedProgramCounters) {
        printf("%s\n", e.c_str());
    }
    #endif

    return buff;
}
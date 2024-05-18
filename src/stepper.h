#pragma once

#include <vector>
#include <bitset>
#include <string>
#include <format>

std::string buff = "";
int programCounter = -2;

std::string getProgramCounter(){
		programCounter += 2;

	return std::format("{:#06X}#", programCounter);
}

bool programCounterStepper(std::bitset<4>* opcode16bit) {
	static int buffIterator = 0;

	if (!(buffIterator < buff.length()))
		return false;

	std::string opcodeString;
	for (int j = 0; j < 16; j++)
		opcodeString += buff.at(buffIterator + j);
	std::string tmp;
	for (int y = 0, x = 0; y < opcodeString.length(); y++) {
		if (y % 4 == 0 && y != 0) {
			opcode16bit[x] = std::bitset<4>(tmp); x++;
			tmp.clear();
		}
		tmp += opcodeString.at(y);
	}

	opcode16bit[3] = std::bitset<4>(tmp); tmp.clear(); opcodeString.clear();

	buffIterator += 16;

	return true;
}
//this program has as input a .hex file and returns only the data sector (00 as record type)
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <string>
#include "instruction_decoder.h"
#include "stepper.h"
#include "labeling.h"


#ifdef GUI
#include "disassemblerHeader.h"
#endif

static std::vector<std::string> _readFile(std::string filePath);
static std::string _extractData(std::string &hexLine);
static std::string _toBigEndian(std::string littleEndianData);
static std::vector<std::string> _formatter(std::vector<std::string>& extractedDataLines);
static void _toBinaryElements(std::vector<std::string> &formattedInstructions);
std::vector<std::string> decodeInstruction(std::vector<std::string> bufferToDecode);

#ifndef GUI
std::string getFilePath() {
	std::string filePath;
	printf("Insert the .hex absulute path ->");
	std::cin >> filePath;

	if (!(std::filesystem::path(filePath).string().ends_with(".hex") && std::filesystem::exists(filePath)))
		throw std::invalid_argument("Invalid argument: Argument does not terminate with .hex, is not a file, or does not exists");
	return filePath;
}
#endif


#ifdef DEBUG
void readBuffer(std::vector<std::string> buff) {
	for (int i = 0; i < buff.size(); i++)
		printf("%s\n", buff.at(i).c_str());
}

int main(int argc, char* argv[]) {
	if (argc > 1 && std::filesystem::path(argv[argc - 1]).string().ends_with(".hex"))
		readBuffer(labeling(decodeInstruction(_readFile(argv[argc - 1]))));
	else if (argc == 1) {
		try {
			readBuffer(labeling(decodeInstruction(_readFile(getFilePath()))));
		}
		catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
	}
	return 0;
}

#endif

#ifdef NOGUI
void writeBuffer(std::vector<std::string> buff, std::string path) {
	std::ofstream output(std::filesystem::path(path).replace_extension(".asm").string());
	for (auto& e : buff) {
		output << e << std::endl;
	}
	buff.pop_back(); // removes the empty line
}

int main(int argc, char* argv[]) {
	std::string filePath = argv[argc - 1];

	if (argc > 1 && std::filesystem::path(filePath).string().ends_with(".hex"))
		writeBuffer(labeling(decodeInstruction(_readFile(filePath))), filePath);
	else if (argc == 1) {
		try {
			filePath = getFilePath();
		}catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
		writeBuffer(labeling(decodeInstruction(_readFile(filePath))), filePath);	
	}
	return 0;
}
#endif

#ifdef GUI
void writeTempBuffer(std::vector<std::string> buff, std::string path) {
	std::ofstream output(std::filesystem::path(path).replace_extension(".asm").string());
	for (auto& e : buff) output << e << std::endl;
}
void disassemble(std::string path) {
	std::vector<std::string> disassembledFileBuffer = labeling(decodeInstruction(_readFile(path)));
	writeTempBuffer(disassembledFileBuffer, path);
}
#endif

std::vector<std::string> _readFile(std::string filePath) {
	std::vector<std::string> fileBuffer;
	std::string fileContentLine;
	std::ifstream fileHex;
	
	try{
		fileHex.open(filePath);

		while (getline(fileHex, fileContentLine)) {
			if (fileContentLine.at(7) == fileContentLine.at(8) && fileContentLine.at(7) == '0')
				fileBuffer.push_back(_toBigEndian(_extractData(fileContentLine)));
		}
	}catch(std::ifstream::failure &e){
		std::cerr << "\n\nException occured when reading a file: \n"
			<< e.what()
			<< std::endl;
		exit(-1);
	}

	std::vector<std::string> outputBuffer = _formatter(fileBuffer);
	_toBinaryElements(outputBuffer);

	return outputBuffer;
}

std::string _extractData(std::string& hexLine) {
	std::string onlyData;
	for (int i = 9; i < hexLine.size() - 2; i++)
		onlyData += hexLine.at(i);
	return onlyData;
}


std::string _toBigEndian(std::string littleEndianData) {
	std::string bigEndianLine;

	for (int i = 0; i < littleEndianData.size(); i += 4) {
		bigEndianLine += littleEndianData[i + 2];
		bigEndianLine += littleEndianData[i + 3];
		bigEndianLine += littleEndianData[i];
		bigEndianLine += littleEndianData[i + 1];
	}

	return bigEndianLine;
}

std::vector<std::string> _formatter(std::vector<std::string> &extractedDataLines) {
	std::vector<std::string> outputFormattedInstructions;
	for (auto& e : extractedDataLines) {
		std::string tmp;
		for (int i = 0; i < e.size(); i++) {
			if (i % 4 == 0 && i != 0) {
				outputFormattedInstructions.push_back(tmp);
				tmp.clear();
			}
			tmp += e.at(i);
		}
		outputFormattedInstructions.push_back(tmp); tmp.clear();
	}
	extractedDataLines.clear();

	return outputFormattedInstructions;
}

void _toBinaryElements(std::vector<std::string> &formattedInstructions) {
	for (auto& e : formattedInstructions) {
		e = std::bitset<16>(std::stoul(e, nullptr, 16)).to_string();
	}
}

std::vector<std::string> decodeInstruction(std::vector<std::string> bufferToDecode) {
	std::vector<std::string> output;

	for (auto& e : bufferToDecode)
		buff += e;

	std::bitset<4> opcode16bit[4]; 
	
	while(programCounterStepper(opcode16bit)){
		switch (opcode16bit[0].to_ulong()) {
		case 0b0000: output.push_back(getProgramCounter() + decodeOpcode0000(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0001: output.push_back(getProgramCounter() + decodeOpcode0001(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0010: output.push_back(getProgramCounter() + decodeOpcode0010(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0011: output.push_back(getProgramCounter() + decodeOpcode0011(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0100: output.push_back(getProgramCounter() + decodeOpcode0100(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0101: output.push_back(getProgramCounter() + decodeOpcode0101(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0110: output.push_back(getProgramCounter() + decodeOpcode0110(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b0111: output.push_back(getProgramCounter() + decodeOpcode0111(opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1000: output.push_back(getProgramCounter() + decodeOpcode1000(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1001: output.push_back(getProgramCounter() + decodeOpcode1001(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1010: output.push_back(getProgramCounter() + decodeOpcode1010(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1011: output.push_back(getProgramCounter() + decodeOpcode1011(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1100: output.push_back(getProgramCounter() + decodeOpcode1100(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1101: output.push_back(getProgramCounter() + decodeOpcode1101(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1110: output.push_back(getProgramCounter() + decodeOpcode1110(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		case 0b1111: output.push_back(getProgramCounter() + decodeOpcode1111(opcode16bit[0], opcode16bit[1], opcode16bit[2], opcode16bit[3])); break;
		}
		if (was32bit) {
			getProgramCounter(); was32bit = false;
		}
			
	}
	return output;
}
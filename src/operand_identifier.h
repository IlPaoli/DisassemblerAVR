#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <string>
#include <format>

#include "stepper.h"

bool was32bit = false;

std::string NOP() { return "NOP"; }
std::string MOVW(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "MOVW r";
	output += std::to_string(b3.to_ulong() << 1);
	output += ",r";
	output += std::to_string(b4.to_ulong() << 1);
	return output;
} 
std::string MULS(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "MULS r";
	output += std::to_string(b3.to_ulong() + 16);
	output += ",r";
	output += std::to_string(b4.to_ulong() + 16);
	return output;
}
std::string MULSU(std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "MULSU r";
	b3 <<= 1;
	b3 >>= 1;
	b4 <<= 1;
	b4 >>= 1;
	output += std::to_string(b3.to_ulong()+16);
	output += ",r";
	output += std::to_string(b4.to_ulong()+16);
	return output;
}
std::string FMUL(std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "FMUL r";
	b3 <<= 1;
	b3 >>= 1;
	b4 <<= 1;
	b4 >>= 1;
	output += std::to_string(b3.to_ulong()+16);
	output += ",r";
	output += std::to_string(b4.to_ulong()+16);
	return output;
}
std::string FMULS(std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "FMULS r";
	b3 <<= 1;
	b3 >>= 1;
	b4 <<= 1;
	b4 >>= 1;
	output += std::to_string(b3.to_ulong()+16);
	output += ",r";
	output += std::to_string(b4.to_ulong()+16);
	return output;
}
std::string FMULSU(std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "FMULSU r";
	b3 <<= 1;
	b3 >>= 1;
	b4 <<= 1;
	b4 >>= 1;
	output += std::to_string(b3.to_ulong()+16);
	output += ",r";
	output += std::to_string(b4.to_ulong()+16);
	return output;
}
std::string CPC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CPC r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();
	
	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string SBC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBC r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string ADD(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	if (firstOperand.to_ulong() == secondOperand.to_ulong()) {
		output = "LSL r";
		output += std::to_string(firstOperand.to_ulong());
	}else {
		output = "ADD r";
		output += std::to_string(firstOperand.to_ulong());
		output += ",r";
		output += std::to_string(secondOperand.to_ulong());
	}
		
	return output;
}
std::string CPSE(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CPSE r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string CP(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CP r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string SUB(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SUB r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string ADC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	if (firstOperand.to_ulong() == secondOperand.to_ulong()) {
		output = "ROL r";
		output += std::to_string(firstOperand.to_ulong());
	}
	else {
		output = "ADC r";
		output += std::to_string(firstOperand.to_ulong());
		output += ",r";
		output += std::to_string(secondOperand.to_ulong());
	}

	return output;
}
std::string AND(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	if (firstOperand.to_ulong() == secondOperand.to_ulong()) {
		output = "TST r";
		output += std::to_string(firstOperand.to_ulong());
	}
	else {
		output = "AND r";
		output += std::to_string(firstOperand.to_ulong());
		output += ",r";
		output += std::to_string(secondOperand.to_ulong());
	}

	return output;
}
std::string EOR(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	if (firstOperand.to_ulong() == secondOperand.to_ulong()) {
		output = "CLR r";
		output += std::to_string(firstOperand.to_ulong());
	}
	else {
		output = "EOR r";
		output += std::to_string(firstOperand.to_ulong());
		output += ",r";
		output += std::to_string(secondOperand.to_ulong());
	}

	return output;
}
std::string OR(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "OR r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string MOV(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "MOV r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string CPI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CPI r";

	std::bitset<4> firstOperand;
	std::bitset<8> secondOperand;

	std::string tmpString = "";
	
	firstOperand = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	secondOperand = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(firstOperand.to_ulong() + 16);
	output += ", ";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string SBCI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBCI r";

	std::bitset<4> firstOperand;
	std::bitset<8> secondOperand;

	std::string tmpString = "";

	firstOperand = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	secondOperand = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(firstOperand.to_ulong() + 16);
	output += ", ";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string SUBI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SUBI r";

	std::bitset<4> firstOperand;
	std::bitset<8> secondOperand;

	std::string tmpString = "";

	firstOperand = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	secondOperand = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(firstOperand.to_ulong() + 16);
	output += ", ";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string ORI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "ORI r";

	std::bitset<4> firstOperand;
	std::bitset<8> secondOperand;

	std::string tmpString = "";

	firstOperand = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	secondOperand = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(firstOperand.to_ulong() + 16);
	output += ", ";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string ANDI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "ANDI r";

	std::bitset<4> firstOperand;
	std::bitset<8> secondOperand;

	std::string tmpString = "";

	firstOperand = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	secondOperand = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(firstOperand.to_ulong() + 16);
	output += ", ";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string LD(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> operandD;
	std::bitset<6> operandQ;
	
	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();
	tmpString.push_back(b1.to_string().at(2));
	tmpString.push_back(b2.to_string().at(0));
	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandQ = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	int stat0 = b1[0];
	int	stat1 = b4[3];
	int stat2 = operandQ.to_ulong();


	if (stat0 == 0 && stat2 >= 2)
		output = "LDD r";
	else
		output = "LD r";
	
	output += std::to_string(operandD.to_ulong());
	output += ",";
	
	if (output.at(2) == 'D') {
		if (stat1 == 0)
			output += "Z+";
		else
			output += "Y+";
		output.append(std::to_string(stat2));
	} else {
		switch (b4.to_ulong()) {
		case 0b0000: output += "Z"; break;
		case 0b0001: output += "Z+"; break;
		case 0b0010: output += "-Z"; break;
		case 0b1000: output += "Y"; break;
		case 0b1001: output += "Y+"; break;
		case 0b1010: output += "-Y"; break;
		case 0b1100: output += "X"; break;
		case 0b1101: output += "X+"; break;
		case 0b1110: output += "-X"; break;
		}
	}
	return output;
}
std::string ST(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output;
	std::bitset<5> operandD;
	std::bitset<6> operandQ;

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();
	tmpString.push_back(b1.to_string().at(2));
	tmpString.push_back(b2.to_string().at(0));
	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandQ = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	int stat0 = b1[0];
	int	stat1 = b4[3];
	int stat2 = operandQ.to_ulong();

	if (stat0 == 0 && stat2 >= 2)
		output = "STD r";
	else
		output = "ST r";

	output += std::to_string(operandD.to_ulong());
	output += ",";

	if (output.at(2) == 'D') {
		if (stat1 == 0)
			output += "Z+";
		else
			output += "Y+";
		output.append(std::to_string(stat2));
	}
	else {
		switch (b4.to_ulong()) {
		case 0b0000: output += "Z"; break;
		case 0b0001: output += "Z+"; break;
		case 0b0010: output += "-Z"; break;
		case 0b1000: output += "Y"; break;
		case 0b1001: output += "Y+"; break;
		case 0b1010: output += "-Y"; break;
		case 0b1100: output += "X"; break;
		case 0b1101: output += "X+"; break;
		case 0b1110: output += "-X"; break;
		}
	}
	return output;
}
std::string MUL(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "MUL r";
	std::bitset<5> firstOperand;
	std::bitset<5> secondOperand;

	std::string tmpString = "";

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	firstOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();

	tmpString.push_back(b2.to_string().at(2)); tmpString.append(b4.to_string());
	secondOperand = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	tmpString.clear();
	
	output += std::to_string(firstOperand.to_ulong());
	output += ",r";
	output += std::to_string(secondOperand.to_ulong());

	return output;
}
std::string LDS32(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "LDS ";

	std::bitset<4> second16bitOpcode[4];
	programCounterStepper(second16bitOpcode);
	
	std::bitset<5> operandD;
	std::bitset<16> operandK;

	{
		std::string tmpString;
		tmpString.push_back(b2.to_string().at(3));
		tmpString.append(b3.to_string());
		operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
		tmpString.clear();

		for(int i = 0; i < 4; i++)
			tmpString.append(second16bitOpcode[i].to_string());
		operandK = std::bitset<16>(std::stoul(tmpString, nullptr, 2));
	}

	output += "r";
	output += std::to_string(operandD.to_ulong());
	output += std::format(",${:X}", operandK.to_ulong());
	was32bit = true;

	return output;
}
std::string LPM(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "LPM ";

	std::string tmpString; 
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	switch (b4.to_ulong()) {
	case 0b0100: output += "r"; output += std::to_string(operandD.to_ulong()); output += ",Z"; break;
	case 0b0101: output += "r"; output += std::to_string(operandD.to_ulong()); output += ",Z+"; break;
	}

	return output;
}
std::string ELPM(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "ELPM ";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	switch (b4.to_ulong()) {
	case 0b0110: output += "r"; output += std::to_string(operandD.to_ulong()); output += ",Z"; break;
	case 0b0111: output += "r"; output += std::to_string(operandD.to_ulong()); output += ",Z+"; break;
	}

	return output;
}
std::string POP(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "POP r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string STS32(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "STS ";

	std::bitset<4> second16bitOpcode[4];
	programCounterStepper(second16bitOpcode);
	
	std::bitset<5> operandD;
	std::bitset<16> operandK;

	{
		std::string tmpString;
		tmpString.push_back(b2.to_string().at(3));
		tmpString.append(b3.to_string());
		operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
		tmpString.clear();

		for(int i = 0; i < 4; i++)
			tmpString.append(second16bitOpcode[i].to_string());
		operandK = std::bitset<16>(std::stoul(tmpString, nullptr, 2));
	}

	output += std::format("${:X},", operandK.to_ulong());
	output += "r";
	output += std::to_string(operandD.to_ulong());
	was32bit = true;

	return output;
}
std::string XCH(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "XCH Z,r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string LAS(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "LAS Z,r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string LAC(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "LAC Z,r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string LAT(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "LAS Z,r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string PUSH(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "PUSH r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string JUMP(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "JMP_";

	std::bitset<4> second16bitOpcode[4];
	programCounterStepper(second16bitOpcode);
	std::bitset<26> operandK;

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(3));
	
	tmpString.append(second16bitOpcode[0].to_string());
	tmpString.append(second16bitOpcode[1].to_string());
	tmpString.append(second16bitOpcode[2].to_string());
	tmpString.append(second16bitOpcode[3].to_string());

	operandK = std::bitset<26>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:#06X}", operandK.to_ullong() * 2);
	was32bit = true;
	
	return output;
}
std::string CALL(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CALL_";

	std::bitset<4> second16bitOpcode[4];
	programCounterStepper(second16bitOpcode);
	std::bitset<26> operandK;

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(3));
	
	tmpString.append(second16bitOpcode[0].to_string());
	tmpString.append(second16bitOpcode[1].to_string());
	tmpString.append(second16bitOpcode[2].to_string());
	tmpString.append(second16bitOpcode[3].to_string());

	operandK = std::bitset<26>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:#06X}", operandK.to_ullong() * 2);
	was32bit = true;

	return output;
}
std::string COM(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "COM r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string NEG(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "NEG r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string SWAP(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "SWAP r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string INC(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "INC r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string ASR(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "ASR r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string LSR(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "LSR r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string ROR(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "ROR r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string DEC(std::bitset<4> b2, std::bitset<4> b3) {
	std::string output = "DEC r";

	std::string tmpString;
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());

	std::bitset<5> operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());

	return output;
}
std::string SEC() {
	return "SEC";
}
std::string SEZ() {
	return "SEZ";
}
std::string SEN() {
	return "SEN";
}
std::string SEV() {
	return "SEV";
}
std::string SES() {
	return "SES";
}
std::string SEH() {
	return "SEH";
}
std::string SET() {
	return "SET";
}
std::string SEI() {
	return "SEI";
}
std::string CLC() {
	return "CLC";
}
std::string CLZ() {
	return "CLZ";
}
std::string CLN() {
	return "CLN";
}
std::string CLV() {
	return "CLV";
}
std::string CLS() {
	return "CLS";
}
std::string CLH() {
	return "CLH";
}
std::string CLT() {
	return "CLT";
}
std::string CLI() {
	return "CLI";
}
std::string IJMP() {
	return "IJMP";
}
std::string EIJMP() {
	return "EIJMP";
}
std::string DES(std::bitset<4> b3) {
	std::string output = "DES 0x0";

	output += std::format("{:X}", b3.to_ulong());

	return output;
}
std::string RET() {
	return "RET";
}
std::string RETI() {
	return "RETI";
}
std::string SLEEP() {
	return "SLEEP";
}
std::string BREAK() {
	return "BREAK";
}
std::string WDR() {
	return "WDR";
}
std::string SPM() {
	return "SPM";
}
std::string ICALL() {
	return "ICALL";
}
std::string EICALL() {
	return "EICALL";
}
std::string ADIW(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "ADIW r";
	std::string tmpString;

	std::bitset<6> operandK;
	std::bitset<2> tmpOperandD;
	int operandD;

	tmpString.push_back(b3.to_string().at(0)); 
	tmpString.push_back(b3.to_string().at(1));
	tmpString.append(b4.to_string());
	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b3.to_string().at(2));
	tmpString.push_back(b3.to_string().at(3));
	tmpOperandD = std::bitset<2>(std::stoul(tmpString, nullptr, 2));

	switch (tmpOperandD.to_ulong()) {
	case 0b00: operandD = 24; break;
	case 0b01: operandD = 26; break;
	case 0b10: operandD = 28; break;
	case 0b11: operandD = 30; break;
	}

	output += std::to_string(operandD + 1);
	output += ":r";
	output += std::to_string(operandD);
	output += ",";
	output += std::to_string(operandK.to_ulong());

	return output;
}
std::string SBIW(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBIW r";
	std::string tmpString;

	std::bitset<6> operandK;
	std::bitset<2> tmpOperandD;
	int operandD;

	tmpString.push_back(b3.to_string().at(0));
	tmpString.push_back(b3.to_string().at(1));
	tmpString.append(b4.to_string());
	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b3.to_string().at(2));
	tmpString.push_back(b3.to_string().at(3));
	tmpOperandD = std::bitset<2>(std::stoul(tmpString, nullptr, 2));

	switch (tmpOperandD.to_ulong()) {
	case 0b00: operandD = 24; break;
	case 0b01: operandD = 26; break;
	case 0b10: operandD = 28; break;
	case 0b11: operandD = 30; break;
	}

	output += std::to_string(operandD + 1);
	output += ":r";
	output += std::to_string(operandD);
	output += ",";
	output += std::to_string(operandK.to_ulong());

	return output;
}
std::string CBI(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "CBI $";
	std::string tmpString;

	std::bitset<5> operandA;
	std::bitset<3> operandB;

	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));
	operandA = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:X}", operandA.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string SBIC(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBIC $";
	std::string tmpString;

	std::bitset<5> operandA;
	std::bitset<3> operandB;

	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));
	operandA = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:X}", operandA.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string SBI(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBI $";
	std::string tmpString;

	std::bitset<5> operandA;
	std::bitset<3> operandB;

	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));
	operandA = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:X}", operandA.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string SBIS(std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBIS $";
	std::string tmpString;

	std::bitset<5> operandA;
	std::bitset<3> operandB;

	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));
	operandA = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:X}", operandA.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string LDS16(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "LDS r";
	std::string tmpString;

	std::bitset<7> operandK;

	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	tmpString.append(b4.to_string());
	operandK = std::bitset<7>(std::stoul(tmpString, nullptr, 2));


	output += std::to_string(b3.to_ulong() + 16);
	output += ",$";
	output += std::format("{:X}", operandK.to_ulong());

	return output;
}
std::string STS16(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "LDS r";
	std::string tmpString;

	std::bitset<7> operandK;

	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	tmpString.append(b4.to_string());
	operandK = std::bitset<7>(std::stoul(tmpString, nullptr, 2));


	output += std::to_string(b3.to_ulong() + 16);
	output += ",$";
	output += std::format("{:X}", operandK.to_ulong());

	return output;
}
std::string IN(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "IN r";
	std::string tmpString;

	std::bitset<6> operandA;
	std::bitset<5> operandD;

	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b2.to_string().at(2));
	tmpString.append(b4.to_string());
	operandA = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());
	output += ",$";
	output += std::format("{:X}", operandA.to_ulong());

	return output;
}
std::string OUT(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "OUT $";
	std::string tmpString;

	std::bitset<6> operandA;
	std::bitset<5> operandR;

	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b2.to_string().at(2));
	tmpString.append(b4.to_string());
	operandA = std::bitset<6>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	operandR = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	output += std::format("{:X}", operandA.to_ulong());
	output += ",r";
	output += std::to_string(operandR.to_ulong());
	
	return output;
}
std::string RJMP(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4){
	std::string output = "RJMP_";
	std::string tmpString;
	std::bitset<11> operandK;

	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b2.to_string().at(2));
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.append(b4.to_string());

	operandK = std::bitset<11>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string RCALL(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "RCALL_";
	std::string tmpString;
	std::bitset<11> operandK;

	tmpString.push_back(b2.to_string().at(1));
	tmpString.push_back(b2.to_string().at(2));
	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.append(b4.to_string());

	operandK = std::bitset<11>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string SER(std::bitset<4> b3) {
	std::string output = "SER r";

	output += std::to_string(b3.to_ulong() + 16);

	return output;
}
std::string LDI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "LDI r";

	std::bitset<4> operandD;
	std::bitset<8> operandR;

	std::string tmpString = "";

	operandD = b3;
	tmpString.append(b2.to_string());
	tmpString.append(b4.to_string());

	operandR = std::bitset<8>(std::stoull(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong() + 16);
	output += ", ";
	output += std::to_string(operandR.to_ulong());

	return output;
}
std::string BLD(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BLD r";
	std::string tmpString;

	std::bitset<5> operandD;
	std::bitset<3> operandB;

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));
	
	tmpString.clear(); 
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string BST(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BST r";
	std::string tmpString;

	std::bitset<5> operandD;
	std::bitset<3> operandB;

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string SBRC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBRC r";
	std::string tmpString;

	std::bitset<5> operandD;
	std::bitset<3> operandB;

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string SBRS(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "SBRS r";
	std::string tmpString;

	std::bitset<5> operandD;
	std::bitset<3> operandB;

	tmpString.push_back(b2.to_string().at(3)); tmpString.append(b3.to_string());
	operandD = std::bitset<5>(std::stoul(tmpString, nullptr, 2));

	tmpString.clear();
	tmpString.push_back(b4.to_string().at(1));
	tmpString.push_back(b4.to_string().at(2));
	tmpString.push_back(b4.to_string().at(3));
	operandB = std::bitset<3>(std::stoul(tmpString, nullptr, 2));

	output += std::to_string(operandD.to_ulong());
	output += ",";
	output += std::to_string(operandB.to_ulong());

	return output;
}
std::string BRCS(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRCS_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BREQ(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BREQ_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRMI(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRMI_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRVS(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRVS_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRLT(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRLT_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRHS(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRHS_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRTS(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRTS_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRIE(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRIE_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRCC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRCC_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRNE(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRNE_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRPL(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRPL_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRVC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRVC_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRGE(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRGE_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRHC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRHC_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRTC(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRTC_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}
std::string BRID(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::string output = "BRID_";
	std::string tmpString;
	std::bitset<6> operandK;

	tmpString.push_back(b2.to_string().at(3));
	tmpString.append(b3.to_string());
	tmpString.push_back(b4.to_string().at(0));

	operandK = std::bitset<6>(std::stoul(tmpString, nullptr, 2));
	int operandKDecoded;

	if (b2.to_string().at(2) == '1') {
		operandK = ~operandK;
		operandKDecoded = operandK.to_ulong() + 1;
		output += "-";
		output += std::to_string(operandKDecoded);
	}
	else
		output += std::to_string(operandK.to_ulong());

	return output;
}


/*=======================BUGS=======================*//*
	LDD r4, z+63 --> LDS r20, $77
*/
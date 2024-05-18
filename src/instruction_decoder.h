#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <string>
#include "operand_identifier.h"


std::string decodeOpcode0000(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong()) {
	case 0b0000: return NOP(); break;
	case 0b0001: return MOVW(b3, b4); break;
	case 0b0010: return MULS(b3, b4); break;
	case 0b0011: {
		bool tmp0 = (b3.to_ulong() & 0b1000) > 0;
		bool tmp1 = (b4.to_ulong() & 0b1000) > 0;
		if (!tmp0 && !tmp1) return MULSU(b3, b4);
		if (!tmp0 && tmp1) return FMUL(b3, b4);
		if (tmp0 && !tmp1) return FMULS(b3, b4);
		if (tmp0 && tmp1) return FMULSU(b3, b4);
		break;
	}
	}
	switch (b2.to_ulong() >> 2) {
	case 0b01: return CPC(b2, b3, b4); break;
	case 0b10: return SBC(b2, b3, b4); break;
	case 0b11: return ADD(b2, b3, b4); break;
	}

	return "";
}
std::string decodeOpcode0001(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong() >> 2) {
	case 0b00: return CPSE(b2, b3, b4); break;
	case 0b01: return CP(b2, b3, b4); break;
	case 0b10: return SUB(b2, b3, b4); break;
	case 0b11: return ADC(b2, b3, b4); break;
	}
	return "";
}
std::string decodeOpcode0010(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong() >> 2) {
	case 0b00: return AND(b2, b3, b4); break;
	case 0b01: return EOR(b2, b3, b4); break;
	case 0b10: return OR(b2, b3, b4); break;
	case 0b11: return MOV(b2, b3, b4); break;
	}
	return "";
}
std::string decodeOpcode0011(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return CPI(b2, b3, b4);
}
std::string decodeOpcode0100(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return SBCI(b2, b3, b4);
}
std::string decodeOpcode0101(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return SUBI(b2, b3, b4);
}
std::string decodeOpcode0110(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return ORI(b2, b3, b4);
}
std::string decodeOpcode0111(std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return ANDI(b2, b3, b4);
}
std::string decodeOpcode1000(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	bool bit = (b2.to_ulong() & 0b0010) > 0;

	switch (bit) {
	case 0: return LD(b1, b2, b3, b4); break;
	case 1: return ST(b1, b2, b3, b4); break;
	}
	return "?";
}
std::string decodeOpcode1001(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong() >> 2) {
	case 0b11: return MUL(b2, b3, b4); break;
	}
	switch (b2.to_ulong() >> 1) {
	case 0b000:
		switch (b4.to_ulong()) {
		case 0b0000: return LDS32(b2, b3, b4); break;
		case 0b0001: return LD(b1, b2, b3, b4); break;
		case 0b0010: return LD(b1, b2, b3, b4); break;
		case 0b0100: return LPM(b2, b3, b4); break;
		case 0b0101: return LPM(b2, b3, b4); break;
		case 0b0110: return ELPM(b2, b3, b4); break;
		case 0b0111: return ELPM(b2, b3, b4); break;
		case 0b1001: return LD(b1, b2, b3, b4); break;
		case 0b1010: return LD(b1, b2, b3, b4); break;
		case 0b1100: return LD(b1, b2, b3, b4); break;
		case 0b1101: return LD(b1, b2, b3, b4); break;
		case 0b1110: return LD(b1, b2, b3, b4); break;
		case 0b1111: return POP(b2, b3); break;
		}
	break;
	case 0b001:
		switch (b4.to_ulong()) {
		case 0b0000: return STS32(b2, b3, b4); break;
		case 0b0001: return ST(b1, b2, b3, b4); break;
		case 0b0010: return ST(b1, b2, b3, b4); break;
		case 0b0100: return XCH(b2, b3); break;
		case 0b0101: return LAS(b2, b3); break;
		case 0b0110: return LAC(b2, b3); break;
		case 0b0111: return LAT(b2, b3); break;
		case 0b1001: return ST(b1, b2, b3, b4); break;
		case 0b1010: return ST(b1, b2, b3, b4); break;
		case 0b1100: return ST(b1, b2, b3, b4); break;
		case 0b1101: return ST(b1, b2, b3, b4); break;
		case 0b1110: return ST(b1, b2, b3, b4); break;
		case 0b1111: return PUSH(b2, b3); break;
			break;
		}
	break;
	case 0b010:
		switch (b4.to_ulong() >> 1) {

		case 0b110: return JUMP(b2, b3, b4); break;
		case 0b111: return CALL(b2, b3, b4); break;
		}
		switch (b4.to_ulong()) {
		case 0b0000: return COM(b2, b3); break;
		case 0b0001: return NEG(b2, b3); break;
		case 0b0010: return SWAP(b2, b3); break;
		case 0b0011: return INC(b2, b3); break;
		case 0b1000: if (b2.to_ulong() == 0b0101 && b3.to_ulong() == 0b1100) { return LPM(b2, b3, b4); } break;
		case 0b0101: return ASR(b2, b3); break;
		case 0b0110: return LSR(b2, b3); break;
		case 0b0111: return ROR(b2, b3); break;
		case 0b1010: return DEC(b2, b3); break;
		}
		switch (b2.to_ulong()) {
		case 0b0100:
			switch (b4.to_ulong()) {
			case 0b1000:
				switch (b3.to_ulong()) {
				case 0b0000: return SEC(); break;
				case 0b0001: return SEZ(); break;
				case 0b0010: return SEN(); break;
				case 0b0011: return SEV(); break;
				case 0b0100: return SES(); break;
				case 0b0101: return SEH(); break;
				case 0b0110: return SET(); break;
				case 0b0111: return SEI(); break;
				case 0b1000: return CLC(); break;
				case 0b1001: return CLZ(); break;
				case 0b1010: return CLN(); break;
				case 0b1011: return CLV(); break;
				case 0b1100: return CLS(); break;
				case 0b1101: return CLH(); break;
				case 0b1110: return CLT(); break;
				case 0b1111: return CLI(); break;
				}
				break;
			case 0b1001:
				switch (b3.to_ulong()) {
				case 0b0000: return IJMP(); break;
				case 0b0001: return EIJMP(); break;
				}
				break;
			case 0b1011: return DES(b3); break;
			}
			break;
		case 0b0101:
			switch (b4.to_ulong()) {
			case 0b1000:
				switch (b3.to_ulong()) {
				case 0b0000: return RET(); break;
				case 0b0001: return RETI(); break;
				case 0b1000: return SLEEP(); break;
				case 0b1001: return BREAK(); break;
				case 0b1010: return WDR(); break;
				case 0b1100: return LPM(b2, b3, b4); break;
				case 0b1101: return ELPM(b2, b3, b4); break;
				case 0b1110: return SPM(); break;
				case 0b1111: return SPM(); break;
				}
				break;
			case 0b1001:
				switch (b3.to_ulong()) {
				case 0b0000: return ICALL(); break;
				case 0b0001: return EICALL(); break;
				}
				break;
			}
			break;
		}
	break;
	}
	switch (b2.to_ulong()) {
	case 0b0110: return ADIW(b3, b4); break;
	case 0b0111: return SBIW(b3, b4); break;
	case 0b1000: return CBI(b3, b4); break;
	case 0b1001: return SBIC(b3, b4); break;
	case 0b1010: return SBI(b3, b4); break;
	case 0b1011: return SBIS(b3, b4); break;
	}
	
	return "?";
}
std::string decodeOpcode1010(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong() >> 3) {
	case 0b0: return LDS16(b2, b3, b4); break;
	case 0b1: return STS16(b2, b3, b4); break;
	}
	return LD(b1, b2, b3, b4);
}
std::string decodeOpcode1011(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	switch (b2.to_ulong() >> 3) {
	case 0b0: return IN(b2, b3, b4); break;
	case 0b1: return OUT(b2, b3, b4); break;
	}
	return "";
}
std::string decodeOpcode1100(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4){
	return RJMP(b2,b3,b4);
}
std::string decodeOpcode1101(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	return RCALL(b2, b3, b4);
}
std::string decodeOpcode1110(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	if (b2.to_ulong() == 0b1111 && b4.to_ulong() == 0b1111)
		return SER(b3);
	else
		return LDI(b2, b3, b4);
}
std::string decodeOpcode1111(std::bitset<4> b1, std::bitset<4> b2, std::bitset<4> b3, std::bitset<4> b4) {
	std::bitset<3> tmp;

	{ 
		//b4.to_ulong() << 1 not working
		std::string tmpString;
		tmpString.push_back(b4.to_string().at(1));
		tmpString.push_back(b4.to_string().at(2));
		tmpString.push_back(b4.to_string().at(3));
		tmp = std::bitset<3>(std::stoull(tmpString, nullptr, 2));
	}
	
	switch (b4.to_ulong() >> 3){
	case 0b0: 
		switch (b2.to_ulong() >> 1) {
		case 0b100: return BLD(b2, b3, b4); break;
		case 0b101: return BST(b2, b3, b4); break;
		case 0b110: return SBRC(b2, b3, b4); break;
		case 0b111: return SBRS(b2, b3, b4); break;
		}
		break;
	}

	switch (b2.to_ulong() >> 2){
	case 0b0000: 
		switch (tmp.to_ulong()) {
		case 0b000: return BRCS(b2, b3, b4); break;
		case 0b001: return BREQ(b2, b3, b4); break;
		case 0b010: return BRMI(b2, b3, b4); break;
		case 0b011: return BRVS(b2, b3, b4); break;
		case 0b100: return BRLT(b2, b3, b4); break;
		case 0b101: return BRHS(b2, b3, b4); break;
		case 0b110: return BRTS(b2, b3, b4); break;
		case 0b111: return BRIE(b2, b3, b4); break;
		}
	break;
	case 0b0001:
		switch (tmp.to_ulong()) {
		case 0b000: return BRCC(b2, b3, b4); break;
		case 0b001: return BRNE(b2, b3, b4); break;
		case 0b010: return BRPL(b2, b3, b4); break;
		case 0b011: return BRVC(b2, b3, b4); break;
		case 0b100: return BRGE(b2, b3, b4); break;
		case 0b101: return BRHC(b2, b3, b4); break;
		case 0b110: return BRTC(b2, b3, b4); break;
		case 0b111: return BRID(b2, b3, b4); break;
		}
	break;
	}

	return "?";
}
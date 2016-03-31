/*
 * bitoperation.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#include "bitoperation.h"

unsigned int getFrameNum(unsigned int fn) {
	return fn & 0x0fffffff;
}

void setFrameNum(unsigned int& fn, int res) {
	fn = (fn & 0xf0000000) | res;
}

unsigned int getPresentBit(unsigned int addr) {
	return 0 | (addr >> 31);
}

void setPresentBit(unsigned int& addr) {
	addr |= 0x80000000;
}

void resetPresentBit(unsigned int& addr) {
	addr &= 0x7fffffff;
}

unsigned int getModifiedBit(unsigned int addr) {
	return 0 | ((addr >> 30) & 1);
}

void setModifiedBit(unsigned int& addr) {
	addr |= 0x40000000;
}

void resetModifiedBit(unsigned int& addr) {
	addr &= 0xbfffffff;
}

unsigned int getReferencedBit(unsigned int addr) {
	return 0 | ((addr >> 29) & 1);
}

void setReferencedBit(unsigned int& addr) {
	addr |= 0x20000000;
}

void resetReferencedBit(unsigned int& addr) {
	addr &= 0xdfffffff;
}

unsigned int getPageoutBit(unsigned int addr) {
	return 0 | ((addr >> 28) & 1);
}

void setPageoutBit(unsigned int& addr) {
	addr |= 0x10000000;
}

void resetPageoutBit(unsigned int& addr) {
	addr &= 0xefffffff;
}


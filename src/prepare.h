/*
 * prepare.h
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#ifndef PREPARE_H_
#define PREPARE_H_

#include <string>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

#include "random.h"
#include "vmm.h"
#include "pager.h"

class Prepare {
public:
	// instruction file
	FILE* ifile;

	// length of frame table
	int numOfFrame;

	// print options
	bool O, P, F, S, p, f, a;

	// type of replacement algorithm being used
	Pager* pager;

	Prepare();
	~Prepare();

	// if all the events have been put out
	bool done();

	// parse the input
	bool parseCommand(char*[], int);

	// get next instruction
	void nextIns(unsigned int&, unsigned int&);

	// get VMM
	VMM getVMM();
};
#endif

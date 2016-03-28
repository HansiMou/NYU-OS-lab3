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
#include "algorithm.h"

class prepare {
public:
	FILE* ifile;
	int numOfFrame;
	// output options
	bool O, P, F, S, p, f, a;
	Algorithm* alg;

	prepare();
	~prepare();
	bool parseCommand(char**, int);

	void nextIns(unsigned int&, unsigned int&);

	VMM getVMM();
};

#endif /* PREPARE_H_ */

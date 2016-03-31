/*
 * main.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: hans
 */

#include <iostream>
#include <cstdio>

#include "prepare.h"
#include "vmm.h"

int main(int argc, char* argv[]) {
	Prepare p;
	unsigned int type, num;

	p.parseCommand(argv, argc);
	VMM v = p.getVMM();

	while (!p.done()) {
		p.nextIns(type, num);

		// end
		if (type == -1 && num == -1)
			break;

		if (num > 63){
			fprintf(stderr, "Virtual page index should fall within [0, 63].\n");
			break;
		}

		v.map(type, num);
	}
	v.print();
}

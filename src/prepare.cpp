/*
 * Prepare.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#include "prepare.h"

Prepare::Prepare() {
	ifile = NULL;
	numOfFrame = 32;
	O = P = F = S = p = f = a = false;
	pager = new Pager_LRU();
}

Prepare::~Prepare() {
	if (ifile != NULL)
		fclose(ifile);
}

bool Prepare::parseCommand(char* argv[], int argc) {
	if (argc < 3) {
		fprintf(stderr, "Wrong number of parameters.\n");
		return false;
	}

	// parse arguments
	int c;
	int optLen;
	while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
		switch (c) {
		// set algorithm
		case 'a':
			switch (optarg[0]) {
			case 'l':
				pager = new Pager_LRU();
				break;
			case 'r':
				pager = new Pager_Random();
				break;
			case 'f':
				pager = new Pager_FIFO();
				break;
			case 's':
				pager = new Pager_SecondChance();
				break;
			case 'c':
				pager = new Pager_ClockP();
				break;
			case 'a':
				pager = new Pager_AgingP();
				break;
			case 'N':
				pager = new Pager_NRU();
				break;
			case 'X':
				pager = new Pager_ClockV();
				break;
			case 'Y':
				pager = new Pager_AgingV();
				break;
			default:
				break;
			}
			break;
			// set output options
		case 'o':
			optLen = strlen(optarg);
			for (int i = 0; i < optLen; i++) {
				switch (optarg[i]) {
				case 'O':
					O = true;
					break;
				case 'P':
					P = true;
					break;
				case 'F':
					F = true;
					break;
				case 'S':
					S = true;
					break;
				case 'p':
					p = true;
					break;
				case 'f':
					f = true;
					break;
				case 'a':
					a = true;
					break;
				}
			}
			break;
			// set number of frame
		case 'f':
			sscanf(optarg, "%d", &numOfFrame);
			if (numOfFrame > 64) {
				fprintf(stderr, "Too many frames, not supported.\n");
				return false;
			}
			break;
		}
	}

	ifile = fopen(argv[argc - 2], "r");
	if (ifile == NULL) {
		fprintf(stderr, "Instruction file cannot found.\n");
		return false;
	}

	pager->random = Random(argv[argc - 1]);
	pager->numOfFrame = numOfFrame;

	return true;
}

// get next instruction
void Prepare::nextIns(unsigned int& ins, unsigned int& pagenum) {
	char buffer[10000];
	fgets(buffer, 10000, ifile);

	while (!feof(ifile)) {
		if (buffer[0] == '#')
			fgets(buffer, 10000, ifile);
		else {
			sscanf(buffer, "%d%d", &ins, &pagenum);
			return;
		}
	}

	if (feof(ifile)) {
		ins = pagenum = -1;
		return;
	}
}

bool Prepare::done() {
	return feof(ifile);
}
VMM Prepare::getVMM() {
	return VMM(numOfFrame, O, P, F, S, p, f, a, pager);
}

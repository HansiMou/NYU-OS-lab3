/*
 * prepare.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#include "prepare.h"

prepare::prepare() {
	O = P = F = S = p = f = a = numOfFrame = false;
	alg = new Alg_LRU();
}

prepare::~prepare() {
	if (ifile != NULL)
		fclose(ifile);
}

bool prepare::parseCommand(char* argv[], int argc) {
	if (argc < 3) {
		fprintf(stderr, "Wrong number of parameters.\n");
		return false;
	}

	// parse arguments
	int c;
	int optLen;
	while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
		switch (c) {
		// set number of frame
		case 'f':
			sscanf(optarg, "%d", &numOfFrame);
			break;
			// set algorithm
		case 'a':
			switch (optarg[0]) {
			case 'N':
				algo = new Alg_NRU();
				break;
			case 'C':
				algo = new Alg_Clock_V();
				break;
			case 'A':
				algo = new Alg_Aging_V();
				break;
			case 'l':
				algo = new Alg_LRU();
				break;
			case 'r':
				algo = new Alg_Random();
				break;
			case 'f':
				algo = new Alg_FIFO();
				break;
			case 's':
				algo = new Alg_SecondChance();
				break;
			case 'c':
				algo = new Alg_Clock_P();
				break;
			case 'a':
				algo = new Alg_Aging_P();
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
		}
	}

	ifile = fopen(argv[argc - 2], "r");
	if (ifile == NULL) {
		fprintf(stderr, "Instruction file cannot found.\n");
		return false;
	}

	algo->setRandom(Random(argv[argc - 1]));
	algo->setNumOfFrames(numOfFrames);

	return true;
}

// get next instruction
void prepare::nextIns(unsigned int& ins, unsigned int& pagenum) {
	char buffer[10000];
	fgets(buffer, 10000, ifile);

	while (!feof(ifile)){
		if (buffer[0] == '#')
			fgets(buffer, 10000, ifile);
		else{
			sscanf(buffer, "%d%d", &ins, &pagenum);
			return;
		}
	}

	if (feof(ifile)){
		ins = pagenum = -1;
		return;
	}
}

VMM prepare::getVMM() {
	return VMM(algo, numOfFrames, O, P, F, S, p, f, a);
}

/*
 * random.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#include "random.h"
FILE* random::rfile;
random::random(char* path) {
	rfile = fopen(path, r);
	done = false;
	if (rfile == NULL) {
		fprint(stderr, "random file not found.\n");
	}
	char buffer[100];
	fgets(buffer, 100, rfile);
}

int random::getRandNum() {
	char buffer[100];
	int res;
	fgets(buffer, 100, rfile);
	if (feof(rfile)) {
		fseek(rfile, 0, SEEK_SET);
		fgets(buffer, 100, rfile);
		fgets(buffer, 100, rfile);
	}
	sscanf(buffer, "%d", &res);
	return res;
}

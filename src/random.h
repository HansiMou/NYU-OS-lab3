/*
 * random
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdio>

// deal with the random file
class Random {
public:
	bool done;
	static FILE* rfile;
	Random();
	Random(char*);
	int getRandNum();
};

#endif /* RANDOM_H_ */

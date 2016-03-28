/*
 * random
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#ifndef RANDOM_H_
#define RANDOM_H_

// deal with the random file

class random {
public:
	bool done;
	FILE* rfile;
	random(char*);
	int getRandNum();
};

#endif /* RANDOM_H_ */

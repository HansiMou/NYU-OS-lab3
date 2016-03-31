/*
 *  Created on: Mar 30, 2016
 *      Author: hans
 */
#ifndef __PAGER_H__
#define __PAGER_H__

#include <iostream>
#include <vector>

#include "bitoperation.h"
#include "random.h"

// base class for all pager replacement
class Pager {
public:
	Random random;
	int numOfFrame;

	virtual int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&) = 0;
	virtual void update(std::vector<unsigned int>&, unsigned int);
};

class Pager_NRU: public Pager {
public:
	// reset the ref bits every 10th page
	int clock;
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_LRU: public Pager {
public:
	void update(std::vector<unsigned int>&, unsigned int);
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_Random: public Pager {
public:
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_FIFO: public Pager {
public:
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_SecondChance: public Pager {
public:
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_ClockP: public Pager {
public:
	int clock;
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_ClockV: public Pager {
public:
	int clock;
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_AgingP: public Pager {
public:
	std::vector<unsigned int> ages;
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};

class Pager_AgingV: public Pager {
public:
	std::vector<unsigned int> ages;
	int getNew(std::vector<unsigned int>&, std::vector<unsigned int>&,
			std::vector<unsigned int>&);
};
#endif

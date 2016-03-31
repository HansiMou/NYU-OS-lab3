/*
 * vmm.h
 *
 *  Created on: Mar 30, 2016
 *      Author: hans
 */
#ifndef __VMM_H__
#define __VMM_H__

#include <cstdio>
#include <vector>
#include <iostream>

#include "pager.h"
#include "bitoperation.h"

class VMM {
public:
	// a list contains all the frames
	std::vector<unsigned int> frametable;

	// reverse-mapped table
	std::vector<unsigned int> reversed;

	// list of pages
	std::vector<unsigned int> pagetable;

	// the number of frame
	unsigned int numOfFrame;

	// statistics
	long long int stats_inst, stats_zeros, stats_ins, stats_outs, stats_unmaps, stats_maps;

	// page replacement
	Pager* pager;

	// options
	bool O, P, F, S, p, f, a;

	VMM(unsigned int, bool, bool, bool, bool, bool, bool, bool, Pager*);

	void Update_pte(unsigned int, unsigned int&);

	void doTheMap(unsigned int&, unsigned int);

	void pageReplace(unsigned int&, unsigned int);

		// map the page number to frame
	void map(unsigned int, unsigned int);

	// print the result for output
	void print();
};

#endif

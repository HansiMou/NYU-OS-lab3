/*
 * vmm.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: hans
 */

#include "vmm.h"

VMM::VMM(unsigned int num, bool vo, bool vp, bool vf, bool vs, bool vpp,
		bool vff, bool va, Pager* pa) {
	// intialize
	stats_inst = stats_zeros = stats_ins = stats_outs = stats_unmaps =
			stats_maps = 0;

	// set the number of frames
	numOfFrame = num;

	pager = pa;

	// set printing options
	O = vo;
	P = vp;
	F = vf;
	S = vs;
	p = vpp;
	f = vff;
	a = va;

	pagetable = std::vector<unsigned int>(64, 0);
	reversed = std::vector<unsigned int>(numOfFrame, -1);
}
void VMM::print() {
	if (P) {
		for (int i = 0; i < pagetable.size(); i++) {
			if (getPresentBit(pagetable[i]) == 1) {
				printf("%d:", i);
				if (getReferencedBit(pagetable[i]) == 1) {
					printf("R");
				} else {
					printf("-");
				}

				if (getModifiedBit(pagetable[i]) == 1) {
					printf("M");
				} else {
					printf("-");
				}

				if (getPageoutBit(pagetable[i]) == 1) {
					printf("S ");
				} else {
					printf("- ");
				}

			} else {
				if (getPageoutBit(pagetable[i]) == 1) {
					printf("# ");
				} else {
					printf("* ");
				}
			}
		}
		printf("\n");
	}
	if (F) {
		for (int i = 0; i < reversed.size(); i++) {
			if (reversed[i] == -1) {
				printf("* ");
			} else {
				printf("%d ", reversed[i]);
			}
		}
		printf("\n");
	}
	if (S) {
		unsigned long long taotalcost;

		taotalcost = stats_inst + 400 * (stats_maps + stats_unmaps)
				+ 3000 * (stats_ins + stats_outs) + 150 * stats_zeros;

		printf("SUM %d U=%d M=%d I=%d O=%d Z=%d ===> %llu\n", stats_inst,
				stats_unmaps, stats_maps, stats_ins, stats_outs, stats_zeros,
				taotalcost);
	}
}

void VMM::Update_pte(unsigned int type, unsigned int& page) {
	pager->update(frametable, getFrameNum(page));
	// read instruction
	if (type == 0) {
		setReferencedBit(page);
	} else {
		// write operation
		setModifiedBit(page);
		setReferencedBit(page);
	}
}

void VMM::doTheMap(unsigned int& page, unsigned int num) {
	unsigned int numofframe;
	numofframe = frametable.size();

	// build the map
	setFrameNum(page, numofframe);
	// printf("ffff: %d\n", getFrameNum(page));

	// save to the frame table
	frametable.push_back(numofframe);

	// build thte reverse table
	reversed[numofframe] = num;

	if (O) {
		printf("%d: ZERO     %4d\n", stats_inst, numofframe);
		printf("%d: MAP  %4d%4d\n", stats_inst, num, numofframe);
	}
	stats_zeros++;
	stats_maps++;
}
void VMM::pageReplace(unsigned int& page, unsigned int num) {
	unsigned int numofframe;
	// find the new  page
	numofframe = pager->getNew(pagetable, frametable, reversed);
	unsigned int tt = reversed[numofframe];
	unsigned int& t = pagetable[tt];

	if (O) {
		printf("%d: UNMAP%4d%4d\n", stats_inst, tt, numofframe);
	}
	stats_unmaps++;

	// reset present and referenced bit
	resetPresentBit(t);
	resetReferencedBit(t);

	// previous page is modified
	if (getModifiedBit(t) == 1) {
		// clean it
		resetModifiedBit(t);
		setPageoutBit(t);

//				printf("ffff: %d", numofframe);
		if (O) {
			printf("%d: OUT  %4d%4d\n", stats_inst, tt, numofframe);
		}
		stats_outs++;
	}

	if (getPageoutBit(page) == 1) {
		if (O) {
			printf("%d: IN   %4d%4d\n", stats_inst, num, numofframe);
		}
		stats_ins++;
	} else {
		if (O) {
			printf("%d: ZERO     %4d\n", stats_inst, numofframe);
		}
		stats_zeros++;
	}
	if (O) {
		printf("%d: MAP  %4d%4d\n", stats_inst, num, numofframe);
	}
	stats_maps++;

	setFrameNum(page, numofframe);
	reversed[numofframe] = num;
}
void VMM::map(unsigned int type, unsigned int num) {
	unsigned int& page = pagetable[num];

	if (O) {
		printf("==> inst: %d %d\n", type, num);
	}
	// already mapped
	if (getPresentBit(page) == 1) {
		Update_pte(type, page);
	}
	// this page has not been mapped yet
	else {
		// not full
		if (frametable.size() < numOfFrame) {
			doTheMap(page, num);

		}
		// page replacement
		else {
			pageReplace(page, num);
		}

		// update
		setPresentBit(page);
		Update_pte(type, page);
	}
	stats_inst++;
}


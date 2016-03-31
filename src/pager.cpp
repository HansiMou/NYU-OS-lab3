/*
 *
 *  Created on: Mar 30, 2016
 *      Author: hans
 */

#include "pager.h"
void Pager::update(std::vector<unsigned int>& frametable, unsigned int f) {
}
// NRU
int Pager_NRU::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {

	std::vector<std::vector<int> > NumberedSet(4, std::vector<int>());

	// number all the pagetable
	for (int i = 0; i < pagetable.size(); i++) {
		// if the page is present
		if (getPresentBit(pagetable[i]) == 1) {
			unsigned int r = getReferencedBit(pagetable[i]);
			unsigned int m = getModifiedBit(pagetable[i]);

			if (r == 0 && m == 0) {
				NumberedSet[0].push_back(getFrameNum(pagetable[i]));
			} else if (r == 0 && m == 1) {
				NumberedSet[1].push_back(getFrameNum(pagetable[i]));
			} else if (r == 1 && m == 0) {
				NumberedSet[2].push_back(getFrameNum(pagetable[i]));
			} else {
				NumberedSet[3].push_back(getFrameNum(pagetable[i]));
			}
		}
	}

// find a random page from the lowest numbered unempty class
	int res = -1;
	for (int i = 0; i < 4; i++) {
		if (NumberedSet[i].size() > 0) {
			res = NumberedSet[i][random.getRandNum() % NumberedSet[i].size()];
			break;
		}
	}

	clock++;
	if (clock == 10) {
		for (int i = 0; i < pagetable.size(); i++) {
			resetReferencedBit(pagetable[i]);
		}
		clock = 0;
	}

	return res;
}

// LRU
void Pager_LRU::update(std::vector<unsigned int>& frametable, unsigned int f) {
	for (int i = 0; i < frametable.size(); i++) {
		if (frametable[i] == f) {
			frametable.erase(frametable.begin() + i);
			frametable.push_back(f);
			break;
		}
	}
	return;
}

int Pager_LRU::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {

	// fetch the lease recently used frame
	unsigned int f = frametable.front();
	frametable.erase(frametable.begin());

	// moves it to the back, because we just used it
	frametable.push_back(f);
	return frametable.back();
}

// Random
int Pager_Random::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {
	int r = random.getRandNum();
	return frametable[r % frametable.size()];
}

// FIFO
int Pager_FIFO::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {

	unsigned int f = frametable.front();
	frametable.erase(frametable.begin());
	frametable.push_back(f);
	return frametable.back();
}

// second chance
int Pager_SecondChance::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {

	unsigned int f, index;
	bool found = false;

	while (found != true) {
		f = frametable.front();
		index = reversed[f];
		if (getReferencedBit(pagetable[index]) == 0) {
			frametable.erase(frametable.begin());
			frametable.push_back(f);
			found = true;
		} else {
			resetReferencedBit(pagetable[index]);
			frametable.erase(frametable.begin());
			frametable.push_back(f);
		}
	}
	return frametable.back();
}

// Clock Based on Physical Frames
int Pager_ClockP::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {
	unsigned int f, index;
	bool found = false;

	while (found != true) {
		f = frametable[clock];
		index = reversed[f];

		if (getReferencedBit(pagetable[index]) == 0) {
			found = true;
		} else {
			resetReferencedBit(pagetable[index]);
		}
		// advance the clock
		clock = (clock + 1) % frametable.size();
	}
	return f;
}

// Clock based on virtual page
int Pager_ClockV::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {
	unsigned int res;
	bool found = false;

	while (found != true) {
		if (getPresentBit(pagetable[clock]) == 1) {
			if (getReferencedBit(pagetable[clock]) == 0) {
				found = true;
				res = getFrameNum(pagetable[clock]);
			} else {
				resetReferencedBit(pagetable[clock]);
			}
		}
		clock = (clock + 1) % pagetable.size();
	}
	return res;
}

// Aging based on physical frametable
int Pager_AgingP::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {
	unsigned int min_frame = -1;
	unsigned int min_index = -1;
	unsigned int min_age = 0xffffffff;

	if (ages.size() == 0) {
		ages = std::vector<unsigned int>(64, 0);
	}

	for (int i = 0; i < frametable.size(); i++) {
		//added R to the leftmost
		ages[i] =
				(ages[i] >> 1)
						| ((getReferencedBit(pagetable[reversed[frametable[i]]]))
								<< 31);

		// found the lowest age
		if (ages[i] < min_age) {
			min_frame = frametable[i];
			min_index = i;
			min_age = ages[i];
		}

		resetReferencedBit(pagetable[reversed[frametable[i]]]);
	}
	ages[min_index] = 0;
	return min_frame;
}

// Aging based on virtual pagetable
int Pager_AgingV::getNew(std::vector<unsigned int>& pagetable,
		std::vector<unsigned int>& frametable,
		std::vector<unsigned int>& reversed) {
	unsigned int min_age = 0xffffffff;
	unsigned int min_index = -1;

	if (ages.size() == 0) {
		ages = std::vector<unsigned int>(64, 0);
	}

	for (int i = 0; i < pagetable.size(); i++) {
		//added R to the leftmost
		ages[i] = (ages[i] >> 1) | ((getReferencedBit(pagetable[i])) << 31);
		// found the lowest age
		if (getPresentBit(pagetable[i]) == 1 && ages[i] < min_age) {
			min_age = ages[i];
			min_index = i;
		}

		if (getPresentBit(pagetable[i]) == 1) {
			resetReferencedBit(pagetable[i]);
		}
	}
	ages[min_index] = 0;

	return getFrameNum(pagetable[min_index]);
}

/*
 * bitoperation.h
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#ifndef BITOPERATION_H_
#define BITOPERATION_H_

unsigned int getFrameNum(unsigned int);
void setFrameNum(unsigned int&, int);

unsigned int getPresentBit(unsigned int);
void setPresentBit(unsigned int&);
void resetPresentBit(unsigned int&);

unsigned int getModifiedBit(unsigned int);
void setModifiedBit(unsigned int&);
void resetModifiedBit(unsigned int&);

unsigned int getReferencedBit(unsigned int);
void setReferencedBit(unsigned int&);
void resetReferencedBit(unsigned int&);

unsigned int getPageoutBit(unsigned int);
void setPageoutBit(unsigned int&);
void resetPageoutBit(unsigned int&);

#endif /* BITOPERATION_H_ */

/*
 * bitoperation.h
 *
 *  Created on: Mar 28, 2016
 *      Author: hans
 */

#ifndef BITOPERATION_H_
#define BITOPERATION_H_

void setFrameNumber(unsigned int&, int);
unsigned int getFrameNumber(unsigned int);

void setPresentBit(unsigned int&);
unsigned int getPresentBit(unsigned int);
void resetPresentBit(unsigned int&);

void setModifiedBit(unsigned int&);
unsigned int getModifiedBit(unsigned int);
void resetModifiedBit(unsigned int&);

void setReferencedBit(unsigned int&);
unsigned int getReferencedBit(unsigned int);
void resetReferencedBit(unsigned int&);

void setPageoutBit(unsigned int&);
unsigned int getPageoutBit(unsigned int);
void resetPageoutBit(unsigned int&);



#endif /* BITOPERATION_H_ */

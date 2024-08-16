/******************************************************************************
;@
;@ Student Name 1: Tao Li
;@ Student 1 #: 301342974
;@ Student 1 userid (email): tla152(tla152@sfu.ca)
;@
;@ Student Name 2: student2
;@ Student 2 #: 123456782
;@ Student 2 userid (email): stu2 (stu2@sfu.ca)
;@
;@ Below, edit to list any people who helped you with the code in this file,
;@      or put ‘none’ if nobody helped (the two of) you.
;@
;@ Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
;@
;@ Also, reference resources beyond the course textbooks and the course pages on Canvas
;@ that you used in making your submission.
;@
;@ Resources:  ___________
;@
;@% Instructions:
;@ * Put your name(s), student number(s), userid(s) in the above section.
;@ * Edit the "Helpers" line and "Resources" line.
;@ * Your group name should be "HW5_<userid1>_<userid2>" (eg. HW5_stu1_stu2)
;@ * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
;@ * Submit your file to courses.cs.sfu.ca
;@
;@ Name        : BigFib.c
;@ Description : bigFib subroutine for HW5.
******************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <string.h>  // for strerror()
#include "heapstats.h"

typedef unsigned int bigNumN[];

int bigAdd(bigNumN bigN0P, const bigNumN bigN1P, unsigned int maxN0Size);

//check if the address is null
int bigFib(int n, int maxSize, unsigned **bNP) {
	if(bNP ==0){
		errno = EINVAL;
		return -1;
}

	unsigned* bNa = malloc(4*(1 + maxSize));
	// check for null pointer being returned or not
	if (bNa){
		*bNa = 0;
	}		
	else{
		errno = ENOMEM;
		*bNP = bNa;
		return -1;
	}


	unsigned* bNb = malloc(4*(1 + maxSize));
	// check for null pointer being returned or not
		if (bNb){
		*bNb = 1;
		}			
		else{
			errno = ENOMEM;
			*bNP = bNb;
			return -1;
		}

	HEAPSTATS;

	if(n<0||maxSize <0){
		errno = EINVAL;
		*bNa = 0;
		*bNP = bNa;
		free(bNb);
		return -1;
	}
	if(maxSize == 0){
		*bNa = 0;
		*bNP = bNa;
		free(bNb);
		return 0;
	}
	//initialze variable
	int EvenNum = 0;
	int OddNum = 0;
	int carry = 0;

	//calculation
	if(maxSize>0){

		*(bNa+1) = 0;
		*(bNb+1) = 1;
		for (int i = 2; i<=n; i++){
			if(*bNa>maxSize){
				carry = 1;
			}
			else{
				carry = 0;
			}
			if(!(i%2)){
				EvenNum = bigAdd(bNa, bNb, maxSize+carry);
			}
			else{
				OddNum = bigAdd(bNb,bNa, maxSize+carry);
			}
			if(EvenNum == 1){
				*bNP = bNb;
				free(bNa);
				return i-1;
			}
			if(OddNum == 1){
				*bNP = bNa;
				free(bNb);
				return i-1;
			}
		}
	}

	if(n == 0){
			*bNP = bNa;
			free(bNb);
			return 0;
	}
	if (n == 1){
		*bNb = 1;
		*(bNb+1) = 1;
		*bNP = bNb;
		free(bNa);
		return 1;
	}
	else if(n%2 ==0){
		*bNP = bNa;
		return n;
	}
	else{
		*bNP = bNb;
		return n;
	}
	
	return 0;
}


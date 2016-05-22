#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO;
	uint32_t address;
	uint8_t  firstbyte;
	struct breakpoint *next;

	/* TODO: Add more members if necessary */


} BP;

#endif

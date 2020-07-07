#pragma once


/****************************************Trace Marcos****************************************/

#define trace(fmt,...)		printf((fmt), ##__VA_ARGS__)

/*****************************************Bit-wise Marcros***********************************/

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (((x) & (y)) == (y))   // warning: evaluates y twice
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))

/**
 * @brief a=Target variable b=bit number c=conditon to check
 * 
 * Sets a bit at bit number based on a given condition. If condition true
 * the bit is set to 1, if false, it is set to 0.
 * 
 */
#define BIT_SET_FROM(a, b, c) ((c) ? BIT_SET(a, b) : BIT_CLEAR (a, b))

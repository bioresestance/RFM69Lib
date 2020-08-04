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

// Defines bitfields of various widths.
#define BITMASK_BITS(numBits)   BITMASK_ ## numBits ## BITS
#define BITMASK_1BITS   (0b00000001)
#define BITMASK_2BITS   (0b00000011)
#define BITMASK_3BITS   (0b00000111)
#define BITMASK_4BITS   (0b00001111)
#define BITMASK_5BITS   (0b00011111)
#define BITMASK_6BITS   (0b00111111)
#define BITMASK_7BITS   (0b01111111)
#define BITMASK_8BITS   (0b11111111)

/**
 * @brief Gets a wide bitfield based on a value passed in and the desired location.
 * 
 *  @param w Value to modify.
 *  @param x Value to build the bitfield from.
 *  @param y Width of bitfield
 *  @param z Starting location, in bit index.
 * 
 */
#define WIDEBITFIELD_SET_FROM(w, x, y, z)   ( (w) |= ((x) & BITMASK_BITS(y)) << (z)) 

/**
 * @brief Gets a wide bitfield based on a value passed in and the desired location.
 * 
 *  @param x Value to build the bitfield from.
 *  @param y Width of bitfield
 *  @param z Starting location, in bit index.
 * 
 */
#define WIDEBITFIELD_GET_FROM(x, y, z)   (((x) & (BITMASK_BITS(y) << (z))) >> (z)) 

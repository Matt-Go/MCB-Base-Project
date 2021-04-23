/*
 *
 * safety.h
 *
 * This file declares all safety functions for the MCB
 */

#ifndef _SAFETY_H_
#define _SAFETY_H_

// This function will check the output values of each motor and reduce the values to safer ranges
void safety_clamp_outputs(void);

#endif // _SAFETY_H_

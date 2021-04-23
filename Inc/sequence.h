/*
 *
 * sequence.h
 *
 * This file defines structures to implement a re-entrant state machine system,
 * allowing for more complicated processes to be implemented within our
 * main task function without causing blocking delays.
 *
 * USAGE:
 *
 * Create a single, global scope sequence_t structure in your module. In your
 * initialization for your module, use sequence_reset on the module.
 *
 * In your task function for your module, you will have code like the following:
  ```
    if (sequence_do_delay(&fsm, 0, 10)) {
      printf("Done state 0\n");
    }

    if (sequence_do_delay(&fsm, 1, 50)) {
      printf("Done state 1\n");
    }

    if (sequence_do_delay(&fsm, 2, 5)) {
      printf("Done state 2\n");
    }

    if (sequence_do_delay(&fsm, 3, 0)) {
      printf("Done state 3\n");
      sequence_reset(&fsm); // returns to state 0
    }
  ```
 * What this will do is it will run the code in each block only when the state machine
 * is in the correct state, which is automatically updated once the desired amount of
 * time has passed. For tasks that don't always run but still need to follow a set
 * order of instructions (for example, firing from the turret), do the following:
  ```
  if (should_fire) {
    if (sequence_do_delay(&fsm, 0, 0)) {
      // now entered the fire start state
    }
  }
  
  if (sequence_do_delay(&fsm, 1, 10)) {
    // load pellet
  }
  
  if (sequence_do_delay(&fsm, 2, 20) {
    // pressurize chamber
  }
  
  if (sequence_do_delay(&fsm, 3, 20)) {
    // fire pellet!
  }
  
  if (sequence_do_delay(&fsm, 4, 0)) {
    sequence_reset(&fsm); // returns to state 0
  }
  ```
 * This allows the condition to fire to be only need to be on at the start
 * of the sequence while allowing this to be run spread out among multiple
 * method calls.
 */

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "stdint.h"

#define SEQUENCE_RUN 1
#define SEQUENCE_SKIP 0

typedef struct {
  uint32_t state;
  uint32_t start_time;
  uint8_t  waiting;
} sequence_t;

/* This function will return SEQUENCE_RUN if and only if the sequence struct
 * given is able to do the given state (state == s->state), and then will
 * change to the next state after the desired delay has passed.
 *
 * If the function is called on a sequence_t that is in the wrong state,
 * or is currently waiting to move to the next state, it will return SEQUENCE_SKIP.
 *
 * Note: If delay == 0 it will always progress to the next state.
 */
uint8_t sequence_do_delay(sequence_t *s, uint32_t state, uint32_t delay_ms);

// Clears all the entries of a sequence to 0.
void sequence_reset(sequence_t *s);

#endif // _SEQUENCE_H_

/*
 *
 * sequence.c
 *
 * This file defines code to implement a re-entrant state machine system,
 * allowing for more complicated processes to be implemented within our
 * main task function without causing blocking delays.
 */

#include "stdint.h"
#include "sequence.h"
#include "main.h"

uint8_t sequence_do_delay(sequence_t *s, uint32_t state, uint32_t delay_ms) {
  if (s->state != state) {
    // wrong state
    return SEQUENCE_SKIP;
  }
  // we now have that s->state == state
  uint8_t res = SEQUENCE_SKIP;
  if (!s->waiting) {
    // start waiting 
    s->start_time = HAL_GetTick();
    s->waiting = 1;
    res = SEQUENCE_RUN;
  }
  if (s->waiting) {
    uint32_t cur_tick = HAL_GetTick();
    if (delay_ms == 0 || cur_tick - s->start_time >= delay_ms) {
      // done waiting, move to next state
      s->waiting = 0;
      s->state++;
    }
  }
  return res;
}

void sequence_reset(sequence_t *s) {
  s->state = 0;
  s->start_time = 0;
  s->waiting = 0;
}

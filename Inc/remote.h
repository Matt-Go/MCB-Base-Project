/*
 * remote.h
 *
 * This file provides functions declarations and type definitions related to the remote control
 * input that the user uses to drive the robot.
 */
 
#ifndef _REMOTE_H_
#define _REMOTE_H_

#include "stdint.h"

#define REMOTE_DR16_PACKET_LEN 18

typedef struct {
    struct { 
        int16_t ch0;  // right horizontal
        int16_t ch1;  // right vertical
        int16_t ch2;  // left horizontal
        int16_t ch3;  // left vertical
        uint8_t s1;
        uint8_t s2;
    } rc;
    struct {
        int16_t x;
        int16_t y;
        int16_t z;
        uint8_t press_l;
        uint8_t press_r;
    } mouse;
    struct {
        uint16_t v;
    } key;
    volatile uint32_t update_counter;
} remote_info_t; // (taken from 2017 code)



// Parses a buffer the size of an remote_info_t into RC.
// Returns 1 on success, 0 on failure
int remote_parse_buf(uint8_t *buf, remote_info_t *RC);

// Converts an remote_info_t to a human readable string in a given buffer
// len of buffer must be 
void remote_to_string(char *buf, uint32_t len, const remote_info_t *RC);

// Converts an remote_info_t mouse/key data to a human readable string in a given buffer
// len of buffer must be 
void remote_mouse_to_string(char *buf, uint32_t len, const remote_info_t *RC);


// Enable IDLE interrupts
// Not sure what to do with IDLE interrupts, but they seem important.
void remote_uart_it_init(void);

// Returns 1 if r1 == r2
int remote_equals(remote_info_t r1, remote_info_t r2);

#endif // _REMOTE_H_

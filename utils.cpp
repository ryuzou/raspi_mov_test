//
// Created by ryuzo on 2022/03/15.
//

#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <linux/can.h>
#include <linux/can/error.h>
#include <sys/socket.h> /* for sa_family_t */
#define hex_asc_upper_hi(x)	hex_asc_upper[((x) & 0xF0) >> 4]

double convert_byte_to_double(uint8_t (&bytes)[8]) {
    union {
        uint8_t bytes[8];
        double data;
    }Data{};
    for (int i = 0; i < 8; ++i) {
        Data.bytes[i] = bytes[i];
    }
    return Data.data;
}

float convert_byte_to_float(uint8_t (&bytes)[4]) {
    union {
        uint8_t bytes[4];
        float data;
    }Data{};
    for (int i = 0; i < 4; ++i) {
        Data.bytes[i] = bytes[i];
    }
    return Data.data;
}

void convert_float_to_byte(float data, uint8_t (&bytes)[4]) {
    union {
        uint8_t bytes[4];
        float data;
    }Data{};
    Data.data = data;
    for (int i = 0; i < 4; ++i) {
        bytes[i] = Data.bytes[i];
    }
}

void convert_double_to_byte(double data, uint8_t (&bytes)[8]) {
    union {
        uint8_t bytes[8];
        double data;
    }Data{};
    Data.data = data;
    for (int i = 0; i < 8; ++i) {
        bytes[i] = Data.bytes[i];
    }
}



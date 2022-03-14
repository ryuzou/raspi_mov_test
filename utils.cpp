//
// Created by ryuzo on 2022/03/15.
//

#include "utils.h"

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


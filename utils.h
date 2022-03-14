//
// Created by ryuzo on 2022/03/15.
//

#ifndef MOV_TEST_UTILS_H
#define MOV_TEST_UTILS_H

#include <cstdio>
#include <cstdint>

double convert_byte_to_double(uint8_t (&bytes)[8]);
float convert_byte_to_float(uint8_t (&bytes)[4]);
void convert_float_to_byte(float data, uint8_t (&bytes)[4]);
void convert_double_to_byte(double data, uint8_t (&bytes)[8]);

#endif //MOV_TEST_UTILS_H

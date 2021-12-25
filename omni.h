//
// Created by ryuzo on 2021/12/25.
//

#ifndef MOV_TEST_OMNI_H
#define MOV_TEST_OMNI_H

#include <cmath>
#define  Pi 3.14159265


class wheel {
public:
    wheel();
    double Motor[4];//各タイヤの各速度
    void motor_main(float v, float direction, float w);

private:
    double l = 0.3;//機体中心から各タイヤまでの距離[m]
    double r = 0.08;//タイヤの半径[m]
};


#endif //MOV_TEST_OMNI_H

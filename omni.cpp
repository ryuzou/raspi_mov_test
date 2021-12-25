//
// Created by ryuzo on 2021/12/25.
//

#include "omni.h"

using namespace std;

wheel::wheel() {}

//速度[m/s]、行きたい方向[degree],機体の角速度[rad/s]を受け取り、最後に各タイヤの角速度[rad/s]を返す
void wheel::motor_main(float v, float direction, float w){
    if (direction > 360) {
        direction = 360;
    }
    else {
        direction = direction;
    }
    double x = v * cos((direction - 45)*Pi/180);
    double y = v * sin((direction - 45)*Pi/180);

    //角速度計算
    Motor[0] = y / (2 * r) + l * w / r;
    Motor[1] = -x / (2 * r) + l * w / r;
    Motor[2] = -y / (2 * r) + l * w / r;
    Motor[3] = x / (2 * r) + l * w / r;

    //各タイヤの各速度が定格rpmを上回らないようにする
    if (Motor[0] > 1926 ) {
        Motor[0] = 1800;
    }
    else if (Motor[0] < -1926){
        Motor[0] = -1800;
    }

    if (Motor[1] > 1926 ) {
        Motor[1] = 1800;
    }
    else if (Motor[1] < -1926){
        Motor[1] = -1800;
    }

    if (Motor[2] > 1926 ) {
        Motor[2] = 1800;
    }
    else if (Motor[2] < -1926){
        Motor[2] = -1800;
    }

    if (Motor[3] > 1926 ) {
        Motor[3] = 1800;
    }
    else if (Motor[3] < -1926){
        Motor[3] = -1800;
    }

}

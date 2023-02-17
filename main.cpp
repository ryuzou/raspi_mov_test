#include <iostream>
#include "omni.h"
#include "tcp.h"
#include "utils.h"
#include "json.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <net/if.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define pi 3.14159265

/*
 * MCU Placement
 *
 * v2   v1
 *
 * v3   v4
 */

//#define MECHANAM

#define STEAR

using json = nlohmann::json;

short f32tof16(float a){
    return
            (*(int*)&a >> 31 & 0b1) << 15 |
            ((*(int*)&a >> 23 & 0b11111111) - 127 + 15) << 10 |
            (*(int*)&a >> 13 & 0b1111111111);
}

float f16tof32(short a){
    int b =
            (a >> 15 & 0b1) << 31 |
            ((a >> 10 & 0b11111) - 15 + 127 ) << 23 |
            (a & 0b1111111111) << 13;
    return *(float*)&b;
}

short convert_byte_to_f16(uint8_t(&bytes)[2]){
    union {
        uint8_t bytes[2];
        short data;
    }Data{};
    for (int i = 0; i < 2; ++i) {
        Data.bytes[i] = bytes[i];
    }
    return Data.data;
}

void convert_f16_to_byte(short data, uint8_t(&bytes)[2]){
    union {
        uint8_t bytes[2];
        short data;
    }Data{};
    Data.data = data;
    for (int i = 0; i < 2; ++i) {
        bytes[i] = Data.bytes[i];
    }
}
int move_can(){
    //tcp connection setup.
    const char *connected_adder;
    std::string recieveData;
    tcp tcp(8000);
    tcp.receive_setup();
    connected_adder = tcp.connect();
    std::cout << "Connected from " << connected_adder << std::endl;

    //can init.
    int s;
    struct sockaddr_can addr{};
    struct ifreq ifr{};

    struct canfd_frame frame{};
    frame.can_id = 0x101;
    frame.len = 16;
    for (int i = 0; i < 16; ++i) {
        frame.data[i] = i;
    }


    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (ioctl(s, SIOCGIFMTU, &ifr) < 0) {
        perror("SIOCGIFMTU");
        return 1;
    }
    int mtu = ifr.ifr_mtu;

    if (mtu != CANFD_MTU) {
        printf("CAN interface is not CAN FD capable - sorry.\n");
        return 1;
    }

    int enable_canfd = 1;
    /* interface is ok - try to switch the socket into CAN FD mode */
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable_canfd, sizeof(enable_canfd));

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }

    //tcp and omni init.
    float v = 100;
    float direction = 0;
    float w = 0;

    wheel wheel_cal;
    double omega = 0;

    float v1, v2, v3, v4 = 0;
    // initial connection
    while (true) {
        recieveData = tcp.recieve_lines();
        json j = json::parse(recieveData);

        double x_val = j["x"];
        double y_val = j["y"];
        double rad = j["rad"];

        // int buttun1 = j["button"]["1"];
        // printf("%d\n\r", buttun1);

#ifdef MECHANAM
        v1 = -1 * x_val + 1 * y_val + rad;
        v2 = 1 * x_val + 1 * y_val - rad;
        v3 = -1 * x_val + 1 * y_val - rad;
        v4 = 1 * x_val + 1 * y_val + rad;
#endif

#ifdef STEAR
        omega = rad;
        float R = 0.4;
        float vk[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
        for (int i = 0; i < 4; ++i) {
            vk[i][1] = x_val - omega*R*sin((2*i - 1)*pi/4);
            vk[i][2] = y_val + omega*R*cos((2*i - 1)*pi/4);
            vk[i][0] = atan2(vk[i][2],vk[i][1]);
        }
        v1 = sqrt(vk[0][1]*vk[0][1]+vk[0][2]*vk[0][2]);
        v2 = sqrt(vk[1][1]*vk[1][1]+vk[1][2]*vk[1][2]);
        v3 = sqrt(vk[2][1]*vk[2][1]+vk[2][2]*vk[2][2]);
        v4 = sqrt(vk[3][1]*vk[3][1]+vk[3][2]*vk[3][2]);


#endif

        uint8_t _send_bytes[16];
        uint8_t _tmp_bytes[4];
        convert_float_to_byte(v1, _tmp_bytes);
        for (int i = 0; i < 4; ++i) {
            _send_bytes[i] = _tmp_bytes[i];
        }
        convert_float_to_byte(v2, _tmp_bytes);
        for (int i = 0; i < 4; ++i) {
            _send_bytes[i + 4] = _tmp_bytes[i];
        }
        convert_float_to_byte(v3, _tmp_bytes);
        for (int i = 0; i < 4; ++i) {
            _send_bytes[i + 8] = _tmp_bytes[i];
        }
        convert_float_to_byte(v4, _tmp_bytes);
        for (int i = 0; i < 4; ++i) {
            _send_bytes[i + 12] = _tmp_bytes[i];
        }
        for (int i = 0; i < 16; ++i) {
            frame.data[i] = _send_bytes[i];
        }
        while (true){
            if (write(s, &frame, sizeof(struct canfd_frame)) != sizeof(struct canfd_frame)) {
                perror("Write frame");
                usleep(100);
            } else{
                break;
            }
        }
    }


    return 0;
}

int main(int argc, char **argv) {
    move_can();
    return 0;
}

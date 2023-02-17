#include <iostream>
#include "omni.h"
#include "tcp.h"
#include "utils.h"
#include "json.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdint>

#include <net/if.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

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

    struct can_frame frame{};
    frame.can_id = 0x101;
    frame.can_dlc = 8;


    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }

    //tcp and omni init.
    float v = 100;
    float direction = 0;
    float w = 0;

    wheel wheel_cal;

    // initial connection
    recieveData = tcp.recieve_lines();
    while (true) {
        recieveData = tcp.recieve_lines();
        json j = json::parse(recieveData);

        double x_val = j["x"];
        double y_val = j["y"];
        float v1 = -1 * x_val + 1 * y_val;
        float v2 = 1 * x_val + 1 * y_val;
        float v3 = -1 * x_val + 1 * y_val;
        float v4 = 1 * x_val + 1 * y_val;

        uint8_t _send_bytes[8];
        uint8_t _tmp_bytes[2];
        convert_f16_to_byte(v1, _tmp_bytes);
        for (int i = 0; i < 2; ++i) {
            _send_bytes[i] = _tmp_bytes[i];
        }
        convert_f16_to_byte(v2, _tmp_bytes);
        for (int i = 0; i < 2; ++i) {
            _send_bytes[i + 2] = _tmp_bytes[i];
        }
        convert_f16_to_byte(v3, _tmp_bytes);
        for (int i = 0; i < 2; ++i) {
            _send_bytes[i + 4] = _tmp_bytes[i];
        }
        convert_f16_to_byte(v4, _tmp_bytes);
        for (int i = 0; i < 2; ++i) {
            _send_bytes[i + 6] = _tmp_bytes[i];
        }
        for (int i = 0; i < 8; ++i) {
            frame.data[i] = _send_bytes[i];
        }
        while (true){
            if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
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

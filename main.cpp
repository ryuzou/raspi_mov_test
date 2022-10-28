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

using json = nlohmann::json;

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
    struct can_frame frame0{};
    struct can_frame frame1{};
    struct can_frame frame2{};
    struct can_frame frame3{};
    frame0.can_id = 0x101;
    frame1.can_id = 0x102;
    frame2.can_id = 0x103;
    frame3.can_id = 0x104;
    frame0.can_dlc = frame1.can_dlc = frame2.can_dlc = frame3.can_dlc = 8;


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

        double v1, v2, v3, v4;
        v1 = double(j["paramaters"]["1"]["axis"]) * double(j["paramaters"]["1"]["ratio"])/100 * double(j["v1"]);
        v2 = double(j["paramaters"]["2"]["axis"]) * double(j["paramaters"]["2"]["ratio"])/100 * double(j["v2"]);
        v3 = double(j["paramaters"]["3"]["axis"]) * double(j["paramaters"]["3"]["ratio"])/100 * double(j["v3"]);
        v4 = double(j["paramaters"]["4"]["axis"]) * double(j["paramaters"]["4"]["ratio"])/100 * double(j["v4"]);

        convert_double_to_byte(v1, frame0.data);
        convert_double_to_byte(v2, frame1.data);
        convert_double_to_byte(v3, frame2.data);
        convert_double_to_byte(v4, frame3.data);


        while (true){
            if (write(s, &frame0, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                perror("Write frame0");
                usleep(100);
            } else{
                break;
            }
        }
        while (true){
            if (write(s, &frame1, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                perror("Write frame1");
                usleep(100);
            } else{
                break;
            }
        }
        while (true){
            if (write(s, &frame2, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                perror("Write frame2");
                usleep(100);
            } else{
                break;
            }
        }
        while (true){
            if (write(s, &frame3, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                perror("Write frame3");
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

#include <iostream>
#include "omni.h"
#include "tcp.h"
#include "utils.h"
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdint>

#include <net/if.h>
#include <sys/socket.h>

#include <linux/can.h>

int main(int argc, char **argv) {

    //can init.

    int s;
    struct sockaddr_can addr{};
    struct ifreq ifr{};
    struct can_frame frame0{};
    struct can_frame frame1{};
    struct can_frame frame2{};
    struct can_frame frame3{};
    frame0.can_id = 0x100;
    frame1.can_id = 0x101;
    frame2.can_id = 0x102;
    frame3.can_id = 0x103;
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
    //tcp connection setup.
    const char *connected_adder;
    /*std::string recieveData;
    tcp tcp(8000);
    tcp.receive_setup();
    connected_adder = tcp.connect();
    std::cout << "Connected from " << connected_adder << std::endl;

    // initial connection
    recieveData = tcp.recieve_lines();*/
    int radius = std::stoi(argv[1]);
    int degree = std::stoi(argv[2]);

    while (true) {
        char delm = ',';
        /*recieveData = tcp.recieve_lines();
        int counter = 0;
        for (char ch: recieveData) {
            if (ch == delm) {
                radius = std::stoi(recieveData.substr(0, counter));
                degree = std::stoi(recieveData.substr(counter + 1));
            }
            counter++;
        }*/
        wheel_cal.motor_main(radius, degree, w);
        std::cout << wheel_cal.Motor[0] << "," << wheel_cal.Motor[1] << "," << wheel_cal.Motor[2] << ","
                  << wheel_cal.Motor[3] << std::endl;

        convert_double_to_byte(wheel_cal.Motor[0], frame0.data);
        convert_double_to_byte(wheel_cal.Motor[1], frame1.data);
        convert_double_to_byte(wheel_cal.Motor[2], frame2.data);
        convert_double_to_byte(wheel_cal.Motor[3], frame3.data);


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
                perror("Write frame0");
                usleep(100);
            } else{
                break;
            }
        }
        while (true){
            if (write(s, &frame3, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                perror("Write frame0");
                usleep(100);
            } else{
                break;
            }
        }
    }

    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}

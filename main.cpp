#include <iostream>
#include "omni.h"
#include "tcp.h"
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdint>

#include <net/if.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <linux/can.h>


#define SERIAL_PORT "/dev/ttyACM0"

int main(int argc, char *argv[])
{
    unsigned char msg[] = "serial port open...\n";
    unsigned char buf[9];             // バッファ
    int fd;                             // ファイルディスクリプタ
    struct termios tio;                 // シリアル通信設定
    int baudRate = B115200;
    int i;
    int len;
    int ret;
    int size;

    fd = open(SERIAL_PORT, O_RDWR);     // デバイスをオープンする
    if (fd < 0) {
        printf("open error\n");
        return -1;
    }

    tio.c_cflag += CREAD;               // 受信有効
    tio.c_cflag += CLOCAL;              // ローカルライン（モデム制御なし）
    tio.c_cflag += CS8;                 // データビット:8bit
    tio.c_cflag += 0;                   // ストップビット:1bit
    tio.c_cflag += 0;                   // パリティ:None

    cfsetispeed( &tio, baudRate );
    cfsetospeed( &tio, baudRate );

    cfmakeraw(&tio);                    // RAWモード

    tcsetattr( fd, TCSANOW, &tio );     // デバイスに設定を行う

    ioctl(fd, TCSETS, &tio);            // ポートの設定を有効にする

    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04;
    buf[4] = 0x05;
    buf[5] = 0x06;
    buf[6] = 0x07;
    buf[7] = 0x08;
    buf[8] = 0x09;
    while(1) {
        write(fd, buf, 9);
        usleep(100);
    }

    close(fd);                              // デバイスのクローズ
    return 0;
}

/*
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
    frame0.can_dlc = frame1.can_dlc = frame2.can_dlc = frame3.can_dlc = 4;

    union {
        float f;
        uint8_t Data[8];
    } data0{};

    union {
        float f;
        uint8_t Data[8];
    } data1{};

    union {
        float f;
        uint8_t Data[8];
    } data2{};

    union {
        float f;
        uint8_t Data[8];
    } data3{};


    printf("CAN Sockets Demo\r\n");

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
    std::string recieveData;
    tcp tcp(8000);
    tcp.receive_setup();
    connected_adder = tcp.connect();
    std::cout << "Connected from " << connected_adder << std::endl;

    // initial connection
    recieveData = tcp.recieve_lines();
    int radius = 0;
    int degree = 0;

    while (1) {
        char delm = ',';
        recieveData = tcp.recieve_lines();
        int counter = 0;
        for (char ch: recieveData) {
            if (ch == delm) {
                radius = std::stoi(recieveData.substr(0, counter));
                degree = std::stoi(recieveData.substr(counter + 1));
            }
            counter++;
        }
        wheel_cal.motor_main(radius, degree, w);
        std::cout << wheel_cal.Motor[0] << "," << wheel_cal.Motor[1] << "," << wheel_cal.Motor[2] << ","
                  << wheel_cal.Motor[3] << std::endl;

        data0.f = wheel_cal.Motor[0];
        data1.f = wheel_cal.Motor[1];
        data2.f = wheel_cal.Motor[2];
        data3.f = wheel_cal.Motor[3];

        for (int i = 0; i < 8; ++i) {
            frame0.data[i] = data0.Data[i];
        }
        for (int i = 0; i < 8; ++i) {
            frame1.data[i] = data1.Data[i];
        }
        for (int i = 0; i < 8; ++i) {
            frame2.data[i] = data2.Data[i];
        }
        for (int i = 0; i < 8; ++i) {
            frame3.data[i] = data3.Data[i];
        }



        if (write(s, &frame0, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
            perror("Write frame0");
            usleep(10);
        }
        if (write(s, &frame1, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
            perror("Write frame1");
            usleep(10);
        }
        if (write(s, &frame2, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
            perror("Write frame2");
            usleep(10);
        }
        if (write(s, &frame3, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
            perror("Write frame3");
            usleep(10);
        }

        if (radius == 0){
            for (int i = 0; i < 10; ++i) {
                if (write(s, &frame0, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                    perror("Write frame0");
                    usleep(10);
                }
                if (write(s, &frame1, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                    perror("Write frame1");
                    usleep(10);
                }
                if (write(s, &frame2, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                    perror("Write frame2");
                    usleep(10);
                }
                if (write(s, &frame3, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                    perror("Write frame3");
                    usleep(10);
                }
            }
        }
    }

    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}*/

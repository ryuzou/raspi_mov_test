#include <iostream>
#include "omni.h"
#include "tcp.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/ttyACM0"



int main() {
    unsigned char buf[255];             // バッファ
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

    // 送受信処理ループ
    while(1) {
        len = read(fd, buf, sizeof(buf));
        if (0 < len) {
            for(i = 0; i < len; i++) {
                printf("%c", buf[i]);
            }
            printf("\n");
        }
        write(fd, buf, len);
    }

    close(fd);
    float v = 100;
    float direction = 0;
    float w = 0;

    wheel wheel_cal;
    //tcp connection setup.
    const char *connected_adder;
    std::string recieve_data;
    tcp tcp(8000);
    tcp.receive_setup();
    connected_adder = tcp.connect();
    std::cout << "Connected from " << connected_adder << std::endl;

    // initial connection
    recieve_data = tcp.recieve_lines();
    int radius = 0;
    int degree = 0;
    while (1){
        char delm = ',';
        recieve_data = tcp.recieve_lines();
        int counter = 0;
        for (char ch:recieve_data){
            if (ch == delm){
                radius = std::stoi(recieve_data.substr(0, counter));
                degree = std::stoi(recieve_data.substr( counter + 1));
            }
            counter++;
        }
        wheel_cal.motor_main(radius,degree,w);
        std::cout << wheel_cal.Motor[0] << ","<< wheel_cal.Motor[1] << ","<< wheel_cal.Motor[2] << ","<< wheel_cal.Motor[3] << std::endl;
    }
    return 0;
}

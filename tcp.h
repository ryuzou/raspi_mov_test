//
// Created by ryuzo on 2021/12/25.
//

#ifndef MOV_TEST_TCP_H
#define MOV_TEST_TCP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "errorhandling.h"

#define BUFFER_SIZE 256

class tcp {
    int orgSock{};
    int dstSock{};
    struct sockaddr_in origin_addr{};
    struct sockaddr_in destination_addr{};
    int numrcv{};
    char buffer[BUFFER_SIZE]{};

public:
    explicit tcp(const int port){
        orgSock = socket(AF_INET, SOCK_STREAM, 0);
        memset(&origin_addr, 0, sizeof(struct sockaddr_in));
        origin_addr.sin_family = AF_INET;
        origin_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        origin_addr.sin_port = htons(port);
    }

    int receive_setup(){
        bind(orgSock, (struct sockaddr *)&origin_addr, sizeof(origin_addr));
        listen(orgSock, 1);
        return 0;
    }

    /**
    int send_setup(const char *_destination_addr, int port){
        inet_pton(AF_INET, _destination_addr, &destination_addr.sin_addr);
        destination_addr.sin_port = htons(port);
        return 0;
    }**/

    /**
    int send_content(const std::string& content){
        send(dstSock, content.c_str(), content.length(), 0);
        return 0;
    }**/
    std::basic_string<char> recieve_lines(){
        ssize_t i, rc;
        char c;
        std::string lineString("");
        logger log(LOGLEVEL_DEBUG);
        for (i = 1; i < MAXLINE; ++i) {
            rc = read(dstSock, &c, 1);
            if (rc == 1){
                lineString += c;
                if (c == '\n'){
                    break;
                }
            } else if (rc == 0){
                if (i == 1){
                    return const_cast<char *>(std::string("").c_str());
                } else {
                    break;
                }
            } else {
                close(dstSock);
                log.error("Connection error:.");
            }
        }
        return lineString;
    }

    const char *connect() {
        logger log(LOGLEVEL_DEBUG);
        socklen_t len = sizeof(destination_addr);
        dstSock = accept(orgSock, (struct sockaddr *)&destination_addr, &len);
        if (dstSock == -1){
            log.error("accept failed:.");
        }
        return inet_ntop(AF_INET, &destination_addr.sin_addr, buffer, sizeof(buffer));
    }

    ~tcp(){
        close(orgSock);
    }
};

#endif //MOV_TEST_TCP_H

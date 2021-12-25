//
// Created by ryuzo on 2021/12/25.
//

#ifndef MOV_TEST_ERRORHANDLING_H
#define MOV_TEST_ERRORHANDLING_H

#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>

#define MAXLINE 4096
#define LOGLEVEL_DEBUG 0
#define LOGLEVEL_RELEASE 1


class logger {
private:
    enum log_level {
        DEBUG,
        RELEASE,
    };
    enum log_level level;
public:
    logger(const short int logLevel) {
        switch (logLevel) {
            case 0:
                level = DEBUG;
                break;
            case 1:
                level = RELEASE;
                break;
            default:
                level = RELEASE;
                break;
        }
    }

    logger();

    void log(const char *content) {
        char buf[MAXLINE + 1];
        snprintf(buf, sizeof(buf), "%s", content);
    }

    void debug(const char *content) {
        if (level == DEBUG) {
            char buf[MAXLINE + 1];
            snprintf(buf, sizeof(buf), "%s", content);
        }
    }

    void error(const char *content) {
        char buf[MAXLINE + 1];
        snprintf(buf, sizeof(buf), "%s", content);
        perror(buf);
        exit(1);
    }
};

#endif //MOV_TEST_ERRORHANDLING_H

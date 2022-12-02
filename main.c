#include "clog.h"
#include "ev.h"
#include "serial.h"
#include "stdin.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>


#define DEV "/dev/ttyUSB0"
#define MAXEVENTS 10
#define BUFFSIZE 2048


int 
main() {
    int i;
    int fd;
    int sfd;
    int fdcount;
    char buff[BUFFSIZE];
    ssize_t bytes;
    struct epoll_event events[MAXEVENTS];
    struct epoll_event *e;

    if (ev_init()) {
        FATAL("ev_init()");
    }


    if (stdin_init()) {
        FATAL("stdin_init()");
    }

    sfd = serial_open(DEV);
    if (sfd == -1) {
        FATAL("serial_open()");
    }

    /* Main Loop */
    while (1) {
        fdcount = ev_wait(events, MAXEVENTS);
        if (fdcount == -1) {
            FATAL("epoll_wait returned: %d", fdcount);
        }
        
        for (i = 0; i < fdcount; i++) {
            e = &events[i];
            fd = e->data.fd;

            if (e->events & EPOLLERR) {
                FATAL("File error: %d", fd);
            }

            if (fd == STDIN_FILENO) {
                // DEBUG("Read input");
                bytes = read(STDIN_FILENO, buff, BUFFSIZE);
                if (bytes <= 0) {
                    FATAL("stdin");
                }
                if (write(sfd, buff, bytes) != bytes) {
                    FATAL("Serial write");
                }
            }
            else if (fd == sfd) {
                // DEBUG("Read serial");
                bytes = read(sfd, buff, BUFFSIZE);
                if (bytes <= 0) {
                    FATAL("serial");
                }
                if (write(STDOUT_FILENO, buff, bytes) != bytes) {
                    FATAL("stdout");
                }
            } 
        }
    }
    return EXIT_SUCCESS;
}

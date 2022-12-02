#include "ev.h"

#include <clog.h>
#include <sys/epoll.h>


int evfd;


int 
ev_init() {
    // Create epoll instance
    evfd = epoll_create1(0);
    if (evfd == -1) {
        ERROR("Cannot create epoll file descriptor");
        return -1;
    }
    return 0;
}


int 
ev_add(int fd, int op) {
    struct epoll_event ev;

    ev.events = op | EPOLLRDHUP | EPOLLERR;
    ev.data.fd = fd;
    if (epoll_ctl(evfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        ERROR("epoll_ctl: EPOLL_CTL_ADD, serial interface");
        return -1;
    }
    return 0;
}

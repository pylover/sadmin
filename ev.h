#ifndef EV_H
#define EV_H


#include <sys/epoll.h>


int 
ev_init();


int 
ev_add(int fd, int op);


int
ev_wait(struct epoll_event *events, int maxevents);


#endif

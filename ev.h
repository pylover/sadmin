#ifndef EV_H
#define EV_H


extern int evfd;


int 
ev_init();


int 
ev_add(int fd, int op);


#endif

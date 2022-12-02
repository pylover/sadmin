#include "stdin.h"
#include "ev.h"

#include <clog.h>
#include <termios.h>
#include <unistd.h>
#include <sys/epoll.h>


struct termios _ttystate_back;


int stdin_init() {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
    _ttystate_back = ttystate;

    // turn off canonical mode and echo
    ttystate.c_lflag &= ~ICANON;

    // minimum of number input read.
    ttystate.c_cc[VMIN] = 1;

    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    if (ev_add(STDIN_FILENO, EPOLLIN)) {
        ERROR("ev_add");
        return -1;
    }
    return 0;
}

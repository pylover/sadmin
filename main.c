#include "clog.h"
#include "serial.h"

#include <stdio.h>
#include <stdlib.h>


#define DEV "/dev/ttyUSB0"


int main() {
    int sfd;

    sfd = serial_open(DEV);
    if (sfd == -1) {
    }
    return EXIT_SUCCESS;
}

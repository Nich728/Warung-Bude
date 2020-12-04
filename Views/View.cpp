#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Controllers/controller.h"

int main(void) {
    extern int terminated;
    do {
        printf("%s\n", getOS());
        printStart();
        cls();
    } while (!terminated);
    return 0;
}

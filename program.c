#include "Models/control.c"
#include <stdio.h>

struct Control ctrl;

int main(int argc, char const *argv[])
{
    if (argc < 9)
    {
        printf("Missing parameters\n");
        return -1;
    }

    ctrl = getControl(argv);

    return 0;
}

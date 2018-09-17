#include <stdio.h>
#include "Models/Control.c"
#include "Models/Stack.c"

struct Control ctrl;
struct Stack* stack;

int main(int argc, char const *argv[])
{
    if (argc < 9)
    {
        printf("Missing parameters\n");
        return -1;
    }

    ctrl = getControl(argv);
    stack = createStack(5);

    

    return 0;
}

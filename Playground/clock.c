#include <time.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{    
    time_t now = time(0);
    struct tm *tm = localtime(&now);

    int t = tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;

    printf("%d\n", t);

    return 0;
}

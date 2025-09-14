#include "time.h"
#include <sys/time.h>  // gettimeofday
#include <stddef.h>

long long current_time_ms(void) {
// Function to get the current time in milliseconds. It receives no parameters and returns a long long integer representing the current time in milliseconds.
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

#include "time.h"
#include <sys/time.h>  // gettimeofday
#include <stddef.h>

// Function to get the current time in milliseconds
long long current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

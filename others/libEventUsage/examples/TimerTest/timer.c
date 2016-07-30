#include <sys/types.h>
#include <event2/event-config.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>

struct timeval lasttime;
int event_persist;

static void timeout_cb(evutil_socket_t fd, short event, void *arg) {

    struct timeval newtime, diff;
    struct event *timeout = (struct event *) arg;
    double elapsed;

    evutil_gettimeofday(&newtime, NULL);
    evutil_timersub(&newtime, &lasttime, &diff);
    elapsed = diff.tv_sec + (diff.tv_usec) / 1.0e6;
    printf("time reached! The Elapsed time is %f\n", elapsed);
    lasttime = newtime;
    if (!event_persist) {
        struct timeval tv;
        evutil_timerclear(&tv);
        tv.tv_sec = 2;
        event_add(timeout, &tv);
    }
}

int main(int argc, char ** argv) {
    struct event timeout;
    struct timeval tv;
    struct event_base *base;
    int flags;
    if (argc == 2 && !strcmp(argv[1], "-p")) {
        event_persist = 1;
        flags = EV_PERSIST;
    } else {
        event_persist = 0;
        flags = 0;
    }

    base = event_base_new();
    event_assign(&timeout, base, -1, flags, timeout_cb, (void *) &timeout);

    evutil_timerclear(&tv);
    tv.tv_sec = 2;
    event_add(&timeout, &tv);

    evutil_gettimeofday(&lasttime, NULL);
    event_base_dispatch(base);
    return 0;
}
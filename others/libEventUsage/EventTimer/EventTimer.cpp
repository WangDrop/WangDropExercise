/*************************************************************************
	> File Name: EventTimer.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年06月30日 星期四 17时30分16秒
 ************************************************************************/

#include<iostream>
#include<event2/event.h>
#include<event2/util.h>
#include<cstdlib>
#include<unistd.h>
#include<cstdio>
using namespace std;

struct EventTimerVal{
    struct timeval tv;
    void * argv;
    void * ev;
};


void timerEventHandler(evutil_socket_t fd, short events, void * argv)
{
    cout << "Timer Wake Up!" << endl;
    EventTimerVal * eventVal = (EventTimerVal *)argv;
    eventVal->tv.tv_sec = 1;
    //add event again
    evtimer_add((struct event *)eventVal->ev, &eventVal->tv);
}

int main()
{
    struct event_base * base = event_base_new();
    EventTimerVal eventTimerVal;
    struct event * eventTimer = evtimer_new(base, timerEventHandler, &eventTimerVal);
    eventTimerVal.tv.tv_sec = 1;
    eventTimerVal.argv = NULL;
    eventTimerVal.ev = eventTimer;
    
    evtimer_add((struct event *)eventTimerVal.ev, &eventTimerVal.tv);
    int err = event_base_dispatch(base);
    cout << err << endl;
    return 0;
}

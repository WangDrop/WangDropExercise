#include "string.h"
#include "stdio.h"
#include "errno.h"
#include "signal.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"

static const char MESSAGE[] = "HELLO WORLD!";
static const int PORT = 9995;

static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);

static void conn_writecb(struct bufferevent *, void *);

static void conn_eventcb(struct bufferevent *, short, void *);

static void signal_cb(evutil_socket_t, short, void *);

int main(int argc, char argv) {
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;
    struct sockaddr_in sin;
    base = event_base_new();
    if (!base) {
        fprintf(stderr, "connot init the event base!\n");
        return 1;
    }

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    //省去了,socket,bind,listen这几个步骤，直接使用connlistener_new_bind完成
    //_OPT_REUSEABLE：表示重用socket
    //LET_OPT_CLOSE_ON_FREE: 连接释放之后关闭socket
    listener = evconnlistener_new_bind(base, listener_cb, (void *) base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr *) &sin, sizeof(sin));
    if (!listener) {
        fprintf(stderr, "create server listener failed!\n");
        return 1;
    }

    //创建一个新的signal_event，绑定到_event_base上面
    signal_event = evsignal_new(base, SIGINT, signal_cb, (void *) base);

    if (!signal_event || event_add(signal_event, NULL) < 0) {
        fprintf(stderr, "Could not create or add a signal event!\n");
        return 1;
    }

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);

    printf("Everything Done!\n");
    return 0;
}

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sin, int socklen,
                        void *user_date) {
    struct event_base *base = (struct event_base *) user_date;
    struct bufferevent *bev;
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        fprintf(stderr, "Error create buffer event!\n");
        event_base_loopbreak(base);
        return;
    }
    bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
    //监听写事件，关闭读事件
    bufferevent_enable(bev, EV_WRITE);
    bufferevent_disable(bev, EV_READ);

    //向buffer上面写数据
    bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

static void conn_writecb(struct bufferevent *bev, void *user_data) {
    //得到写缓冲区
    struct evbuffer *buffer = bufferevent_get_output(bev);
    if (evbuffer_get_length(buffer) == 0) {
        printf("flushed answer!\n");
        bufferevent_free(bev);
    }
}

static void conn_eventcb(struct bufferevent *bev, short events, void *user_date) {
    if (events & BEV_EVENT_EOF) {
        printf("connection closed!\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("Got an error on the connection: %s\n", strerror(errno));
    }
    bufferevent_free(bev);
}

static void signal_cb(evutil_socket_t sig, short events, void *user_date) {
    struct event_base *base = (struct event_base *) user_date;
    struct timeval delay = {2, 0};
    printf("caught Interruput signal! exit and clean in two second!\n");
    event_base_loopexit(base, &delay);
}


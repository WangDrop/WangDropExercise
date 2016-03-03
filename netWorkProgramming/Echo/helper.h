/*************************************************************************
	> File Name: helper.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月18日 星期一 15时57分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 8888
void perr_exit(const char *s)
{
    perror(s);
    exit(1);

}
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;
    again:
    if ( (n = accept(fd, sa, salenptr)) < 0 ) {
        if ((errno == ECONNABORTED) || (errno == EINTR))
        goto again;
        else
        perr_exit("accept error");

    }
    return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
    perr_exit("bind error");

}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
    perr_exit("connect error");

}

void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
    perr_exit("listen error");

}

int Socket(int family, int type, int protocol)
{
    int n;
    if ( (n = socket(family, type, protocol)) < 0 )
    perr_exit("socket error");
    return n;

}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;
    again:
    if ( (n = read(fd, ptr, nbytes)) == -1 ) {
        if (errno == EINTR)
        goto again;
        else
        return -1;

    }
    return n;

}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
    ssize_t n;
    again:
    if ( (n = write(fd, ptr, nbytes)) == -1 ) {
        if (errno == EINTR)
        goto again;
        else
        return -1;

    }
    return n;

}

void Close(int fd)
{
    if (close(fd) == -1)
    perr_exit("close error");

}

int Fork()
{
    int id = 0;
    if((id = fork()) < 0){
        perr_exit("fork error!");
    }
    return id;
}

/*
ssize_t  Read(int fd, void * buf, size_t count)
{
    ssize_t count;
    if((count = read(fd, buf, count)) < 0){
        perr_exit("Read error!");
    }
    return count;
}
*/

size_t Readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char
    *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0 ) {
            if (errno == EINTR)
            nread = 0;
            else
            return -1;

        } else if (nread == 0)
        break;
        nleft -= nread;
        ptr += nread;

    }
    return n - nleft;

}

ssize_t Writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0 ) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else 
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

int Inet_pton(int af, const char * src, void * dst)
{
    int ret;
    if((ret = inet_pton(af, src, dst)) < 0)
        perr_exit("Inet_pton error!\n");
    return ret;
    
}


static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static * read_ptr;
    static read_buf[100];
    if (read_cnt <= 0) {
        again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0 ) {
            if (errno == EINTR)
            goto again;
            return -1;
        } 
        else if (read_cnt == 0)
            return 0;
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;

}

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;
    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1 ) {
        *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return n - 1;
        }else
            return -1;
    }
    *ptr = 0;
    return n;
}

char *  Fgets(char * buf, int bufsize, FILE * stream)
{
    char * ptr;
    if((ptr = fgets(buf, bufsize, stream)) == NULL){
        if(feof(stream) == 1){
            return NULL;
        }else
            perr_exit("fgets error!\n");
    }
    return ptr;
}

int Fputs(const char * s, FILE * stream)
{
    int cnt;
    if((cnt = fputs(s, stream)) == EOF){
        perr_exit("fputs error !\n");
    }
    return cnt; 
}

int Recvfrom(int s, void * buf, int len, unsigned int flags, struct sockaddr * from, int * fromlen)
{
    int cnt;
again:
    if((cnt = recvfrom(s, buf, len, flags, from, fromlen)) < 0){
        if(errno == EINTR)
            goto again;
        else
            perr_exit("recvfrom error!\n");
    }
    return cnt;
}

int Sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen)
{
    int cnt;
again:
    if((cnt = sendto(s, msg, len, flags, to, tolen)) < 0){
        if(errno == EINTR)
            goto again;
        else
            perr_exit("sendto error!\n");
    }
    return cnt;
}


int bzero(void * addr, size_t n)
{
    memset(addr, 0, n);
}

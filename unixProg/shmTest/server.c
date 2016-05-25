/*************************************************************************
	> File Name: shmTest.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月24日 星期二 20时26分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

//计数器结构体
struct shmstruct
{
    int     count;
};
//同步有名信号量
sem_t  *mutex;

int main(int argc,char *argv[])
{
    int     fd;
    struct  shmstruct *ptr;
    if(argc != 3)
    {
        printf("usage: server1 <shmname> <semname>.\n");
        exit(0);
    }
    //防止所需共享内存区对象已经存在
    shm_unlink(argv[1]);
    //创建一个新的共享内存区对象
    if((fd = shm_open(argv[1],O_RDWR | O_CREAT | O_EXCL,FILE_MODE)) == -1)
    {
        perror("shm_open error");
        exit(-1);
    }
    //指定新创建的共享内存区对象的大小
    ftruncate(fd,sizeof( struct shmstruct));
    //将新创建的共享内存区映射到调用进程的地址空间
    if((ptr = mmap(NULL,sizeof(struct shmstruct),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0)) == MAP_FAILED)
    {
        perror("mmap error");
        exit(-1);
    }
    //关闭对象描述符
    close(fd);
    //防止所需的信号量已经存在
    sem_unlink(argv[2]);
    //创建有名信号量，作为互斥锁用
    if((mutex = sem_open(argv[2],O_CREAT|O_EXCL,FILE_MODE,1)) == SEM_FAILED)
    {
        perror("sem_open error");
        exit(-1);
    }
    //关闭信号量
    sem_close(mutex);
    exit(0);
} 

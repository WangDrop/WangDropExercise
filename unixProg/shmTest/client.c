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

struct shmstruct
{
    int     count;
};

sem_t  *mutex;

int main(int argc,char *argv[])
{
    int     fd,i,nloop;
    pid_t   pid;
    struct shmstruct *ptr;
    if(argc != 4)
    {
        printf("usage: client1 <shmname> <semname> <#loops>.\n");
        exit(0);
    }
    nloop = atoi(argv[3]);
        //打开共享内存区
    if((fd = shm_open(argv[1],O_RDWR,FILE_MODE)) == -1)
    {
        perror("shm_open error");
        exit(0);
    }
        //将共享内存区映射到进程地址空间
    if((ptr = mmap(NULL,sizeof(struct shmstruct),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0)) == MAP_FAILED)
    {
        perror("mmap error");
        exit(-1);
    }
    close(fd);
        //打开信号量
    if((mutex = sem_open(argv[2],0)) == SEM_FAILED)
    {
        printf("sem_open error");
        exit(-1);
    }
    pid = getpid();
    for(i=0;i<nloop;i++)
    {
        sem_wait(mutex); //锁住信号量
        printf("pid %ld: %d\n",(long) pid,ptr->count++);
        sem_post(mutex); //释放信号量
    }
    exit(0);
}

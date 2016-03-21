#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
void dir_scan(char *path, char *file, char * fileToSearch);
int count = 0;

int main(int argc, char *argv[])
{
    struct stat s;
    if(argc != 3){
        printf("error argu!");
        exit(1);
    }
    if(lstat(argv[1], &s) < 0){
        printf("lstat error!");
        exit(2);
    }
    if(!S_ISDIR(s.st_mode)){
        printf("This is not a dir name!\n");
        exit(3);
    }
    dir_scan("", argv[1], argv[2]);
    exit(0);
}


void dir_scan(char * path, char * file, char * fileToSearch)
{
    struct stat s;
    DIR * dirPtr;
    struct dirent * dtPtr;
    char dirName[1000];
    memset(dirName, 0, 1000 * sizeof(char));
    strcpy(dirName, path);

    if(lstat(file, &s) < 0){
           printf("asdasdad");
           exit((4));
       }
    if(S_ISDIR(s.st_mode)){
       strcat(dirName, file);
       strcat(dirName, "/");
       if((dirPtr = opendir(file)) == NULL){
            printf("open dir error!\n");
            exit(5);
            printf("The count now is %d\n", count);
       }
       if(chdir(file) < 0){
            printf("chdir error!\n");
            exit(6);
       }
       while((dtPtr = readdir(dirPtr)) != NULL){
            if(dtPtr->d_name[0] == '.')
                continue;
            dir_scan(dirName, dtPtr->d_name, fileToSearch);
       }
       if(dirPtr != NULL)
            closedir(dirPtr);
       if(chdir("..") < 0){
            printf("chdir error!\n");
            exit(7);
       }
    }else{
          if(strstr(file, fileToSearch) != NULL && (!strstr(file, "."))){
                printf("%s%s\n", dirName, file);
          }
        count++;
    }
}

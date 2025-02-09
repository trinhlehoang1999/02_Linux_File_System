#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd;
    int numb_read, numb_write;
    int ch;
    char *filename = argv[1];
    char buf1[19] = "i am neo_Hoang1801";


    struct stat fileStat;

    printf("BT4\n");

    fd = open(argv[1], O_RDWR);

    numb_write = write(fd,buf1,strlen(buf1));

    stat(filename, &fileStat);

    char mtime_str[100];
    
    strftime(mtime_str, sizeof(mtime_str), "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));

    printf("name file: %s\n",filename);
    printf("Last modification time (st_mtime): %s\n", mtime_str);
    printf("size of file: %ld bytes\n", fileStat.st_size);

    if (S_ISREG(fileStat.st_mode))
    {
        printf("This is the file");
    }
    else if (S_ISDIR(fileStat.st_mode))
    {
        printf("This is the folder");
    }
    else
    {
        printf("Undefined file\n");
    }

    printf(" and ");
    printf("owner of permissions: ");
    if (fileStat.st_mode & S_IRUSR) printf("read ");
    if (fileStat.st_mode & S_IWUSR) printf("write ");
    if (fileStat.st_mode & S_IXUSR) printf("execute ");
    printf("\n");
    
    close(fd);

}
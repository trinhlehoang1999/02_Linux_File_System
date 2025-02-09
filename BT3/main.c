#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc <= 5)
    {
        int fd; //file descriptor
        int numb_read, numb_write;

        char* filename = argv[1];
        long num_bytes = strtol(argv[2],NULL,10);
        char* mode_rw = argv[3];
        char* data = argv[4];

        int flag;
        int ch;

        char* sign_w = "w";
        char* sign_r = "r";
        printf("BT3\n");

        if (strcmp(mode_rw,sign_r) == 0)
        {
            flag = 1;
            fd = open(argv[1], O_RDONLY);
        }
        else if (strcmp(mode_rw,sign_w) == 0)
        {
            flag = 0;
            fd = open(argv[1], O_RDWR | O_TRUNC);
        }

        if (fd == -1)
        {
            printf("could not using open() %s\n",filename);
        }
        
        numb_write = write(fd,data, num_bytes - 1);

        printf("write %d bytes to %s\n",numb_write,filename);
        
        FILE *file = fopen(filename, "r");
   
        while ((ch = fgetc(file)) != EOF && flag == 1)
        {
            putchar(ch);
        }

        fclose(file);
        close(fd);
    }
    else
    {
        printf("please using only 3 arguments for read file or 4 arguments for write");
    }

}

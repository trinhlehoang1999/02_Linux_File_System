BÀI THỰC HÀNH BUỔI 2
BT1. Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó. Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?
Dữ liệu file được ghi sẽ xuất hiện ở cuối file, bởi vì khi set cờ O_APPEND sẽ luôn luôn trỏ tới cuối file bất kể đã dùng function lseek(SEEK_SET).
Code:
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd; //file descriptor
    int numb_read, numb_write;
    char buf1[15] = "i am neo_Hoang";

    printf("BT1\n");

//  O_APPEND means that always put pointer space into the last text even when using SEEK_Set
    fd = open("hello.txt", O_APPEND | O_RDWR | O_TRUNC); // gan co Read Write file va xoa du lieu khi moi mo file
    printf("value fd = %d\n",fd);

    if (fd == -1)
    {
        printf("could not using open() hello.txt\n");
    }
    
    numb_write = write(fd,buf1,strlen(buf1));

    printf("write %d bytes to hello.txt\n",numb_write);

    lseek(fd, 3, SEEK_SET);
    write(fd, ",Hello",strlen(",Hello"));

    close(fd);
}


BT3. Viết một chương trình có só lượng command-line arguments là 3, có dạng như sau:
$ ./example_program filename num-bytes [r/w] "Hello"
Trong đó:
	1. example_grogram: Tên file thực thi
	2. filename: Tên file
	3. num-bytes: Số byte muốn read/write
	4. [r/w]: r -> Thực hiện đọc từ  filename và in ra màn hình
		    w -> Thực hiện ghi vào filename
	5. "Hello": Nội dung bất kì muốn read/write vào filename
Code:
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

BT4. Tạo file bất kì và ghi một đoạn dữ liệu vào file đó. Thực hiện ghi ra màn hình các thông tin: Loại file, tên file, thời gian chỉnh sửa file lần cuối, kích thước. - Sử dụng struct stat
Code:
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


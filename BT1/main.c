/* 
BT1. Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, 
sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó. 
Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?
==> Answer: Dữ liệu file được ghi sẽ xuất hiện ở cuối file, bởi vì khi set 
cờ O_APPEND sẽ luôn luôn trỏ tới cuối file bất kể đã dùng function lseek(SEEK_SET).
 */
 /* ------------------------------ */
// Run: ./BT1_execute 
 /* ---------------------------------- */

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
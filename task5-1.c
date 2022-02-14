#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    if ((fd = open("myfile", O_RDONLY)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    char buff[14];
    int read_res = read(fd, buff, 14);
    if (read_res != 14) {
        printf("Can\'t read all text\n");
        exit(-1);
    }
    printf("%s", buff);
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
    }

    return 0;
}

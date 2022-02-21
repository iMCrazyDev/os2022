#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd[2], ans = 0;
    char ch = 'i';

    if (pipe(fd) < 0) {
        printf("Can't open pipe\n");
        exit(-1);
    }

    if (fcntl(fd[1], F_SETFL, O_NONBLOCK) == -1) {
        printf("error setting nonblock pipe");
        exit(-1);
    }

    while (write(fd[1], &ch, 1) == 1 && ++ans);
    
    close(fd[0]);
    close(fd[1]);

    printf("buf size is %d bytes", ans);

  return 0;
}

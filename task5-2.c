#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2], result;

    size_t size;
    char  resstring[15];

    if (pipe(fd) < 0) {
        printf("Can't open pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can't fork child\n");
        exit(-1);
    } else if (result > 0) {
        /* Parent process */
        size = write(fd[1], "I'm your parent", 15);

        if (size != 15) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }
        int res;
        wait(&res);
        size = read(fd[0], resstring, 15);

        if (size < 0) {
            printf("Can't read string from pipe\n");
            exit(-1);
        }

        printf("From child: %s\n", resstring);

        if (close(fd[1]) < 0 || close(fd[0]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
        }

        printf("Parent exit\n");

    } else {

        /* Child process */
        size = read(fd[0], resstring, 15);
        if (size < 0) {
            printf("Can't read string from pipe\n");
            exit(-1);
        }


        printf("From parent: %s\n", resstring);

        size = write(fd[1], "I'm your child!", 15);

        if (size != 15) {
            printf("Can't write all string to pipe\n");
            exit(-1);
        }

    }

  return 0;
}

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main() {
    pid_t pid, ppid;

    pid_t frk = fork();

    if (frk == -1) {
        printf("error per forking :((( \n");
    } 

    pid = getpid(), ppid = getppid();

    if(frk == 0) {
        printf("pid: %d, ppid: %d child \n", pid, ppid);
    } else {
        printf("pid: %d, ppid: %d parent \n", pid, ppid);
    }

    return 0;
}

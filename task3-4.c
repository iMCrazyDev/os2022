#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int execlp(const char *file, const char *arg0, ...);

int main() {
    pid_t pid, ppid;

    pid_t frk = fork();

    if (frk == -1) {
        printf("error per forking :((( \n");
    } 

    pid = getpid(), ppid = getppid();

    if(frk == 0) {
        printf("pid: %d, ppid: %d child \n", pid, ppid);
        printf("callin' cat \n");
        execlp("/bin/cat", "/bin/cat", "task1-1.c", NULL);  
    } else {
        printf("pid: %d, ppid: %d parent \n", pid, ppid);
    }

    return 0;
}

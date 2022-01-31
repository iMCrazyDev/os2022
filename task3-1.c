#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main() {
    pid_t pid = getpid(), ppid = getppid();

    printf("pid: %d, ppid: %d \n", pid, ppid);
    /* 
    из опыта видно, что pid назначается последовательно, 
    когда дойдет до максимального значения, будет искать незанятые и сначала пойдет все.
    ppid одинаковый т.к. запуск из консоли то есть ppid = pid консоли
    */
    return 0;
}

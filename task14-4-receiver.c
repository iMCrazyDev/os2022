#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid = 0;
int count = 0;
int real_res = 0;
int res = 0;

void zero() {
    if (++count == 32) {
        printf("res: %d\n", res);
        exit(0);
    } else {
        while (pid == 0);
        printf("step: %d bit: 0\n", count);
        kill(pid, SIGUSR1);
    }
}

void one() {
    res = res ^ (1 << count);
    if (++count == 32) {
        printf("res: %d\n", res);
        exit(0);
    } else {
        while (pid == 0);
        printf("step: %d bit: 1\n", count);
        kill(pid, SIGUSR1);
    }
}


int main() {
    (void)signal(SIGUSR1, zero);
    (void)signal(SIGUSR2, one);

    printf("[RECEIVER] my pid: %d\n", getpid());
    printf("enter sender pid:");
    scanf("%d", &pid);
    while(1);

    return 0;
}

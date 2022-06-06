#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid = 0;
int count = 0;
int sync1 = 0;
int number;

void zero() {
    sync1 = 1;
    printf("got sync\n");
}

int main() {
    (void)signal(SIGUSR1, zero);

    printf("[SENDER] my pid: %d\n", getpid());
    printf("enter reciever pid:");
    scanf("%d", &pid);
    printf("enter number:");
    scanf("%d", &number);

    for (int i = 0; i < 32; i++) {
        sync1 = 0;
        if ((number & (1 << i)) == 0) {
            kill(pid, SIGUSR1);
        } else {
            kill(pid, SIGUSR2);
        }
        if (i == 31) {
            break;
        }
        while (sync1 == 0);
    }

    printf("ok");

    return 0;
}

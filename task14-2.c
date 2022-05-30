#include <signal.h>
#include <stdio.h>

void on_signal(int nsig) {
    if (nsig == 2) {
        printf("Code: %d, SIGINT received\n", nsig);
    } else {
        printf("Code: %d, SIGQUIT received\n", nsig);
    }
}

int main(void) {
    (void)signal(SIGINT, on_signal);
    (void)signal(SIGQUIT, on_signal);

    while(1);
    return 0;
}

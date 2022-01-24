#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    printf("user id: %i \n group id: %i", getuid(), getgid());
    return 0;
}
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    while (*envp) {
        printf("%s\n", *(envp++));
    }
    return 0;
}

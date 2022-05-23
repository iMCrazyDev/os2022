#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
    char res[30], res2[30];
    int aasdadas = open("a.txt", O_RDWR | O_CREAT);
    if (aasdadas == -1) {
        printf("error oppening file \n");
        exit(1);
    }
    symlink("a.txt", "0");
    sprintf(res, "0\0");
    int i = 1;
    while (1) {
        sprintf(res2, "%d\0", i);
        int p;
        if((p = open(res, O_RDONLY)) == -1) { 
            printf ("path res: %s, ans: %d\n", res, i + 1); 
            exit(0); 
        } 
        symlink(res, res2); 
        printf("%d\n", i);
        sprintf(res, "%d\0", i);
        i++;
    }
    printf("result: %d", i);
    return 0;
}
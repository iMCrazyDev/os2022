#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
struct stat st;

int main()
{
    char     *array;
    int     shmid;
    int     new = 1;
    char    pathname[] = "task7-1w.c";
    key_t   key;
    stat(pathname, &st);
    size_t size = st.st_size;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, size*sizeof(char), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
    }

    if ((array = (char*)shmat(shmid, NULL, 0)) == (char *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    char* arr2 = (char*)malloc(size);
    for (int i = 0; i < size; i++) {
        arr2[i] = array[i];
    }
    printf ("res %s", arr2);
    free(arr2);

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

  return 0;
}

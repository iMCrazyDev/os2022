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
    char     *array;    // Pointer to shared memory
    int     shmid;     // IPC descriptor for the shared memory
    int     new = 1;   // Initialization flag for the elements of the array
    char    pathname[] = "task7-1w.c"; // The file name used to generate the key.
                                    // A file with this name must exist in the current directory.
    key_t   key;       // IPC key
    //
    // Generate an IPC key from the file name 07-1a.c in the current directory
    // and the instance number of the shared memory 0.

    stat(pathname, &st);
    size_t size = st.st_size;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((shmid = shmget(key, size*sizeof(char), 0666|IPC_CREAT)) < 0) {
        if (errno != EEXIST) {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } 
    }

    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    //char* file_text = (char*)malloc(size);
    //fgets(char_text, size, file);

    if (new) {
        FILE* file = fopen(pathname, "r");
        for (int i = 0; i < size; i++) {
            array[i] = fgetc(file);
        }
    } 
    /*else {
        array[0] += 1;
        array[2] += 1;
    }

    printf (
        "Program 1 was spawn %d times,\n"
        "program 2 - %d times,\n"
        "total - %d times\n",
        array[0],
        array[1],
        array[2]
    );*/
    printf("Successfully writed");

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}

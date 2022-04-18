#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/sem.h>

/*
 * Как работает. В общей памяти array[0] это сколько осталось. Семафор отвечает за синхноризацию очереди
 * когда семафор равен нулю выполняется родитель, затем прибавляется 2 к семафору,
 * Сын сначала отнимает 1 от семафора, а потом еще раз 1, когда выполнился, в итоге станет 0 и семафор вернется в родителя
 * array[0] вычитает children, выводов будет n*2-1 например, при n=2 будет отец->сын-> вывод -> отец -> вывод -> сын -> вывод т.к.
 * в самый первый раз не выводим
 */

int main()
{
    int* array;
    int   semid;
    key_t   key;
    int n = 2;
    int     fd[2], result;

    size_t size;
    char    pathname[] = "task9-3.c";
    char  resstring[7];

    int     shmid, shmid2;
    struct sembuf mybuf, mybuf2, mybuf3;

    mybuf3.sem_num = 0;
    mybuf3.sem_op  = 2;
    mybuf3.sem_flg = 0;

    mybuf.sem_num = 0;
    mybuf.sem_op  = 0;
    mybuf.sem_flg = 0;

    mybuf2.sem_num = 0;
    mybuf2.sem_op  = -1;
    mybuf2.sem_flg = 0;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    if ((shmid2 = shmget(key, 1*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if ((shmid2 = shmget(key, 1*sizeof(int), 0)) < 0) {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

    if ((array = (int *)shmat(shmid2, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    array[0] = n;

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {

        /* Parent process */
        int flag = 0;
        while (array[0] != 0) {
            while (semop(semid, &mybuf, 1) < 0);
            if (array[0] == 0) {
                break;
            }

            if (flag == 1) {
                read(fd[0], resstring, 7);
                printf("from child:%s\n", resstring);
            }

            write(fd[1], "parent", 7);

            semop(semid, &mybuf3, 1);
            flag = 1;
        }

        printf("Parent exit\n");

    } else {

        /* Child process */

        while (array[0] != 0) {
            while (semop(semid, &mybuf2, 1) < 0);
            read(fd[0], resstring, 7);
            printf("from parent:%s\n", resstring);
            --array[0];
            if (array[0] != 0) {
                write(fd[1], "childr", 7);
            }
            semop(semid, &mybuf2, 1);
        }


        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n"); exit(-1);
        }

        if (close(fd[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n"); exit(-1);
        }

        printf("child exit");
    }

    return 0;
}

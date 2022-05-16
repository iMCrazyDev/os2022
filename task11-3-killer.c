#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int msqid;
    char pathname[] = "task11-3-server.c";
    key_t key;
    int len, maxlen;

   struct request {
        long mtype;
        struct {
            pid_t pid;
	        double number;
        } request;
    } request_data;

    struct response {
        long mtype;
        struct {
	        double numbernumber;
        } response;
    } response_data;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("can't get msqid\n");
        exit(-1);
    }

    request_data.mtype = 2;
    request_data.request.pid = getpid();
    request_data.request.number = 0;
    len = sizeof(request_data.request);
    if (msgsnd(msqid, (struct msgbuf *) &request_data, len, 0) < 0) {
        printf("error per sending message\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    return 0;
}

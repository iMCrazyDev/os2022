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

    double input;
    printf("enter number: \n")
    scanf("%lf", &input);

    if ((key = ftok(pathname, 0)) < 0) {
        printf("can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("can't get msqid\n");
        exit(-1);
    }

    request_data.mtype = 1;
    request_data.request.pid = getpid();
    request_data.request.number = input;
    len = sizeof(request_data.request);
    if (msgsnd(msqid, (struct msgbuf *) &request_data, len, 0) < 0) {
        printf("error per sending message\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    maxlen = sizeof(response_data.response);
    if (len = msgrcv(msqid, (struct msgbuf *) &response_data, maxlen, getpid(), 0) < 0) {
        printf("error per recieving message\n");
        exit(-1);
    }

    printf("x = %lf, x^2 = %lf, mypid = %ld\n", request_data.request.number, response_data.response.numbernumber, request_data.request.pid);

    return 0;
}

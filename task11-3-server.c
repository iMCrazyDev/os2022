#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
    int msqid;
    char pathname[] = "task11-3-server.c";
    key_t key;
    int len;

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
    len = sizeof(request_data.request);
    while (1) {
        if (len = msgrcv(msqid, (struct msgbuf *) &request_data, len, 1, 0) < 0) {
            printf("error per recieving message\n");
            exit(-1);
        }
        printf("%d",request_data.mtype);
        if (request_data.mtype == 2) {
            printf("exiting...");
            exit(0);
        }
        response_data.mtype = request_data.request.pid;
        response_data.response.numbernumber = request_data.request.number * request_data.request.number;
        len = sizeof(response_data.response.numbernumber);
 
        if (msgsnd(msqid, (struct msgbuf *) &response_data, len, 0) < 0) {
            printf("error per sending message\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
            exit(-1);
        }
    }

    return 0;
}

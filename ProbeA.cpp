//  Saul Hernandez
//  Dustin
//  ProbeA.cpp, ProbeB.cpp, ProbeC.cpp, DataHub.cpp
//  This code defines the ProbeA component of this
//  assignment
//  must be
//  msgrev(,,,,0); IPC_NOWAIT = polling

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main() {

    int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

    struct buf {
		long mtype; // required
		char content[50]; // mesg content
	};

    buf msg;
    int size = sizeof(msg) - sizeof(long);

    do {
        msg.mtype = rand();
        strcpy(msg.content, "Message!");
        msgsnd(qid, (struct msgbuf *)&msg, size, 0);

        msgrcv(qid, (struct msgbuf *)&msg, size, 0);
        
    } while (msg.mtype > 100);

    exit(0);
}

//  Saul Hernandez
//  Dustin
//  ProbeA.cpp, ProbeB.cpp, ProbeC.cpp, DataHub.cpp
//  This code defines the DataHub component of this
//  assignment

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main() {
    int alpha = 997, beta = 257, rho = 251;
    int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

    struct buf {
		long mtype; // required
		char content[50]; // mesg content
	};

    buf msg;
    int size = sizeof(msg) - sizeof(long);

    bool running = true;
    buf reply;
    int msg_count = 0;

    while (running) {

        //msgrcv recieves all message types
        if (msgrcv(qid, (struct msgbuf *)&msg, size, 0, 0) > -1) {

            // message is from ProbeA
            if (msg.mtype % alpha == 0) {

                cout << "DataHub recieved data from Probe A PID: " << msg.content << endl;
                cout << "MsgType is: " << msg.mtype << endl; 
                reply.mtype = msg.mtype;
                strcpy(reply.content, "DataHub received message");
                msgsnd(qid, (struct msgbuf *)&reply, size, 0);

            } else if (msg.mtype % beta == 0) {

                //TODO: recieve data from probe B

            } else if (msg.mtype % rho == 0) {

                //TODO: recieve data from probe C

            } else {break;}
        } else {
            running = false;
        }
    }

    msgctl(qid, IPC_RMID, NULL);
    ::exit(0);
}

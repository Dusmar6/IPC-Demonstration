

//  Saul Hernandez
//  Dustin
//  ProbeA.cpp, ProbeB.cpp, ProbeC.cpp, DataHub.cpp
//  This code defines the ProbeC.cpp component of this
//  assignment

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
#include <signal.h>
#include <unistd.h>


using namespace std;

// the function sends one message to the queue, when the user enters the kill command (SIGUSR1) & terminates the process
// qid - id of attached queue (retval from msgget)
// exitmsg - pointer to message object contains the exit message to its recipient
// size - size of the message object
// mtype - mtype associated with this message object
void kill_patch(int qid, struct msgbuf *exitmsg, int size, long mtype);

int main() {
    //int alpha = 997, beta = 257, rho = 251;
    int magic_seed = 251; //rho
    int qid = msgget(ftok(".",'u'), 0); 

    struct buf {
		long mtype; // required
		char content[50]; // mesg content
	};

    buf msg;
    int size = sizeof(msg) - sizeof(long);
    int pid = getpid();
    int return_mtype;
    bool run = true;

    while (run) {
        msg.mtype = return_mtype = rand();
        
        if (msg.mtype % magic_seed == 0) {
            strcpy(msg.content, to_string(pid).c_str()); // add pid to msg.content in form of C-string
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
        }
    }

    exit(0);
}

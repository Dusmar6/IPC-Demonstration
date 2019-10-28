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
#include <string>

using namespace std;

int main() {
    //int alpha = 997, beta = 257, rho = 251;
    int magic_seed = 997; //alpha
    int qid = msgget(ftok(".",'u'), 0); 

    struct buf {
		long mtype; // required
		char content[50]; // mesg content
	};

    buf msg;
    int size = sizeof(msg) - sizeof(long);
    int pid = getpid();
    int return_mtype = 20;
    int rand_num;
    
    do {
        rand_num = rand();
        
        if (rand_num % magic_seed == 0) {
            msg.mtype = magic_seed;
            strncpy(msg.content, to_string(pid).c_str(), size); // add pid to msg.content in 
                                                                // form of C-string
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            cout << "Sending: Probe A: " << msg.content << ": " << msg.mtype << endl;

            msgrcv(qid, (struct msgbuf *)&msg, size, return_mtype, 0);

            cout << "Recieving from Data Hub: " << msg.content << ": " << msg.mtype << endl;

        }

    } while (rand_num > 100);
    cout << "Probe A terminating\n";
    exit(0);
}

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
		char greeting[50]; // mesg content
	};

    buf msg;
    int size = sizeof(msg) - sizeof(long);

    bool running = true;
    int msg_count = 0;

    while (running) {

    }

    
}

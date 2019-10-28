//  Saul Hernandez
//  Dustin
//  ProbeA.cpp, ProbeB.cpp, ProbeC.cpp, DataHub.cpp
//  This code defines the ProbeB.cpp component of this
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

using namespace std;

int main() {

    int magic_seed = 7001; // beta
    int qid = msgget(ftok(".",'u'), 0);
    
    struct buf {
        long mtype;
        char content[50];
    };

    buf msg;
    int size = sizeof(msg) - sizeof(long);
    int pid = getpid();
    int rand_num;

    while (true) {
        rand_num = rand();
        if (rand_num % magic_seed == 0) {
            msg.mtype = magic_seed;
            strncpy(msg.content, to_string(pid).c_str(), size);
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            cout << "Probe B: " << msg.content << ": " << msg.mtype << endl;
        }
    }
}

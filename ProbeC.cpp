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
#include "kill_patch.h"

using namespace std;

int main() {

    struct buf {
        long mtype;
        char content[50];
    };
    buf msg, exit_msg;

    int size = sizeof(msg) - sizeof(long);
    int pid = getpid();
    int rand_num;

    strncpy(exit_msg.content, "Final Message", size);
    exit_msg.mtype = 10;

    int magic_seed = 21001;
    int qid = msgget(ftok(".",'u'), 0);
    kill_patch(qid, (struct msgbuf *)&exit_msg, size, 10);

    while (true) {
        rand_num = rand();
        if (rand_num % magic_seed == 0) {
            msg.mtype = magic_seed;
            strncpy(msg.content, to_string(pid).c_str(), size);
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            cout << "Probe C:" << msg.content << ": " << msg.mtype << endl;            
        }
    }
}
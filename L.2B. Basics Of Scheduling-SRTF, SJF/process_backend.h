#ifndef PROCESS_BACKEND
    int numOfProcesses;
    struct Process
    {
        int id;
        int arrival_time;
        int burst_time;
        int completed;
        int last_time;
    };

int next(int curr_process, int choose, struct Process processes[], int currTime);
void run(struct Process processes[], int quanta, int numOfProcesses, int choose);

#include "process_backend.c"

#endif
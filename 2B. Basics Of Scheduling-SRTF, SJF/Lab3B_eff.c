// Group Members:
// 1) Vikas Dangi-B20238
// 2) Pushkar Patel-B20121
// 3) Saksham Kumar-B20228
#include <stdio.h>
#include "process_backend.h"

int main()
{
    printf("Please input the number of processes: \n");
    scanf("%d", &numOfProcesses);
    struct Process processes[numOfProcesses];
    printf("Please input the Processes as \nprocess_id, arrival time, burst time\n");
    for (int i = 0; i < numOfProcesses; i++)
    {
        // int curr_id, curr_arrival_time, curr_burst_time, is_completed;
        scanf("%d", &processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        scanf("%d", &processes[i].burst_time);
        processes[i].completed=0;
        processes[i].last_time=processes[i].arrival_time;
    }

    int choose;
    printf("Choose:\n1 for FCFS \n2 for Round Robin\n3 for SJF\n4 for SRTF... \n");
    scanf("%d", &choose);
    if(choose==1){
        int quanta=2e9;
        run(processes, quanta, numOfProcesses, choose);
    }else if(choose==2){
        int quanta;
        printf("Please input the time-slice for Round Robin: \n");
        scanf("%d", &quanta);
        run(processes, quanta, numOfProcesses, choose);
    }else if(choose==3){
        int quanta=2e9;
        run(processes, quanta, numOfProcesses, choose);
    }else if(choose==4){
        int quanta=1;
        run(processes, quanta, numOfProcesses, choose);
    }
    return 0;
}
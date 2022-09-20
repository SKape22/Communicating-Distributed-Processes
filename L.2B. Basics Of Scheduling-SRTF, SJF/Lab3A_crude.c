// Group Members:
// 1) Vikas Dangi-B20238
// 2) Pushkar Patel-B20121
// 3) Saksham Kumar-B20228
#include <stdio.h>
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int completed;
    int last_time;
};

void run(struct Process processes[], int quanta, int numOfProcesses)
{
    int currTime=processes[0].arrival_time;
    int dones=0;
    float total_time = 0;
    float wait_time = 0;

    while (dones<numOfProcesses)
    {
        for (int i = 0; i < numOfProcesses; i++)
        {
            int remaining=processes[i].burst_time-processes[i].completed;
            if(processes[i].arrival_time<=currTime && remaining>0){
                printf("Process %d runs from %d - ", processes[i].id, currTime);
                if(remaining-quanta<=0){
                    dones++;
                    wait_time+=currTime-processes[i].last_time;
                    currTime+=remaining;
                    total_time+=currTime;
                    processes[i].last_time=currTime;
                    processes[i].completed+=remaining;
                }else{
                    wait_time+=currTime-processes[i].last_time;
                    processes[i].completed+=quanta;
                    currTime+=quanta;
                    processes[i].last_time=currTime;
                }
                printf("%d\n", currTime);
            }
        }
    }
    total_time /= numOfProcesses;
    wait_time /= numOfProcesses;
    printf("Average Completion Time: %f\n", total_time);
    printf("Average Wait Time: %f\n", wait_time);
}

int main()
{
    printf("Please input the number of processes: \n");
    int numOfProcesses;
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
    printf("Choose:\n1 for FCFS \n2 for Round Robin\n3 for SJF\nchoose 4 for SRTF... \n");
    scanf("%d", &choose);
    int quanta;
    if(choose==1){
        quanta=2e9;
        run(processes, quanta, numOfProcesses);
    }else if(choose==2){
        printf("Please input the time-slice for Round Robin: \n");
        scanf("%d", &quanta);
        run(processes, quanta, numOfProcesses);
    }else if(choose==3){
        int curr_process=0;
        int currTime=processes[0].arrival_time;
        int dones=0;
        float total_time = 0;
        float wait_time = 0;
        while(dones<numOfProcesses){
            dones++;
            printf("Process %d runs from %d - ", processes[curr_process].id, currTime);
            int remaining=processes[curr_process].burst_time-processes[curr_process].completed;
            processes[curr_process].completed+=processes[curr_process].burst_time;
            wait_time+=currTime-processes[curr_process].last_time;
            currTime+=processes[curr_process].burst_time;
            total_time+=currTime;
            processes[curr_process].last_time=currTime;
            processes[curr_process].completed+=remaining;
            printf("%d\n", currTime);
            if(dones==numOfProcesses) break;
            int val=2e9;
            for(int i=0;i<numOfProcesses;i++){
                if(processes[i].arrival_time<=currTime && processes[i].completed<processes[i].burst_time){
                    if(val>processes[i].burst_time){
                        val=processes[i].burst_time;
                        curr_process=i;
                    }
                }
            }
        }
        total_time /= numOfProcesses;
        wait_time /= numOfProcesses;
        printf("Average Completion Time: %f\n", total_time);
        printf("Average Wait Time: %f\n", wait_time);
    }
    else if(choose==4){
        int curr_process=0;
        int currTime=processes[0].arrival_time;
        int dones=0;
        float total_time = 0;
        float wait_time = 0;
        int quanta=1;
        while (dones<numOfProcesses)
        {
            int remaining=processes[curr_process].burst_time-processes[curr_process].completed;
            if(processes[curr_process].arrival_time<=currTime && remaining>0){
                printf("Process %d runs from %d - ", processes[curr_process].id, currTime);
                if(remaining-quanta<=0){
                    dones++;
                    wait_time+=currTime-processes[curr_process].last_time;
                    currTime+=remaining;
                    total_time+=currTime;
                    processes[curr_process].last_time=currTime;
                    processes[curr_process].completed+=remaining;
                }else{
                    wait_time+=currTime-processes[curr_process].last_time;
                    processes[curr_process].completed+=quanta;
                    currTime+=quanta;
                    processes[curr_process].last_time=currTime;
                }
                printf("%d\n", currTime);
            }
            int val=2e9;
            for(int i=0;i<numOfProcesses;i++){
                if(processes[i].arrival_time<=currTime && processes[i].completed<processes[i].burst_time){
                    int rem=processes[i].burst_time-processes[i].completed;
                    if(val>rem){
                        val=processes[i].burst_time;
                        curr_process=i;
                    }
                }
            }
        }
        total_time /= numOfProcesses;
        wait_time /= numOfProcesses;
        printf("Average Completion Time: %f\n", total_time);
        printf("Average Wait Time: %f\n", wait_time);
    }
    return 0;
}
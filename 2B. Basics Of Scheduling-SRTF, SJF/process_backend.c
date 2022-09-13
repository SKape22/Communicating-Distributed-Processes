int next(int curr_process, int choose, struct Process processes[], int currTime)
{
    int new_process;
    if(choose==1 || choose==2){
        new_process=(curr_process+1)%numOfProcesses;
    }else if(choose==3 || choose==4){
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
        new_process=curr_process;
    }
    return new_process;
}

void run(struct Process processes[], int quanta, int numOfProcesses, int choose)
{
    int curr_process=0;
    int currTime=processes[0].arrival_time;
    int dones=0;
    float total_time = 0;
    float wait_time = 0;
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
        curr_process=next(curr_process, choose, processes, currTime);
    }
    total_time /= numOfProcesses;
    wait_time /= numOfProcesses;

    printf("Average Completion Time: %f\n", total_time);
    printf("Average Wait Time: %f\n", wait_time);
}
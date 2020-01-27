#include<stdio.h>

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main(){
	int noOfProcesses, i, j, cpuIdleTime = 0, time;

	printf("\nEnter the number of processes: ");
	scanf("%d", &noOfProcesses);

	int processID[noOfProcesses];
	int arrivalTime[noOfProcesses];
	int burstTime[noOfProcesses];
	int turnAroundTime[noOfProcesses];
	int waitingTime[noOfProcesses];

	for(i = 0; i < noOfProcesses; i++)
		processID[i] = i;

	for(i = 0; i < noOfProcesses; i++){
		printf("\nFor Process P%d,\nEnter the arrival time: ", i + 1);
		scanf("%d", &arrivalTime[i]);
		printf("Enter the burst time: ");
		scanf("%d", &burstTime[i]);
	}
	for(i = 0; i < noOfProcesses - 1; i++)
		for(j = 0; j < noOfProcesses - i - 1; j++)
			if(arrivalTime[j] > arrivalTime[j + 1]){
				swap(&processID[j], &processID[j + 1]);
				swap(&arrivalTime[j], &arrivalTime[j + 1]);
				swap(&burstTime[j], &burstTime[j + 1]);
			}

	time = 0;

	printf("\n");

	for(i = 0; i < noOfProcesses; i++){
		if(time < arrivalTime[i]){
			cpuIdleTime += arrivalTime[i] - time;
			printf("CPU was idle from t = %d to t = %d.\n", time, arrivalTime[i]);
			time = arrivalTime[i];
		}
		time += burstTime[i];
		turnAroundTime[i] = time - arrivalTime[i];
		waitingTime[i] = turnAroundTime[i] - burstTime[i];
	}

	printf("\nTotal CPU idle time: %d\n\n", cpuIdleTime);

	for(i = 0; i < noOfProcesses; i++)
		for(j = 0; j < noOfProcesses; j++){
			if(processID[j] == i){
				printf("Turn-around time for process P%d: %d\n", i + 1, turnAroundTime[j]);
				printf("Waiting time for process P%d: %d\n\n", i + 1, waitingTime[j]);
			}
		}
	
	printf("Number of context switches: %d\n\n", noOfProcesses - 1);
}

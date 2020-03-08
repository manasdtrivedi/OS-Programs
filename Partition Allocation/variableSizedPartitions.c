#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int noOfProcesses, size;

void firstFit(int processSize[], int ram[], int processAllocationStatus[])
{
	int pno, i, j;
	printf("Enter the process number of process to be added: ");
	scanf("%d", &pno);
	if(pno < 1 || pno > noOfProcesses)
	{
		printf("Process %d does not exist.\n", pno);
		return;
	}
	pno = pno - 1; // We use 0 to n - 1 process numbers. User uses 1 to n.
	if(processAllocationStatus[pno] == 1)
	{
		printf("Process %d is already allocated.\n", pno + 1);
		return;
	}
	int startingIndexOfEmptyBlock = -1;
	for(i = 0; i < size; i++)
	{
		if(ram[i] == -1)
		{
			startingIndexOfEmptyBlock = i;
			while(i < size && ram[i] == -1)
			{
				i++;
			}
			if(processSize[pno] <= i - startingIndexOfEmptyBlock)
			{
				for(j = startingIndexOfEmptyBlock; j < startingIndexOfEmptyBlock + processSize[pno]; j++)
				{
					ram[j] = pno;
				}
				processAllocationStatus[pno] = 1;
				printf("Process %d was allocated memory from index %d to index %d in the memory.\n", pno + 1, startingIndexOfEmptyBlock, j - 1);
				return;
			}
		}
	}
	if(processAllocationStatus[pno] == 0)
	{
		printf("Process %d cannot be allocated any memory.\n", pno + 1);
		return;
	}
}

void bestFit(int processSize[], int ram[], int processAllocationStatus[])
{
	int pno, i, j;
	printf("Enter the process number of the process to be added: ");
	scanf("%d", &pno);
	if(pno < 1 || pno > noOfProcesses)
	{
		printf("Process %d does not exist.\n", pno);
		return;
	}
	pno = pno - 1; // We use 0 to n - 1 process numbers. User uses 1 to n.
	if(processAllocationStatus[pno] == 1)
	{
		printf("Process %d is already allocated.\n", pno + 1);
		return;
	}
	int startingIndexOfEmptyBlock = -1;
	int startingIndexOfSelectedBlock = -1, sizeOfJustFittingBlock = INT_MAX;
	for(i = 0; i < size; i++)
	{
		if(ram[i] == -1)
		{
			startingIndexOfEmptyBlock = i;
			while(i < size && ram[i] == -1)
			{
				i++;
			}
			if(processSize[pno] <= i - startingIndexOfEmptyBlock && sizeOfJustFittingBlock > i - startingIndexOfEmptyBlock)
			{
				sizeOfJustFittingBlock = i - startingIndexOfEmptyBlock;
				startingIndexOfSelectedBlock = startingIndexOfEmptyBlock;
				printf("SELECTED BLOCK BEGINNING FROM INDEX %d.\n", startingIndexOfSelectedBlock);
			}
		}
	}
	if(startingIndexOfSelectedBlock == -1)
	{
		printf("Process %d cannot be allocated any memory.\n", pno + 1);
		return;
	}
	else
	{
		for(j = startingIndexOfSelectedBlock; j < startingIndexOfSelectedBlock + processSize[pno]; j++)
		{
			ram[j] = pno;
		}
		processAllocationStatus[pno] = 1;
		printf("Process %d was allocated memory from index %d to index %d in the memory.\n", pno + 1, startingIndexOfSelectedBlock, j - 1);
	}
}

void worstFit(int processSize[], int ram[], int processAllocationStatus[])
{
	int pno, i, j;
	printf("Enter the process number of the process to be added: ");
	scanf("%d", &pno);
	if(pno < 1 || pno > noOfProcesses)
	{
		printf("Process %d does not exist.\n", pno);
		return;
	}
	pno = pno - 1; // We use 0 to n - 1 process numbers. User uses 1 to n.
	if(processAllocationStatus[pno] == 1)
	{
		printf("Process %d is already allocated.\n", pno + 1);
		return;
	}
	int startingIndexOfEmptyBlock = -1;
	int startingIndexOfSelectedBlock = -1, sizeOfLargestBlock = 0;
	for(i = 0; i < size; i++)
	{
		if(ram[i] == -1)
		{
			startingIndexOfEmptyBlock = i;
			while(i < size && ram[i] == -1)
			{
				i++;
			}
			if(processSize[pno] <= i - startingIndexOfEmptyBlock && sizeOfLargestBlock < i - startingIndexOfEmptyBlock)
			{
				sizeOfLargestBlock = i - startingIndexOfEmptyBlock;
				startingIndexOfSelectedBlock = startingIndexOfEmptyBlock;
			}
		}
	}
	if(startingIndexOfSelectedBlock == -1)
	{
		printf("Process %d cannot be allocated any memory.\n", pno + 1);
		return;
	}
	else
	{
		for(j = startingIndexOfSelectedBlock; j < startingIndexOfSelectedBlock + processSize[pno]; j++)
		{
			ram[j] = pno;
		}
		processAllocationStatus[pno] = 1;
		printf("Process %d was allocated memory from index %d to index %d in the memory.\n", pno + 1, startingIndexOfSelectedBlock, j - 1);
	}
}

void delete(int processSize[], int ram[], int processAllocationStatus[])
{
	int pno, i;
	printf("Enter the process number of the process to be deleted: ");
	scanf("%d", &pno);
	if(pno < 1 || pno > noOfProcesses)
	{
		printf("Process %d does not exist.\n", pno);
		return;
	}
	pno = pno - 1;
	if(processAllocationStatus[pno] == 0)
	{
		printf("Process %d is not currently allocated any memory.\n", pno + 1);
		return;
	}
	else
	{
		for(i = 0; i < size; i++)
		{
			if(ram[i] == pno)
			{
				ram[i] = -1;
			}
		}
		processAllocationStatus[pno] = 0;
		printf("Process %d successfully deleted.\n", pno + 1);
	}
}

void printRAM(int ram[])
{
	int i;
	printf("Current memory status: ");
	for(i = 0; i < size - 1; i++)
	{
		printf("%d, ", ram[i] + 1);
	}
	printf("%d\n", ram[i] + 1);
}

int main()
{
	int mode, i;
	printf("\nEnter the number of processes: ");
	scanf("%d", &noOfProcesses);
	int processSize[noOfProcesses];
	int processAllocationStatus[noOfProcesses];
	printf("\n");
	for(i = 0; i < noOfProcesses; i++)
	{
		printf("Enter the size of process %d: ", i + 1);
		scanf("%d", &processSize[i]);
		processAllocationStatus[i] = 0;
	}
	printf("\n");
	printf("Enter the size of memory: ");
	scanf("%d", &size);
	int ram[size];
	for(i = 0; i < size; i++)
	{
		ram[i] = -1;
	}
	while(1)
	{
		printf("\nEnter 1 to add a process by first fit, 2 by best fit, 3 by worst fit, 4 to delete a process, 5 to display current memory status, 0 to exit: ");
		scanf("%d", &mode);
		switch(mode)
		{
			case 1: firstFit(processSize, ram, processAllocationStatus);
					break;
			case 2: bestFit(processSize, ram, processAllocationStatus);
					break;
			case 3: worstFit(processSize, ram, processAllocationStatus);
					break;
			case 4: delete(processSize, ram, processAllocationStatus);
					break;
			case 5: printRAM(ram);
					break;
			case 0:
			default: exit(0);
					break;
		}
	}
}

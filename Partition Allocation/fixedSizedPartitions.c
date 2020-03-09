#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int noOfBlocks;
int noOfProcesses;

void printProcessBlockMatrix(int processSize[], int blockNoAllocToProcess[], int remainingBlockSize[])
{
	int i;
	for(i = 0; i < noOfProcesses; i++)
	{
		if(blockNoAllocToProcess[i] != -1)
		{
			printf("Process %d was allocated block %d with internal fragmentation %d.\n", i + 1, blockNoAllocToProcess[i] + 1, remainingBlockSize[blockNoAllocToProcess[i]]);
		}
		else
		{
			printf("Process %d was not allocated any block.\n", i + 1);
		}
	}
}

void firstFit(int blockSize[], int processSize[])
{
	int i, j;
	int remainingBlockSize[noOfBlocks];
	int blockNoAllocToProcess[noOfProcesses];
	int blockIsUsed[noOfBlocks];

	for(i = 0; i < noOfProcesses; i++)
	{
		blockNoAllocToProcess[i] = -1;
	}
	for(i = 0; i < noOfBlocks; i++)
	{
		remainingBlockSize[i] = blockSize[i];
		blockIsUsed[i] = 0;
	}
	for(i = 0; i < noOfProcesses; i++)
	{
		for(j = 0; j < noOfBlocks; j++)
		{
			if(processSize[i] <= blockSize[j] && blockIsUsed[j] == 0)
			{
				remainingBlockSize[j] = blockSize[j] - processSize[i];
				blockIsUsed[j] = 1;
				blockNoAllocToProcess[i] = j;
				break;
			}
		}
	}
	printProcessBlockMatrix(processSize, blockNoAllocToProcess, remainingBlockSize);
}

void bestFit(int blockSize[], int processSize[])
{
	int i, j;
	int remainingBlockSize[noOfBlocks];
	int blockNoAllocToProcess[noOfProcesses];
	int blockIsUsed[noOfBlocks];

	for(i = 0; i < noOfProcesses; i++)
	{
		blockNoAllocToProcess[i] = -1;
	}
	for(i = 0; i < noOfBlocks; i++)
	{
		remainingBlockSize[i] = blockSize[i];
		blockIsUsed[i] = 0;
	}
	for(i = 0; i < noOfProcesses; i++)
	{
		int selectedBlock = -1;
		int sizeOfSmallestBlockToAccommodateProcess  = INT_MAX;
		for(j = 0; j < noOfBlocks; j++)
		{
			if(processSize[i] <= blockSize[j] && blockIsUsed[j] == 0 && blockSize[j] < sizeOfSmallestBlockToAccommodateProcess)
			{
				sizeOfSmallestBlockToAccommodateProcess = blockSize[j];
				selectedBlock = j;
			}
		}
		if(selectedBlock != -1)
		{
			remainingBlockSize[selectedBlock] = blockSize[selectedBlock] - processSize[i];
			blockIsUsed[selectedBlock] = 1;
			blockNoAllocToProcess[i] = selectedBlock;
		}
	}
	printProcessBlockMatrix(processSize, blockNoAllocToProcess, remainingBlockSize);
}

void worstFit(int blockSize[], int processSize[])
{
	int i, j;
	int remainingBlockSize[noOfBlocks];
	int blockNoAllocToProcess[noOfProcesses];
	int blockIsUsed[noOfBlocks];

	for(i = 0; i < noOfProcesses; i++)
	{
		blockNoAllocToProcess[i] = -1;
	}
	for(i = 0; i < noOfBlocks; i++)
	{
		remainingBlockSize[i] = blockSize[i];
		blockIsUsed[i] = 0;
	}
	for(i = 0; i < noOfProcesses; i++)
	{
		int selectedBlock = -1;
		int sizeOfLargestBlock = 0;
		for(j = 0; j < noOfBlocks; j++)
		{
			if(processSize[i] <= blockSize[j] && blockIsUsed[j] == 0 && blockSize[j] > sizeOfLargestBlock)
			{
				sizeOfLargestBlock = blockSize[j];
				selectedBlock = j;
			}
		}
		if(selectedBlock != -1)
		{
			remainingBlockSize[selectedBlock] = blockSize[selectedBlock] - processSize[i];
			blockIsUsed[selectedBlock] = 1;
			blockNoAllocToProcess[i] = selectedBlock;
		}
	}
	printProcessBlockMatrix(processSize, blockNoAllocToProcess, remainingBlockSize);
}

int main()
{
	int i;
	printf("\nEnter the number of blocks of memory: ");
	scanf("%d", &noOfBlocks);
	int blockSize[noOfBlocks];
	for(i = 0; i < noOfBlocks; i++)
	{
		printf("Enter the size of block %d: ", i + 1);
		scanf("%d", &blockSize[i]);
	}
	printf("\nEnter the number of processes: ");
	scanf("%d", &noOfProcesses);
	int processSize[noOfProcesses];
	for(i = 0; i < noOfProcesses; i++)
	{
		printf("Enter the size of process %d: ", i + 1);
		scanf("%d", &processSize[i]);
	}
	int mode = -1;
	while(1)
	{
		printf("\nEnter 1 for first fit, 2 for best fit, 3 for worst fit, 0 to exit: ");
		scanf("%d", &mode);
		printf("\n");
		switch(mode)
		{
			case 1: firstFit(blockSize, processSize);
					break;
			case 2: bestFit(blockSize, processSize);
					break;
			case 3: worstFit(blockSize, processSize);
					break;
			case 0 :
			default: exit(0);
					break;
		}
	}
	return 0; 
}

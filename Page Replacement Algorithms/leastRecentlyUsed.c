#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

void printFrames(int frames[], int noOfFrames)
{
	int i;
	for(i = 0; i < noOfFrames; i++)
	{
		printf("%d ", frames[i]);
	}
	printf("\n");
}

int main()
{
	int noOfFrames, length, i, j, pageHits = 0, pageFaults = 0, time = 0;
	char pageCharString[100];
	printf("Enter the string of pages: ");
	scanf("%s", pageCharString);
	length = strlen(pageCharString);
	int pageString[length];
	for(i = 0; i < length; i++)
	{
		pageString[i] = pageCharString[i] - '0';
	}
	printf("Enter the number of page frames: ");
	scanf("%d", &noOfFrames);
	int frames[noOfFrames];
	int timeStampForFrame[noOfFrames];
	for(i = 0; i < noOfFrames; i++)
	{
		frames[i] = -1;
		timeStampForFrame[i] = -1;
	}
	for(i = 0; i < length; i++)
	{
		int pageHitRegistered;
		pageHitRegistered = 0;
		for(j = 0; j < noOfFrames; j++)
		{
			if(pageString[i] == frames[j]) // Page Hit
			{
				pageHits++;
				pageHitRegistered = 1;
				timeStampForFrame[j] = time;
				time++;
				printf("Page hit registered. Current frames: ");
				printFrames(frames, noOfFrames);
				break;
			}
		}
		if(pageHitRegistered == 0) // Page Fault
		{
			pageFaults++;
			int emptyFrameFound = 0;
			emptyFrameFound = 0;
			for(j = 0; j < noOfFrames; j++) // Find an empty page to use
			{
				if(frames[j] == -1)
				{
					emptyFrameFound = 1;
					frames[j] = pageString[i];
					timeStampForFrame[j] = time;
					time++;
					printf("Page fault registered. Empty page found. Current frames: ");
					printFrames(frames, noOfFrames);
					break;
				}
			}
			if(emptyFrameFound == 0) // Find least recently used page, by referring timestamps.
			{
				int leastTime = INT_MAX, frameSelectedToReplace = -1;
				for(j = 0; j < noOfFrames; j++)
				{
					if(timeStampForFrame[j] < leastTime)
					{
						leastTime = timeStampForFrame[j];
						frameSelectedToReplace = j;
					}
				}
				frames[frameSelectedToReplace] = pageString[i];
				timeStampForFrame[frameSelectedToReplace] = time;
				time++;
				printf("Page fault registered. Page replaced. Current frames: ");
				printFrames(frames, noOfFrames);
			}
		}
	}
	printf("No. of page hits = %d\nNo. of page faults = %d\n", pageHits, pageFaults);
}
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
				printf("Page hit registered. Current frames: ");  // Note that time wasn't updated. Time is updated for LRU.
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
					timeStampForFrame[j] = time; // This is the time for first in of this page. It won't be updated on page hit.
					time++;
					printf("Page fault registered. Empty page found. Current frames: "); 
					printFrames(frames, noOfFrames);
					break;
				}
			}
			if(emptyFrameFound == 0)
			{
				int timeForNextPageHit[noOfFrames];
				int noOfFramesWhichDontAppear = 0; // Don't appear in the rest of the string
				for(j = 0; j < noOfFrames; j++)
				{
					timeForNextPageHit[j] = -1;
					int k;
					for(k = i + 1; k < length; k++) // Traversing through remaining page string
					{
						if(pageString[k] == frames[j])
						{
							timeForNextPageHit[j] = k;
							break;
						}
					}
					if(timeForNextPageHit[j] == -1) // jth frame doesn't appear in the rest of the string
					{
						noOfFramesWhichDontAppear++;
					}
				}
				// Note that timeForNextPageHit is distinct for each frame, except if it is -1.
				// More than one frames can have timeForNextPageHit = -1, if they don't appear in remaining string.
				if(noOfFramesWhichDontAppear <= 1)
				{
					int maxTime = 0, frameSelectedToReplace = -1;
					for(j = 0; j < noOfFrames; j++)
					{
						if(timeForNextPageHit[j] == -1)
						{
							frameSelectedToReplace = j;
							break;
						}
						if(timeForNextPageHit[j] > maxTime)
						{
							maxTime = timeForNextPageHit[j];
							frameSelectedToReplace = j;
						}
					}
					frames[frameSelectedToReplace] = pageString[i];
					timeStampForFrame[frameSelectedToReplace] = time;
					time++;
					printf("Page fault registered. Page replaced (by OPR). Current frames: ");
					printFrames(frames, noOfFrames);
				}
				else // Do FIFO with the frames which have timeForNextPageHit = -1
				{
					int leastTime = INT_MAX, frameSelectedToReplace = -1;
					for(j = 0; j < noOfFrames; j++)
					{
						if(timeStampForFrame[j] < leastTime && timeForNextPageHit[j] == -1)
						{
							leastTime = timeStampForFrame[j];
							frameSelectedToReplace = j;
						}
					}
					frames[frameSelectedToReplace] = pageString[i];
					timeStampForFrame[frameSelectedToReplace] = time;
					time++;
					printf("Page fault registered. Page replaced (by FIFO on pages which don't appear in remaining string). Current frames: ");
					printFrames(frames, noOfFrames);
				}
			}
		}
	}
	printf("No. of page hits = %d\nNo. of page faults = %d\n", pageHits, pageFaults);
}
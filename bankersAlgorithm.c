#include<stdio.h>

int n; // Number of processes
int m; // Number of resources

void safe_sequence(int finished[], int allocation[][m], int max[][m], int need[][m], int available[], int ans[], int st)
{
    int i, j, k, flag;
    for(j = 0; j < n; j++)
    {
        if(finished[j] == 0)
        {
            flag = 1;
            for(k = 0; k < m; k++)
            {
                if(need[j][k] > available[k])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1)
            {
                st++;
                ans[st] = j;
                finished[j] = 1;
                for(k = 0; k < m; k++)
                {
                    available[k] = available[k] + allocation[j][k];
                }
                safe_sequence(finished, allocation, max, need, available, ans, st);
                for(k = 0; k < m; k++)
                {
                    available[k] = available[k] - allocation[j][k];
                }
                st--;
                finished[j] = 0;
            }
        }
    }
    if(st == n - 1) 
    {
        for(i = 0; i < n - 1; i++)
        {
            printf("%d, ", ans[i]+1);
        }
        printf("%d\n", ans[n - 1]);
    }
}

int main()
{

	int i, j, k; // Iterators
    int st = -1; // Number of processes in the safe sequence
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the number of resources: ");
	scanf("%d", &m);
	int allocation[n][m], max[n][m], need[n][m];
	int available[m], finished[n], ans[n];
	// Allocation Matrix
	for(i = 0; i < n; i++)
	{
		printf("Enter the no. of resources allocated per resource type for process %d: ", i);
		for(j = 0; j < m; j++)
		{
			scanf("%d", &allocation[i][j]);
		}
	}
	// Max Matrix
	for(i = 0; i < n; i++)
	{
		printf("Enter the max no. of resources required per resource type for process %d: ", i);
		for(j = 0; j < m; j++)
		{
			scanf("%d", &max[i][j]);
		}
	}
	// Need Matrix
	for(i = 0; i < n; i++)
	{
    	for(j = 0; j < m; j++)
    	{
    		need[i][j] = max[i][j] - allocation[i][j]; 
    	}
    }
    // Available Array
    for(j = 0; j < m; j++)
    {
    	printf("Enter the number of resources available of type %d: ", j);
    	scanf("%d", &available[j]);
    }  
    // Finished Array
	for(i = 0; i < n; i++)
	{
		finished[i] = 0;
	}
    printf("\nSafe sequences are:\n");
    safe_sequence(finished, allocation, max, need, available, ans, st);
}

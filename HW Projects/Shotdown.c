#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGE 100000
#define NMAX 11

int n, acts[NMAX], order[NMAX], best[NMAX], maxDrop = -RANGE, done[NMAX], temp[NMAX][NMAX];

void perm(int num_actions, int temp_drop);
//====================================================================================================================
int main() 
{
    //input
    scanf("%d", &n);

    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &acts[i]);
    }
    
    //in actions
    for (int i = 0; i < n; i++) 
    {
    
        for (int j = 0; j < n; j++) 
        {
            scanf("%d", &temp[i][j]);
        }
    }

    //Call the permutation function
    perm(0,0);

    //Print stuff
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", best[i]+1);
    }


    return 0;
}
//====================================================================================================================
void perm(int numActs, int drop) 
{
    //Base Case <- Ryhmes so it must be true
    if (numActs == n) 
    {
        if (drop > maxDrop) 
        {
            maxDrop = drop;
            
            for (int i = 0; i < n; i++) 
            {
                best[i] = order[i];
            }
        }
        return;
    }

    //This is the recursion <- does not rhyme so might not be true
    for (int i = 0; i < n; i++) 
    {
        if (!done[i]) 
        {
            done[i] = 1;
            order[numActs] = i; 
            
            int newDrop = drop + acts[i];
            
            for (int j = 0; j < numActs; j++) 
            {
                newDrop += temp[order[j]][i];
            }

            //Recursion
            perm(numActs+1, newDrop);
            done[i] = 0;
        }
    }
}
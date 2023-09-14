#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_N 500000
#define MAX_S 21

struct tugboat 
{
    int x, y, dist;
    char name[MAX_S];
};

int cmp(const void* a, const void* b);

int xs, ys, x_n, y_n;

//====================================================================================================================
int main() 
{
    //vars
    int i, n, numTugs = 0, prevx = -1, prevy = -1;
    char (*tugs)[MAX_S] = malloc(n * sizeof(*tugs));
    //take input
    scanf("%d%d%d%d", &xs, &ys, &x_n, &y_n);
    scanf("%d", &n);
    
    //create array of boats
    struct tugboat* tugboats = malloc(n * sizeof(struct tugboat));

    for (i = 0; i < n; i++) 
    {
        scanf("%d%d%s", &tugboats[i].x, &tugboats[i].y, tugboats[i].name);
        int dx = tugboats[i].x - xs;
        int dy = tugboats[i].y - ys;
        tugboats[i].dist = dx * dx + dy * dy;
    }
  
    //sort function
    qsort(tugboats, n, sizeof(struct tugboat), cmp);
    
    //change vars
    for (i = 0; i < n; i++) 
    {
        if (tugboats[i].x >= prevx && tugboats[i].y >= prevy && tugboats[i].dist <= x_n * x_n + y_n * y_n) 
        {
            strcpy(tugs[numTugs], tugboats[i].name);
            numTugs++;
            prevx = tugboats[i].x;
            prevy = tugboats[i].y;
        }
    }
    //print tugs
    printf("%d\n", numTugs);
    for (i = 0; i < numTugs; i++) 
    {
        printf("%s\n", tugs[i]);
    }

    free(tugboats);
    free(tugs);

    return 0;
}
//====================================================================================================================
// Comparison function for qsort
int cmp(const void* a, const void* b) {
    const struct tugboat* t1 = (const struct tugboat*) a;
    const struct tugboat* t2 = (const struct tugboat*) b;

    int dx1 = t1->x - x_n;
    int dy1 = t1->y - y_n;
    int dx2 = t2->x - x_n;
    int dy2 = t2->y - y_n;

    int dist1 = dx1 * dx1 + dy1 * dy1 - t1->dist;
    int dist2 = dx2 * dx2 + dy2 * dy2 - t2->dist;

    if (dist1 != dist2) 
    {
        return dist1 - dist2;
    } 
    else 
    {
        return strcmp(t1->name, t2->name);
    }
}

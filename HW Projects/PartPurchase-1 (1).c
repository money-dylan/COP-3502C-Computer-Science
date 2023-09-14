#include <stdio.h>
#include <stdlib.h>

typedef struct {
int count; // The number of this part available
int extra_part; // The additional part that comes when purchasing
int price; // The price of purchasing the part
}Part;

typedef struct {
int known; // Is the component known to the repair crew
int part_req; // The part required to fix
int num_comp_rev; // Number of components revealed when fixed
int * comp_rev; // Array of revealed components when fixed
}Component;

//====================================================================================================================
int main() {
    //vars
    int numComponents, numParts, i, j, totalCost = 0;
    
    //read inputs
    scanf(" %d", &numParts);

    // make array of parts
    Part parts[numParts + 1];
    for (i = 1; i <= numParts; i++) 
    {
        int price, extra_part;
        scanf(" %d %d", &price, &extra_part);
        parts[i] = (Part){0, extra_part, price};
    }

    // read inputs
    scanf(" %d", &numComponents);
    Component components[numComponents + 1];
    
    // array of comps
    for (i = 1; i <= numComponents; i++) 
    {
        int part_req, num_comp_rev;
        scanf(" %d %d", &part_req, &num_comp_rev);
        int *comp_rev = (int *)malloc(num_comp_rev * sizeof(int));
        for (j = 0; j < num_comp_rev; j++) 
        {
            scanf(" %d", &comp_rev[j]);
        }
        components[i] = (Component){0, part_req, num_comp_rev, comp_rev};
    }

    // Create queue
    int queue[numComponents + 1], front = 0, rear = 0;
    queue[rear++] = 1;
    components[1].known = 1;

    // While components in queue
    while (front != rear) 
    {
        int current = queue[front++];
        int partNeed = components[current].part_req;
        
        // If part not available
        if (parts[partNeed].count == 0) 
        {
            totalCost += parts[partNeed].price;
            parts[partNeed].count++;
            parts[parts[partNeed].extra_part].count++;
            queue[rear++] = current;
        } 
        // part available
        else 
        {
            parts[partNeed].count--;
            for (j = 0; j < components[current].num_comp_rev; j++) 
            {
                int revealed = components[current].comp_rev[j];
                if (!components[revealed].known) 
                {
                    components[revealed].known = 1;
                    queue[rear++] = revealed;
                }
            }
        }
    }
    
    //print correct answer i hope
    printf("%d\n", totalCost);
    
    for (i = 1; i <= numComponents; i++) 
    {
        free(components[i].comp_rev);
    }

    return 0;
}
//====================================================================================================================
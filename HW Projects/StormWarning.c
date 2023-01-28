//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defines
#define NAME_LEN 20
#define DEFAULT_CAP 5;

//structs
typedef struct Boat Boat;
typedef struct ArrayList ArrayList;

struct Boat 
{
    int start_x, start_y, start_time;
    char dir, name[NAME_LEN + 1];
};

struct ArrayList 
{
    struct Boat * array;
    int size, cap;
};

ArrayList * createList();

void appendToList(ArrayList * list, Boat newBoat);
void query(int x, int y, int storm_width, int storm_height, int world_width, int world_height, ArrayList * list, int numBoats);
void moveShips(ArrayList * list, int timePassed, int numBoats, int width, int height);

//====================================================================================================================
int main()
{
    // main() comments
    //vars
    int width, height, time= 0, x, y, w, h, numBoats = 0, timePass;
    int bool = 1;

    char dir, name[21], command;

    ArrayList * list = createList();

    // Read the size of the world
    //take init input
    scanf(" %d %d", &width, &height);

    // Initialize the current time
    time = 0;


    // Read the first command

    // Loop until the exit command is given
    while(scanf(" %c", &command) != EOF)
    {
        // Determine the command type
        switch (command)
        {
        case '1':
            //take inputs
            scanf("%d %d %c %s", &x, &y, &dir, name);

            //make struct and take in int values
            struct Boat newBoat;
            newBoat.start_x = x;
            newBoat.start_y = y;
            newBoat.start_time = time;

            //assign char values
            newBoat.dir = dir;
            strcpy(newBoat.name, name);

            //add boat to list
            appendToList(list, newBoat);
            numBoats++;
            break;
        case '2':
            // TIME COMMAND
            scanf("%d", &timePass);
            moveShips(list, timePass, numBoats, width, height);
            // Update the current time
            break;
        case '3':
            // STORM COMMAND
            // Read in the storm information
            scanf("%d %d %d %d", &x, &y, &w, &h);
            query(x, y, w, h, height, width, list, numBoats);
            break;
        case '4':
            //exit commmand
            goto exit_loop;
            break;

        default:
            break;
        }
    }

    //break out of switch and free memory
    exit_loop: ;
    // Clean up memory
        free(list->array);
        free(list);
    // Exit successfully
    return 1;
}

//====================================================================================================================

ArrayList * createList() {
    ArrayList * list = (ArrayList *) malloc(sizeof(ArrayList));
    list->size = 0;
    list->cap = DEFAULT_CAP;
    list->array = (Boat *) malloc(sizeof(Boat) * list->cap);
    return list;
}

//====================================================================================================================

void appendToList(ArrayList * list, Boat newBoat)
{
     // Given a list and a boat tot add to it, add the boat to the end of the list
    // Expand the list if necessary
    if (list->size == list->cap) {
        list->cap *= 2;
        list->array = (Boat *) realloc(list->array, list->cap * sizeof(Boat));
    }
    //add boat to list
    list->array[list->size] = newBoat;
    list->size++;
}
//====================================================================================================================
void query(int x, int y, int storm_width, int storm_height, int world_width, int world_height, ArrayList * list, int numBoats)
{
    //vars
    int numAffected = 0;
    int * affected = (int *) malloc(10 * sizeof(int));
    int xArea = x + storm_width;
    int yArea = y + storm_height;
    int correctedX = xArea - world_width;
    int correctedY = yArea - world_width;

    
    //check which boats are affected
    for(int i = 0; i < numBoats; i++)
    {
        if(list->array[i].start_x < xArea && list->array[i].start_x >= x || list->array[i].start_x < correctedX && correctedX >= 0)
        {
            if(list->array[i].start_y < yArea && list->array[i].start_y >= y || list->array[i].start_y < correctedY && correctedX >= 0)
            {
                affected[numAffected] = i;
                numAffected++;
            }
        }
    }

    //output num of affected boats
    printf("%d\n", numAffected);

    //print affected Boat names
    for(int i = 0; i < numAffected; i++)
    {
        printf("%s\n", list->array[affected[i]].name);
    }

    //clean
    free(affected);
}

//====================================================================================================================

void moveShips(ArrayList * list, int timePassed, int numBoats, int width, int height)
{
    //iterate through ships and move them
    for(int i = 0; i < numBoats; i++)
    {
        if(list->array[i].dir == 'U')
        {
            list->array[i].start_y = (list->array[i].start_y + timePassed) % height;
        }
        else if (list->array[i].dir == 'D')
        {
            list->array[i].start_y = (list->array[i].start_y - timePassed + height) % height;
        }
        else if (list->array[i].dir == 'R')
        {
            list->array[i].start_x = (list->array[i].start_x + timePassed) % width;
        }
        else if (list->array[i].dir == 'L')
        {
            list->array[i].start_x = (list->array[i].start_x - timePassed + width) % width;
        }

        //see if ships fell off flat earth
        if(list->array[i].start_x < 0)
        {
            list->array[i].start_x = width;
        }
        else if(list->array[i].start_x > width)
        {
            list->array[i].start_x = 0;
        }

        if(list->array[i].start_y < 0)
        {
            list->array[i].start_x = height;
        }
        else if(list->array[i].start_y > height)
        {
            list->array[i].start_x = 0;
        }
    }
}

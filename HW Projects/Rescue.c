//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LOWER 1
#define UPPER 100
#define DEFAULT_CAP 5;

typedef struct Boat Boat;
typedef struct ArrayList ArrayList;

struct Boat
{
  int speed, location, currLocation;
};

struct ArrayList 
{
    struct Boat * array;
    int size, cap;
};

ArrayList * createList();

void appendToList(ArrayList * list, Boat newBoat);
int findBoat(ArrayList * list, int speed, int location, int numBoats);
void moveBoats(ArrayList * list, int numBoats);
void removeBoat(ArrayList * list, int position, int numBoats);

//====================================================================================================================
int main()
{
//vars
  int s, l, theBoat, numBoats= 0;
  
  ArrayList * list = createList();
  
  //take in limits
  scanf(" %d%d", &s, &l);
  
  for(int i = 0; i <= s; i ++)
  {
    for(int j = 0; j <= l; j++)
    {
      struct Boat newBoat;
      newBoat.speed = i;
      newBoat.location = j;
      newBoat.currLocation = j;
      appendToList(list, newBoat);
      numBoats++;
    }
  }
  
  //gameloop
   findBoat(list, s, l, numBoats);

  free(list->array);
  free(list);
  return 0;
}
//====================================================================================================================
ArrayList * createList() 
{
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
int findBoat(ArrayList * list, int speed, int location, int numBoats)
{
  int midpoint = 0;
  
  for(int g = 0; g < numBoats; g++)
  {
    midpoint+=list->array[g].currLocation;
  }
  midpoint= midpoint/ (numBoats);

  char input[6];

  fflush(stdout);
  
  for(int i = 0; i < 24; i++)
  {
    moveBoats(list, numBoats);
    if(numBoats == 1)
    {
      printf("!%d\n", list->array[0].currLocation);
      fflush(stdout);
      return 1;
    }
    else
    {
      midpoint = 0;
      
      for(int g = 0; g < numBoats; g++)
      {
        midpoint+=list->array[g].currLocation;
      }
      midpoint= midpoint/ (numBoats);
      
      printf("?%d\n", midpoint);
      fflush(stdout);
      scanf(" %[^\n]s", input);
      
      if(strcmp(input, "Wake") == 0)
      {
        for(int j = 0; j < numBoats; j++)
        {
          if(list->array[j].currLocation <= midpoint)
          {
             removeBoat(list, j, numBoats);
             j--;
             numBoats--;
          }
        }
      }
      else if(strcmp(input, "No Wake") == 0)
      {
        for(int j = 0; j < numBoats; j++)
        {
          if(list->array[j].currLocation > midpoint)
          {
            removeBoat(list, j, numBoats);
            j--;
            numBoats--;
          }
        }
      }
      }
    }
    
  return 0;
  
}
//====================================================================================================================
void moveBoats(ArrayList * list, int numBoats)
{
  for(int i = 0; i <= numBoats; i++)
  {
    list->array[i].currLocation = list->array[i].currLocation + list->array[i].speed;
  }
}
//====================================================================================================================
void removeBoat(ArrayList * list, int position, int numBoats)
{
  if(numBoats > 1)
  {
    for(int i = position; i < numBoats; i++)
    {
      list->array[i] = list->array[i + 1];
    }
  }
}
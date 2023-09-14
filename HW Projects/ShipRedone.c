#include <stdio.h>

#define MAX_LINE_NUMBER 100    
#define MAX_SHIPS_PER_LINE 100 
#define MAX_NAME_LENGTH 20     


void setShip(int lineNumber);
void displayBoat(int totalShipLines, int week);


char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 1];
int totalShipsPerLine[MAX_LINE_NUMBER] = {0};
//====================================================================================================================
int main()
{
    //vars
    int totalShip;
    char input;
    scanf("%d", &totalShip);
    
    //take input
    scanf("%c", &input);

    // set ships
    for (int i = 0; i < totalShip; i++)
    {
        setShip(i);
    }

    // take input
    int totalCust;
    scanf("%d", &totalCust);

    while (totalCust > 0)
    {
        int week;       
        scanf("%d", &week);

        // display boars
        displayBoat(totalShip, week);

        printf("\n");

        totalCust--;
    }
    return 0;
}
//====================================================================================================================
void setShip(int lineNumber)
{
    //vars
    int currentShipIdx = 0, shipNameIndex = 0;  

    while (1)
    {
        char c;
        scanf("%c", &c);

        
        if (c == ' ' || c == '\n')
        {
            names[lineNumber][currentShipIdx][shipNameIndex] = '\0';
            currentShipIdx++;
            shipNameIndex = 0;

            // break if new line
            if (c == '\n')
            {
                break;
            }
        }
        else
        {
            names[lineNumber][currentShipIdx][shipNameIndex] = c;
            shipNameIndex++;
        }
    }

    totalShipsPerLine[lineNumber] = currentShipIdx;
}

//====================================================================================================================
void displayBoat(int totalShipLines, int week)
{
    for (int i = 0; i < totalShipLines; i++) 
    {
        // total ships on curr line
        int totalCurrShip = totalShipsPerLine[i];

        if (totalCurrShip == 0) {
            printf("EMPTY ");
        } else {
            int shipIndex = (week - 1) % totalCurrShip;

            // print ships
            printf("%s ", names[i][shipIndex]);
        }
    }
}
//====================================================================================================================
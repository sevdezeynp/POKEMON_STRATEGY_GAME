#include <string.h>
#include "pokemon.h"
#define TYPES_COUNT 342
void initializeTypes(Type types[])
{
    FILE *file = fopen("types.txt", "r");
    char line[100];
    int typeIndex = 0;
    int effectIndex = 0;
    char currentAttacker[20];
    while (fgets(line, sizeof(line), file))
    {
        // why do I need to remove the \n char?
        char defenderName[20];
        float multiplier;
        // sscanf reads formatted input from a string and returns the number of items successfully read
        if (sscanf(line, "%s %f", defenderName, &multiplier) == 2)
        {
            strcpy(types[typeIndex].typeEffect[effectIndex].atkName, currentAttacker);
            strcpy(types[typeIndex].typeEffect[effectIndex].defName, defenderName);
            types[typeIndex].typeEffect[effectIndex].multiplier = multiplier;

            effectIndex++; // move to the next typeEffect in the array
            // after 18 typeEffects move to the next type
            if (effectIndex == 18)
            {
                typeIndex++;
                effectIndex = 0;
            }
        }
        else
        {                                  // if the multiplier is not found then it is an attack name
            strcpy(currentAttacker, line); // dest , source
            strcpy(types[typeIndex].name, currentAttacker);
            // remove newline character from the name
        }

        fclose(file);
    }
}
// untested method
void initializeMoves(Move moves[], Type types[])
{
    initializeTypes(types);
    FILE *file = fopen("moves.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char typeName[20];

        int movesIndex = 0;
        sscanf(line, "%s %s %s %f", moves[movesIndex].name, typeName, moves[movesIndex].category, moves[movesIndex].power);
        // assign the type corresponding to the move according to the type name

        int iterator = 0;
        Type type;
        while (iterator < TYPES_COUNT)
        {

            if (strcmp(types[iterator].name, typeName) == 0)
            {
                type = types[iterator];
                moves[movesIndex].type = type;
                break;
            }
            iterator++;
        }
        if (&type == NULL)
        {
            printf("Type not found for move: %s\n", moves[movesIndex].name);
            exit(1);
        }
        movesIndex++;
    }

    fclose(file);
}
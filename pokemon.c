#include <string.h>
#include <stdlib.h>
#include "pokemon.h"

void initializeTypes(Type types[])
{
    FILE *file = fopen("Texts/types.txt", "r");
    if (file == NULL)
    {
        printf("Error opening types.txt file\n");
        exit(1);
    }
    char line[100];
    int typeIndex = 0;
    int effectIndex = 0;
    char currentAttacker[20];
    while (fgets(line, sizeof(line), file))
    {
        // printf("DEBUG: Read line: [%s]\n", line);
        //  why do I need to remove the \n char?
        // because it changes the string comparison results
        // example result I get without removing \n
        /*DEBUG: Read line: [Ice 2
        ]*/

        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

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
            strcpy(currentAttacker, line); // dest , source //current attacker is the name of type
            strcpy(types[typeIndex].name, currentAttacker);
            // remove newline character from the name
        }
    }
    fclose(file);
}

void initializeMoves(Move moves[], Type types[])
{

    FILE *file = fopen("Texts/moves.txt", "r");
    if (file == NULL)
    {
        printf("Error opening Texts/moves.txt file\n");
        exit(1);
    }
    char line[100];
    int movesIndex = 0;

    // printf("DEBUG: Starting to read moves...\n");

    while (fgets(line, sizeof(line), file) && movesIndex < MOVES_COUNT)
    {
        // remove newline character from line
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }
        // printf("DEBUG: Line %d: [%s]\n", movesIndex, line);
        char moveName[20];
        char typeName[20];
        char categoryName[20];
        float power;
        int scanned = sscanf(line, "%s %s %s %f", moveName, typeName, categoryName, &power);
        // printf("DEBUG: Scanned %d items - Name:'%s' Type:'%s' Category:'%s' Power:%.2f\n",scanned, moveName, typeName, categoryName, power);

        if (scanned != 4)
        {
            printf("Couldn't parse line properly\nThe line was: %s\n", line);
            continue;
        }

        // assign the type corresponding to the move according to the type name
        int iterator = 0;
        int typeFound = 0;
        while (iterator < TYPES_COUNT)
        {

            if (strcmp(types[iterator].name, typeName) == 0) // find the corresponding type from the type name
            {
                moves[movesIndex].type = types[iterator];
                typeFound = 1;

                // printf("DEBUG: Found type '%s' for move '%s'\n", typeName, moveName);
                break;
            }
            iterator++;
        }
        if (!typeFound)
        {
            printf("Type '%s' not found for move '%s'\n", typeName, moveName);

            exit(1);
        }

        // convert categoryName to Category enum
        if (strcmp(categoryName, "Physical") == 0)
        {
            moves[movesIndex].category = Physical;
        }
        else if (strcmp(categoryName, "Special") == 0)
        {
            moves[movesIndex].category = Special;
        }
        else
        {
            printf("Unidentified category name: %s\n", categoryName);
            exit(1);
        }
        strcpy(moves[movesIndex].name, moveName);
        moves[movesIndex].power = power;

        movesIndex++;
    }

    fclose(file);
}
/*void initializePokemons(Pokemon pokemons[], Type types[], Move moves[])
{
    // assuming moves and types are already initialized

    FILE *file = fopen("pokemons.txt", "r");
    char line[100];
    int pokemonIndex = 0;
}*/
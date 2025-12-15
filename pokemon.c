#include <string.h>
#include <stdlib.h>
#include <time.h>
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
            // after 19 typeEffects move to the next type
            if (effectIndex == TYPES_EFFECT_COUNT)
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
void initializePokemons(Type types[], Move moves[], Pokemon pokemons[])
{
    // assuming moves and types are already initialized
    // pokemon attributes:
    /*
    char name[30];
    Type types[2];
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    Move moves[4];

    sample lines from pokemon.txt:
    Venusaur Grass Poison 80 82 83 100 100 80
    Charmander Fire - 39 52 43 60 50 65

    */
        srand(time(NULL));

        
    FILE *file = fopen("Texts/pokemon.txt", "r");
    if (file == NULL)
    {
        printf("Error opening Texts/pokemon.txt file\n");
        exit(1);
    }
    char line[100];
    int pokemonIndex = 0;

    while (fgets(line, sizeof(line), file) && pokemonIndex < POKEMONS_COUNT)
    {

        // remove newline character from line
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        char type1name[20];
        char type2name[20];
        int scanned = sscanf(line, "%s %s %s %d %d %d %d %d %d",
                             pokemons[pokemonIndex].name,
                             type1name,
                             type2name,
                             &pokemons[pokemonIndex].maxHP,
                             &pokemons[pokemonIndex].attack,
                             &pokemons[pokemonIndex].defense,
                             &pokemons[pokemonIndex].spAtk,
                             &pokemons[pokemonIndex].spDef,
                             &pokemons[pokemonIndex].speed);

        if (scanned != 9)
        {
            printf("Couldn't parse line properly\nThe line was: %s\n", line);
            continue;
        }
        // initialize currentHP to be equal to maxHP
        pokemons[pokemonIndex].currentHP = pokemons[pokemonIndex].maxHP;

        // match the first type name with types object and assign them to the pokemon

        int iterator = 0;
        int typeFound = 0;
        while (iterator < TYPES_COUNT)
        {

            if (strcmp(types[iterator].name, type1name) == 0) // find the corresponding type from the type name
            {
                pokemons[pokemonIndex].types[0] = types[iterator];
                typeFound = 1;

                break;
            }
            iterator++;
        }
        if (!typeFound)
        {
            printf("First type '%s' not found for pokemon '%s'\n", type1name, pokemons[pokemonIndex].name);

            exit(1);
        }

        if (strcmp(type2name, "-") == 0)
        {
            strcpy(type2name, "None");
        }

        // match the second type name

        iterator = 0;
        typeFound = 0;
        while (iterator < TYPES_COUNT)
        {

            if (strcmp(types[iterator].name, type2name) == 0) // find the corresponding type from the type name
            {
                pokemons[pokemonIndex].types[1] = types[iterator];
                typeFound = 1;

                break;
            }
            iterator++;
        }
        if (!typeFound)
        {
            printf("Second type '%s' not found for pokemon '%s'\n", type2name, pokemons[pokemonIndex].name);

            exit(1);
        }

        // initialize moves randomly
        int selectedMoves[4];
        for (int i = 0; i < 4; i++)
        {
            int moveIndex;
            int isDuplicate;
            do
            {
                isDuplicate = 0;

                moveIndex = rand() % MOVES_COUNT;
                for (int j = 0; j < i; j++)
                {
                    if (selectedMoves[j] == moveIndex)
                    {
                        isDuplicate = 1;
                        break;
                    }
                }

            } while (isDuplicate);
            selectedMoves[i] = moveIndex;
            pokemons[pokemonIndex].moves[i] = moves[moveIndex];
        }
        pokemonIndex++;
    }

    fclose(file);
}
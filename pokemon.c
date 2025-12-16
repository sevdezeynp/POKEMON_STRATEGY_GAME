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

void initialize(Type types[], Move moves[], Pokemon pokemons[], Player *player1, Player *player2)
{
    srand(time(NULL));

    initializeTypes(types);
    initializeMoves(moves, types);
    initializePokemons(types, moves, pokemons);

    strcpy(player1->name, "Sunflower");
    strcpy(player2->name, "Jasmine");
    player1->currentIndex = 0; // initialize index to zero to include the first pokemon
    player2->currentIndex = 0;

    // assign six pokemon randomly to player 1
    int selectedPokemonIndicies[PLAYER_POKEMONS_COUNT];
    int isDuplicate;
    for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
    {
        int pokemonIndex;
        do
        {
            isDuplicate = 0;

            pokemonIndex = rand() % POKEMONS_COUNT;
            for (int j = 0; j < i; j++)
            {
                if (selectedPokemonIndicies[j] == pokemonIndex)
                {
                    isDuplicate = 1;
                }
            }
        } while (isDuplicate);
        selectedPokemonIndicies[i] = pokemonIndex;
        player1->pokemons[i] = pokemons[pokemonIndex];
    }

    for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
    {
        int pokemonIndex;
        do
        {
            isDuplicate = 0;

            pokemonIndex = rand() % POKEMONS_COUNT;
            for (int j = 0; j < i; j++)
            {
                if (selectedPokemonIndicies[j] == pokemonIndex)
                {
                    isDuplicate = 1;
                }
            }
        } while (isDuplicate);
        selectedPokemonIndicies[i] = pokemonIndex;
        player2->pokemons[i] = pokemons[pokemonIndex];
    }
}
// helper function
int isAlive(Player *player)
{
    for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
    {
        if (player->pokemons[i].currentHP > 0)
        {
            return 1;
        }
    }

    return 0;
}
void game(Player *player1, Player *player2)
{
    printf("====================================================\n");
    printf("==========Welcome-To-Pokemon-Strategy-Game==========\n");
    printf("====================================================\n");
    printf("Player1 name: %s\n", player1->name);
    printf("Player2 name: %s\n", player2->name);

    // The game end when one of the players has no Pokemon with currentHP value greater than 0
    int isOneAlive;
    int isTwoAlive;
    do
    {
        game_round(player1, player2);
        isOneAlive = isAlive(player1);

        isTwoAlive = isAlive(player2);

    } while (isOneAlive && isTwoAlive);
}

void game_round(Player *player1, Player *player2)
{
    printf("1->%s->> Choose an action to perform:\n", player1->name);
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    int p1_action;
    int p1_selectedMoveIndex;
    int p2_action;
    int p2_selectedMoveIndex;
    // I have to decrease indicies by one to not face IndexOutOfBounds Error
    scanf("%d", &p1_action);

    printf("====================================================\n");
    printf("2->%s->> Choose an action to perform,\n", player2->name);
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");

    scanf("%d", &p2_action);

    if (p1_action == 2) // handle switches first
    {
        // player1 choose change pokemon option, show available pokemons
        for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
        {
            if (player1->pokemons[i].currentHP <= 0)
            {
                continue;
            }
            printf("\n--- Pokemon #%d ---\n", i + 1);
            printf("Name: %s, HP: %d \n", player1->pokemons[i].name, player1->pokemons[i].currentHP);
        }
        printf("1->%s->> Choose one pokemon index: \n", player1->name);
        int newPokemonIndex;
        scanf("%d", &newPokemonIndex);
        if (newPokemonIndex < 1 || newPokemonIndex > 6)
        {
            printf("Invalid Pokemon selection!\n");
            // do something, ask again or return an error
        }
        player1->currentIndex = --newPokemonIndex; // decrease index by one
        printf("The current pokemon index for player %s is updated to %d\n", player1->name, player1->currentIndex);
    }
    if (p2_action == 2) // handle switches first
    {
        // player2 choose change pokemon option, show available pokemons
        for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
        {
            if (player2->pokemons[i].currentHP <= 0)
            {
                continue;
            }
            printf("\n--- Pokemon #%d ---\n", i + 1);
            printf("Name: %s, HP: %d \n", player2->pokemons[i].name, player2->pokemons[i].currentHP);
        }
        printf("2->%s->> Choose one pokemon index: \n", player2->name);
        int newPokemonIndex;
        scanf("%d", &newPokemonIndex);
        player2->currentIndex = --newPokemonIndex;
        printf("The current pokemon index for player %s is updated to %d\n", player2->name, player2->currentIndex);
    }
    if (p1_action == 1)
    {
        // player1 choose attack, show moves of the current pokemon
        printf("1->%s->> Select one of the moves of the current pokemon %s:\n", player1->name, player1->pokemons[player1->currentIndex].name);
        for (int j = 0; j < 4; j++)
        {
            printf("  %d. %-20s [%s] Power: %.0f\n",
                   j + 1,
                   player1->pokemons[player1->currentIndex].moves[j].name,
                   player1->pokemons[player1->currentIndex].moves[j].type.name,
                   player1->pokemons[player1->currentIndex].moves[j].power);
        }

        scanf("%d", &p1_selectedMoveIndex);

        if (p1_selectedMoveIndex > 4 || p1_selectedMoveIndex < 1)
        {
            printf("invalid move selection for %d\n", p1_selectedMoveIndex);
            // I should do something to skip the rest of the round or re ask for a correct input
        }
        --p1_selectedMoveIndex;
    }
    if (p2_action == 1)
    {
        // player2 choose attack, show moves of the current pokemon
        printf("2->%s->> Select one of the moves of the current pokemon %s:\n", player2->name, player2->pokemons[player2->currentIndex].name);
        for (int j = 0; j < 4; j++)
        {
            printf("  %d. %-20s [%s] Power: %.0f\n",
                   j + 1,
                   player2->pokemons[player2->currentIndex].moves[j].name,
                   player2->pokemons[player2->currentIndex].moves[j].type.name,
                   player2->pokemons[player2->currentIndex].moves[j].power);
        }

        scanf("%d", &p2_selectedMoveIndex);

        if (p2_selectedMoveIndex > 4 || p2_selectedMoveIndex < 1)
        {
            printf("invalid move selection for %d\n", p2_selectedMoveIndex);
            // I should do something to skip the rest of the round or re ask for a correct input
        }
        --p2_selectedMoveIndex;
    }

    // after taking all user entries let's do the attack!
    // in case they both decided to attack
    if (p1_action == 1 && p2_action == 1)
    {
        /*first damage will be given by faster Pokemon,if defender
        faints after taking damage it will not be able to attack, so
        other Pokemon will take no damage*/

        Player *faster = player1->pokemons[player1->currentIndex].speed >= player2->pokemons[player2->currentIndex].speed ? player1 : player2;
        Player *slower = player1->pokemons[player1->currentIndex].speed > player2->pokemons[player2->currentIndex].speed ? player2 : player1;
        int fasterMoveIndex = player1->pokemons[player1->currentIndex].speed >= player2->pokemons[player2->currentIndex].speed ? p1_selectedMoveIndex : p2_selectedMoveIndex;
        int slowerMoveIndex = player1->pokemons[player1->currentIndex].speed > player2->pokemons[player2->currentIndex].speed ? p2_selectedMoveIndex : p1_selectedMoveIndex;
        applyDamage(faster, slower, fasterMoveIndex);
        // change the current pokemon for defender if the pokemon
        if (slower->pokemons[slower->currentIndex].currentHP <= 0)
        {
            for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
            {
                if (slower->pokemons[i].currentHP > 0)
                {
                    slower->currentIndex = i;
                    break;
                }
            }
            printf("%s pokemon's faints!, Switched to the pokemon named %s\n", slower->name, slower->pokemons[slower->currentIndex].name);
            printf("Faster pokemon of %s has no damage\n", faster->name);
        }
        else
        {
            applyDamage(slower, faster, slowerMoveIndex);
            if (faster->pokemons[faster->currentIndex].currentHP <= 0)
            {
                for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
                {
                    if (faster->pokemons[i].currentHP > 0)
                    {
                        faster->currentIndex = i;
                        break;
                    }
                }
                printf("%s pokemon's faints!, Switched to the pokemon named %s\n", faster->name, faster->pokemons[faster->currentIndex].name);
            }
        }
    }
    else if (p1_action == 1)
    {
        applyDamage(player1, player2, p1_selectedMoveIndex);
        if (player2->pokemons[player2->currentIndex].currentHP <= 0)
        {
            for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
            {
                if (player2->pokemons[i].currentHP > 0)
                {
                    player2->currentIndex = i;
                    break;
                }
            }
            printf("%s pokemon's faints!, Switched to the pokemon named %s\n", player2->name, player2->pokemons[player2->currentIndex].name);
        }
    }
    else if (p2_action == 1)
    {
        applyDamage(player2, player1, p2_selectedMoveIndex);
        if (player1->pokemons[player1->currentIndex].currentHP <= 0)
        {
            for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
            {
                if (player1->pokemons[i].currentHP > 0)
                {
                    player1->currentIndex = i;
                    break;
                }
            }
            printf("%s pokemon's faints!, Switched to the pokemon named %s\n", player1->name, player1->pokemons[player1->currentIndex].name);
        }
    }
}

void applyDamage(Player *attacker, Player *defender, int attackerMoveIndex)
{
    /*
        damage = power of the move *
        physical or special attack according to the pokemon *
        type effect1*
        type effect2 *
        same type attack bonus (which is 1.5 if attack move type matches with one of types of attacker Pokemon, and is 1 otherwise)
         / physical or special defense
       */

    Pokemon *attacker_pokemon = &attacker->pokemons[attacker->currentIndex];
    Pokemon *defender_pokemon = &defender->pokemons[defender->currentIndex];

    float powerOfMove = attacker_pokemon->moves[attackerMoveIndex].power;

    int attack;
    int defense;
    if (attacker_pokemon->moves[attackerMoveIndex].category == 0)
    {
        // then it is Physical category
        attack = attacker_pokemon->attack;
        defense = defender_pokemon->defense;
    }
    else
    {
        attack = attacker_pokemon->spAtk;
        defense = defender_pokemon->spDef;
    }

    float typeEffect1 = 1;
    float typeEffect2 = 1;
    // find the multiplier of corresponding typeEffect.
    int type1Found = 0;

    for (int i = 0; i < TYPES_EFFECT_COUNT; i++)
    {
        if (strcmp(defender_pokemon->types[0].name, attacker_pokemon->moves[attackerMoveIndex].type.typeEffect[i].defName) == 0)
        {
            // You must access the move's type
            typeEffect1 = attacker_pokemon->moves[attackerMoveIndex].type.typeEffect[i].multiplier;
            type1Found = 1;
        }
    }
    if (!type1Found)
    {
        printf("type 1 multiplier is not found for defender type name:%s", defender_pokemon->types[0].name);
    }

    // for type Effect 2 check for none type
    if (strcmp(defender_pokemon->types[1].name, "None") == 0)
    {
        typeEffect2 = 1;
    }
    else
    {
        int type2Found = 0;
        for (int i = 0; i < TYPES_EFFECT_COUNT; i++)
        {
            if (strcmp(defender_pokemon->types[1].name, attacker_pokemon->moves[attackerMoveIndex].type.typeEffect[i].defName) == 0)
            {

                typeEffect2 = attacker_pokemon->moves[attackerMoveIndex].type.typeEffect[i].multiplier;
                type2Found = 1;
            }
        }
        if (!type2Found)
        {
            printf("type 2 multiplier is not found for defender type name:%s", defender_pokemon->types[1].name);
        }
    }

    // check for same attack type bonus
    // if attack move type = attacker->pokemons[attacker->currentIndex].moves[attackerMoveIndex].type.name
    // attacker's pokemon type1 or type2

    float STAB = 1;

    if (strcmp(attacker_pokemon->moves[attackerMoveIndex].type.name, attacker_pokemon->types[0].name) == 0 || strcmp(attacker_pokemon->moves[attackerMoveIndex].type.name, attacker_pokemon->types[1].name) == 0)
    {

        STAB = 1.5;
    }

    float damage = powerOfMove * attack * typeEffect1 * typeEffect2 * STAB / defense;

    // decrease defender's pokemon's HP
    defender->pokemons[defender->currentIndex].currentHP -= (int)damage;
    printf("%s used %s! Dealt %d damage to %s.\n",
           attacker_pokemon->name, attacker_pokemon->moves[attackerMoveIndex].name, (int)damage, defender_pokemon->name);
}

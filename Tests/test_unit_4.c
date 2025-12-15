#include <stdlib.h>
#include "..\pokemon.h"
// this test file is to verify initialize() function accuracy

int main()
{

    Type *types = malloc(sizeof(Type) * TYPES_COUNT);


    Move *moves = malloc(sizeof(Move) * MOVES_COUNT);
  
    Pokemon *pokemons = malloc(sizeof(Pokemon) * POKEMONS_COUNT);

    Player Player1;
    Player Player2;

    initialize(types, moves, pokemons, &Player1, &Player2);

    // print player info to check if the initialization phase done correctly

    printf("player1 name : %s\n", Player1.name);
    printf("player1 current Index : %d\n", Player1.currentIndex);

    for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
    {
        printf("\n--- Pokemon #%d ---\n", i + 1);
        printf("Name: %s\n", Player1.pokemons[i].name);
        printf("Types: %s / %s\n",
               Player1.pokemons[i].types[0].name,
               Player1.pokemons[i].types[1].name);
        printf("HP: %d/%d (Current/Max)\n",
               Player1.pokemons[i].currentHP,
               Player1.pokemons[i].maxHP);
        printf("Stats: ATK=%d | DEF=%d | SpA=%d | SpD=%d | SPD=%d\n",
               Player1.pokemons[i].attack,
               Player1.pokemons[i].defense,
               Player1.pokemons[i].spAtk,
               Player1.pokemons[i].spDef,
               Player1.pokemons[i].speed);
        printf("Moves:\n");
        for (int j = 0; j < 4; j++)
        {
            printf("  %d. %-20s [%s] [%s] Power: %.0f\n",
                   j + 1,
                   Player1.pokemons[i].moves[j].name,
                   Player1.pokemons[i].moves[j].type.name,
                   Player1.pokemons[i].moves[j].category == Physical ? "Physical" : "Special",
                   Player1.pokemons[i].moves[j].power);
        }
    }

    printf("==============================================\n");
    printf("player2 name : %s\n", Player2.name);
    printf("player2 current Index : %d\n", Player2.currentIndex);

    for (int i = 0; i < PLAYER_POKEMONS_COUNT; i++)
    {
        printf("\n--- Pokemon #%d ---\n", i + 1);
        printf("Name: %s\n", Player2.pokemons[i].name);
        printf("Types: %s / %s\n",
               Player2.pokemons[i].types[0].name,
               Player2.pokemons[i].types[1].name);
        printf("HP: %d/%d (Current/Max)\n",
               Player2.pokemons[i].currentHP,
               Player2.pokemons[i].maxHP);
        printf("Stats: ATK=%d | DEF=%d | SpA=%d | SpD=%d | SPD=%d\n",
               Player2.pokemons[i].attack,
               Player2.pokemons[i].defense,
               Player2.pokemons[i].spAtk,
               Player2.pokemons[i].spDef,
               Player2.pokemons[i].speed);
        printf("Moves:\n");
        for (int j = 0; j < 4; j++)
        {
            printf("  %d. %-20s [%s] [%s] Power: %.0f\n",
                   j + 1,
                   Player2.pokemons[i].moves[j].name,
                   Player2.pokemons[i].moves[j].type.name,
                   Player2.pokemons[i].moves[j].category == Physical ? "Physical" : "Special",
                   Player2.pokemons[i].moves[j].power);
        }
    }
}
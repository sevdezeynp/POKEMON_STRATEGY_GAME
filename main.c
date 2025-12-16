#include <stdlib.h>
#include "pokemon.h"

int main()
{

    Type *types = malloc(sizeof(Type) * TYPES_COUNT);

    Move *moves = malloc(sizeof(Move) * MOVES_COUNT);

    Pokemon *pokemons = malloc(sizeof(Pokemon) * POKEMONS_COUNT);

    Player Player1;
    Player Player2;

    initialize(types, moves, pokemons, &Player1, &Player2);

    game(&Player1, &Player2);

    free(types);
    free(moves);
    free(pokemons);
    if (isAlive(&Player1))
    {
        printf("Congratulations! <<%s>> won the game, sorry for %s", Player1.name, Player2.name);
    }
    else
    {
        printf("Congratulations! <<%s>> won the game, sorry for %s", Player2.name, Player1.name);
    }
}
#define TYPES_COUNT 18
#define MOVES_COUNT 486
#define POKEMONS_COUNT 1015
#include <stdio.h>



typedef struct {
    char atkName[20];
    char defName[20];
    float multiplier;
}TypeEffect;

typedef struct {
    char name[20];
    TypeEffect typeEffect[18];

}Type;

typedef enum{
Physical, Special
}Category;

typedef struct{
    char name[30];
    Type type;
    Category category;
    float power;
}Move;

typedef struct {

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
}Pokemon;

typedef struct{
    char name[30];
    Pokemon pokemons[6];
    int currentIndex;
}Player;

//initialize function protoytpe
void initializeTypes(Type types[]);
void initializeMoves(Move moves[], Type types[]);
void initializePokemons(Pokemon pokemons[], Type types[], Move moves[]);

void initialize(Type types[],Move moves[], Pokemon pokemons[],Player *player1,Player *player2);

//game function prototypes
void game(Player * player1, Player * player2);
void round ( Player * player1, Player * player2);
void applyDamage(Player * attacker, Player defender, int attackerMoveIndex, int defenderMoveIndex, int attackerAction, int defenderAction);
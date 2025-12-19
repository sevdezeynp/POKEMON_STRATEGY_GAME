// this unit will test type initialization function in pokemon.c
#include <stdio.h>
#include "..\\pokemon.h"
// pokemon.h includes functions prototypes while pokemon.c includes their implementation

int main(){
    Type types[TYPES_COUNT];
    initializeTypes(types);

    // Print the initialized types to verify
    for (int i =0 ; i<TYPES_COUNT; i++){

        printf("Type: %s\n", types[i].name);
        for (int j=0; j<TYPES_EFFECT_COUNT; j++){

            printf("Attacker: %s, Defender: %s, Multiplier: %.2f\n", types[i].typeEffect[j].atkName, types[i].typeEffect[j].defName, types[i].typeEffect[j].multiplier);
        }
    }
}
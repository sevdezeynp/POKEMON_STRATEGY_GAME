# POKEMON_STRATEGY_GAME

1-Introduction
A Pokemon themed text-based strategy game.

2- Implementation Details

2.1 Structs
For this game, you should implement the following structs. Files will be provided for initialization
values of Pokemon, Type/TypeEffect and Move structs.

2.1.1 TypeEffect
Your TypeEffect struct should have the following attributes:
• atkName: Name of the attacking type
• defName: Name of the defending type
• multiplier: Damage multiplier

2.1.2 Type
Your Type struct should have the following attributes:
• name: Name of Type
• effects: A TypeEffect array with size eighteen

2.1.3 Move
Your Move struct should have the following attributes:
• name: Name of Move
• type: A Type showing the type of move
• category: Special attack or physical attack (use enum for this attribute)
• power: Power of attack

2.1.4 Pokemon
Your Pokemon struct should have the following attributes:
• name: Name of Pokemon
• types: A Type array with size two
• maxHP: Health points of Pokemon at the beginning
• currentHP: Current health points of Pokemon
• attack: Attack strength of Pokemon
• defense: Defense strength of Pokemon
• spAtk: Special attack strength of Pokemon
• spDef: Special defense strength of Pokemon
• speed: Moving speed of Pokemon
• moves: A Move array with size four

2.1.5 Player
Your Player struct should have the following attributes:
• name: Name of Player
• Pokemons: A Pokemon array with size of six
• currentIndex: Current index in Pokemons array

2.2 Functions
2.2.1 main
In the main function, you should create the following variables:
• Types: A Type array with a size of 18
• Moves: A Move array with a size of 486
• Pokemons: A Pokemon array with a size of 1015
• Player1: First Player
• Player2: Second Player

After creating these variables, you should initialize them by sending them to initialize
function.

Once the structs are initialized, the game may start. For gameplay, you should call game
with necessary parameters.

Your main function is not supposed to contain any other codes.

2.2.2 initialize
You should implement a function named ’initialize’ that will call necessary initialization functions
and then initialize Player1 and Player2.

Your function should first call initializeTypes in order to initalize Types. Later, you should
call initializeMoves for initializing Moves. After that, call initializePokemons to initialize Pokemons.
After calling these three initialization functions, you should initialize Player1 and Player2.

You can give player names as you wish, however Pokemons should be assigned randomly. You
should use rand function to randomly choose six indices between 0 and 1014, then Pokemon’s
corresponding to these six indices should be assigned to Pokemons array. All Pokemon’s
should be unique, so please check for duplicates. currentIndex should be initialized as 1.

2.2.3 initializeTypes
You should initialize the Types array with information provided in ’types.txt’. For each
element of Type array, you should fill the ’effects’ array. The file is structured with a pattern
repeating each nineteen lines, where first line (line without a number at the end of line)
contains attacker name and remaining eighteen lines contain defender names and multipliers
for that attacker name value. You can create a ”None”type for Pokemons that have no
secondary type. Effect multiplier of ”None”should be 1 for all elements.

2.2.4 initializeMoves
You should initialize the Moves array with information provided in ’moves.txt’. Each line of
the file is designed to fill one element of the Moves array. The space sepearated values in each
row represent name, type, category and power, correspondingly.

2.2.5 initializePokemons
You should initialize the Pokemons array with information provided in ’pokemon.txt’. Each
line of the file corresponds to one element of Pokemons array. The space sepearated values
in each row represent name, type1, type2 maxHP, attack, defense, spAtk, spDef and speed,
correspondingly. currentHP attribute should be initialized to be equal with maxHP. The
moves array should be filled randomly. You should use the rand function to randomly choose
four indices between 0 and 485, then moves corresponding to these four indices should be
assigned to the moves array. All moves of one Pokemon should be unique, so please check
for duplicates. Pokemons that do not have a secondary type have -”symbol for type2. Type2
attributes of such Pokemons should be initialized to ”None”, as described in initializeTypes
function.

2.2.6 game
Your ’game’ function should call the ’round’ function until the game ends. The game ends
when one of the players has no Pokemon with currentHP value greater than 0.

2.2.7 round
This function should mimic a round of the game. Inputs of both players will be taken from
the keyboard. Ask the first player for their move:
1 - Attack
2 - Change Pokemon

Ask the second player for their move:
1 - Attack
2 - Change Pokemon

Ask the first player for their following move:
• If they choose attack, list moves of current Pokemon and ask them to select a move.

Example:
1 - PyroBall 2 - FlameBurst
3 - PyschoCut 4 - DreamEater

Please select a move:
User should input 1, 2, 3 or 4.
• If they choose change Pokemon, list available Pokemons (the ones that have currentHP
value greater than 0) and ask them to select a Pokemon to switch with. Example:
1 - Bulbasaur 2 - Squirtle
3 - Charmander 4 - Pikachu
5 - Arceus 6 - Magikarp

Please select a Pokemon to switch:
User should input 1, 2, 3, 4, 5 or 6. Once they select, you should update currentIndex
of Player to selected index.

Ask the second player for their following move:
• If they choose attack, list moves of current Pokemon and ask them to select a move.
• If they choose change Pokemon, list available Pokemons (the ones that have currentHP
value greater than 0) and ask them to select a Pokemon to switch with. Once they
select, you should update currentIndex of Player to selected index.

After taking inputs from players, calculateDamage should be called. You need to pass all
necessary information to the function so that necessary updates can be done. If a Pokemon
faints after taking damage (if its currentHP gets below 0), currentIndex attribute of Player
should be updated to next available Pokemon index.

2.2.8 applyDamage
In this function, you should calculate the damage each Pokemon gets and update their currentHP
stats accordingly. The formula you should use for calculating damage is like this:
damage = power × attack
defense × typeEffect1 × typeEffect2 × STAB

Here, ’damage’ refers to decrease in currentHP stat of defender. Power refers to power of
move. Attack refers to attack power of attacking Pokemon if it is a physical attack and it refers
to spAtk if it is a special attack. Similarly, defense refers to defense power of defender Pokemon
if it is a physical attack and it refers to spDef if it is a special attack. TypeEffect1 refers to
TypeEffect multiplier of attack Move type to defender Pokemon type1 and TypeEffect2 refers
to TypeEffect multiplier of attack Move type to defender Pokemon type2. Finally, STAB
is Same-Type Attack Bonus, which is 1.5 if attack move type matches with one of types of
attacker Pokemon, and is 1 otherwise.

After calculating damage, Pokemons’ currentHP should be updated. Note that first damage
will be given by faster Pokemon, the one whose speed attribute is larger. If defender
faints after taking damage (if its currentHP gets below 0), it will not be able to attack, so
other Pokemon will take no damage. If a Player chose ’Change Pokemon’ option, that Player
will not be able to attack for that round, and the damage will be given to newly selected Pokemon.

3 Notes
• Initializing structs should be done by reading the files, using file operations and loops.
• If you need to use functions that were not covered in the lesson, you should first consult
me and ask for permission. Usage of uncovered functions without permission will be
considered as cheating.
• You are not allowed to share your codes with other groups. Giving this project document
to AI is also not permissible.
• If you have no prior knowledge about Pokemon or Pokemon battles, you can visit
https://play.pokemonshowdown.com and try playing a battle. It will give you some
idea about what you are trying to do, however what you are expected to do is a much
simpler version.
• Your codes will be compiled using gcc:
• gcc -Wall -Werror -Wextra *.c -o project
• ./project
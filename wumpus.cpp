/*
 *  Program 1: Wumpus, version 1 (fixed size array)
 *  System: Mac using Visual Studio Code
 *  Author: Seyfal Sultanov
 */

// Preprocessor directives
#include <stdio.h>	 // for printf
#include <stdlib.h>	 // for srand
#include <time.h>	 // for time
#include <stdbool.h> // for bool

/*
 * @brief 2D array that stores the cave map
 */
const int mapArray[20][3] =
	{
		{2, 5, 8},	  // 1
		{1, 3, 10},	  // 2
		{2, 4, 12},	  // 3
		{3, 5, 14},	  // 4
		{1, 4, 6},	  // 5
		{5, 7, 15},	  // 6
		{6, 8, 17},	  // 7
		{1, 7, 9},	  // 8
		{8, 10, 18},  // 9
		{2, 9, 11},	  // 10
		{10, 12, 19}, // 11
		{3, 11, 13},  // 12
		{12, 14, 20}, // 13
		{4, 13, 15},  // 14
		{6, 14, 16},  // 15
		{15, 17, 20}, // 16
		{18, 7, 16},  // 17
		{9, 17, 19},  // 18
		{11, 18, 20}, // 19
		{13, 16, 19}  // 20
};

/*
 * @brief 2D array that stores the cave map
 */
void displayCave()
{
	printf("       ______18______             \n"
		   "      /      |       \\           \n"
		   "     /      _9__      \\          \n"
		   "    /      /    \\      \\        \n"
		   "   /      /      \\      \\       \n"
		   "  17     8        10     19       \n"
		   "  | \\   / \\      /  \\   / |    \n"
		   "  |  \\ /   \\    /    \\ /  |    \n"
		   "  |   7     1---2     11  |       \n"
		   "  |   |    /     \\    |   |      \n"
		   "  |   6----5     3---12   |       \n"
		   "  |   |     \\   /     |   |      \n"
		   "  |   \\       4      /    |      \n"
		   "  |    \\      |     /     |      \n"
		   "  \\     15---14---13     /       \n"
		   "   \\   /            \\   /       \n"
		   "    \\ /              \\ /        \n"
		   "    16---------------20           \n"
		   "\n");
}

/*
 * @brief displays the instructions for the game
 */
void displayInstructions()
{
	printf("Hunt the Wumpus:                                             \n"
		   "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
		   "room has 3 tunnels leading to other rooms.                   \n"
		   "                                                             \n"
		   "Hazards:                                                     \n"
		   "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
		   "2. The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is \n"
		   "   asleep. He will wake up if you enter his room. When you move into the Wumpus'\n"
		   "   room, then he wakes and moves if he is in an odd-numbered room, but stays    \n"
		   "   still otherwise.  After that, if he is in your room, he snaps your neck and  \n"
		   "   you die!                                                                     \n"
		   "                                                                                \n"
		   "Moves:                                                                          \n"
		   "On each move you can do the following, where input can be upper or lower-case:  \n"
		   "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
		   "   then a room number.                                                          \n"
		   "2. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
		   "3. Enter 'C' to cheat and display current board positions.                      \n"
		   "4. Enter 'D' to display this set of instructions.                               \n"
		   "5. Enter 'P' to print the maze room layout.                                     \n"
		   "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!         \n"
		   "7. Enter 'X' to exit the game.                                                  \n"
		   "                                                                                \n"
		   "Good luck!                                                                      \n"
		   " \n\n");
} // end displayInstructions()

/*
 * @brief This function assigns the rooms to the person, wumpus, pit1, and pit2.
 *
 * @param person
 * @param wumpus
 * @param pit1
 * @param pit2
 */
void assignRooms(int *person, int *wumpus, int *pit1, int *pit2)
{
	srand(1);						   // seed the random number generator
	int randomValue = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19

	*pit1 = randomValue; // first assign the first pit to a random room

	// then assign the second pit to a random room that is not the same as the first pit
	do
	{
		randomValue = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19
		*pit2 = randomValue;		   // assign the second pit to a random room
	} while (*pit2 == *pit1);		   // if the second pit is the same as the first pit, then reassign the second pit

	// then assign the wumpus to a random room that is not the same as the first pit or the second pit
	do
	{
		randomValue = rand() % 20 + 1;				// Using +1 gives random number 1..20 rather than 0..19
		*wumpus = randomValue;						// assign the wumpus to a random room
	} while (*wumpus == *pit1 || *wumpus == *pit2); // if the wumpus is the same as the first pit or the second pit, then reassign the wumpus

	// then assign the person to a random room that is not the same as the first pit, the second pit, or the wumpus
	do
	{
		randomValue = rand() % 20 + 1;									  // Using +1 gives random number 1..20 rather than 0..19
		*person = randomValue;											  // assign the person to a random room
	} while (*person == *pit1 || *person == *pit2 || *person == *wumpus); // if the person is the same as the first pit or the second pit or the wumpus, then reassign the person
}

/*
 * @brief This function displays the current board positions
 *
 * @param person
 * @param wumpus
 * @param pit1
 * @param pit2
 */
int makeMove(int *person, int *wumpus, int pit1, int pit2, int *done)
{
	if (*person == pit1 || *person == pit2) // check if the person entered a pit
	{
		printf("Aaaaaaaaahhhhhh....   \n");
		printf("    You fall into a pit and die. \n");
		printf("\nExiting Program ...\n");
		*done = true; // set done to true to exit the game
	}
	// check if the person entered the wumpus' room, if the room is odd, wumpus goes to
	// the lowest numbered adjacent room, if the room is even wumpus stays and kills you
	else if (*person == *wumpus)
	{
		if (*person % 2 == 1) // check if the room is odd
		{
			for (int i = 0; i < 3; i++) // move the wumpus to the lowest numbered adjacent room
			{
				if (mapArray[*person - 1][i] < *wumpus) // check all adjacent rooms and find the lowest numbered room
				{
					*wumpus = mapArray[*person - 1][i]; // move the wumpus to the lowest numbered adjacent room
				}
			}

			printf("You hear a slithering sound, as the Wumpus slips away. \n" // tell the user the wumpus moved
				   "Whew, that was close! \n");
		}
		else
		{
			printf("You briefly feel a slimy tentacled arm as your neck is snapped. \n" // tell the user the wumpus killed them
				   "It is over.\n");
			printf("\nExiting Program ...\n");
			*done = true;
		}
	}
}

/*
 * @brief check all adjacent rooms and find the lowest numbered room
 *
 * @param person
 * @param room
 * @param wumpus
 * @param pit1
 * @param pit2
 * @param counter
 * @param done
 */
void checkAdjacent(int *person, int room, int *wumpus, int pit1, int pit2, int *counter, int *done)
{
	bool moveMade = false;		// bool to check if the entered room is adjacent to the current room
	for (int i = 0; i < 3; i++) // check if the entered room is adjacent to the current room
	{
		if (mapArray[*person - 1][i] == room)
		{
			*person = room;
			makeMove(person, wumpus, pit1, pit2, done);
			moveMade = true;
			*counter += 1;
		}
	}
	if (moveMade == false) // if the move is not valid, print an error message
	{
		printf("Invalid move.  Please retry. \n"); // message for invalid move
	}
}

/*
 * @brief This function displays the current board positions
 *
 * @param person
 * @param wumpus
 * @param pit1
 * @param pit2
 */
void show_room(int person, int wumpus, int pit1, int pit2)
{
	printf("You are in room %d. ", person); // tell the user which room they are in
	for (int i = 0; i < 3; i++)
	{										   // check all adjacent rooms and print a message if there is a wumpus or pit
		if (mapArray[person - 1][i] == wumpus) // check if the adjacent room is the wumpus' room
		{
			printf("You smell a stench. "); // tell the user there is a wumpus in an adjacent room
		}
		if (mapArray[person - 1][i] == pit1 || mapArray[person - 1][i] == pit2) // check if the adjacent room is a pit
		{
			printf("You feel a draft. "); // tell the user there is a pit in an adjacent room
		}
	}
	printf("\n\n");
}

//--------------------------------------------------------------------------------
int main(void)
{
	int person = 0;	   // person's current room
	int wumpus = 0;	   // wumpus' current room
	int pit1 = 0;	   // pit 1's current room
	int pit2 = 0;	   // pit 2's current room
	int move = 0;	   // the room to move to
	char optionInput;  // the option the user enters
	int room;		   // the room the user enters
	bool done = false; // flag to indicate when game is over
	int counter = 1;   // counter to keep track of the number of moves the user has made

	// randomly assign the person and hazards to the cave
	assignRooms(&person, &wumpus, &pit1, &pit2);

	// main game loop
	while (!done)
	{

		show_room(person, wumpus, pit1, pit2);							  // display the room the player is in
		printf("%d. Enter your move (or 'D' for directions): ", counter); // prompt for user to enter their move
		scanf(" %c", &optionInput);										  // read in the option
		optionInput = tolower(optionInput);								  // convert to lower case

		switch (optionInput)
		{

		case 'd':
			printf("\n");
			displayCave();
			displayInstructions();
			break;

		case 'm':
			scanf("%d", &room); // read in the room
			checkAdjacent(&person, room, &wumpus, pit1, pit2, &counter, &done);
			break;

		case 'x':
			// Message that prints at the end of the program
			printf("\nExiting Program ...\n");
			// Set the done flag to true to exit the game loop
			done = true;
			break;

		case 'c':
			printf("Cheating! Game elements are in the following rooms: \n"
				   "Player Wumpus Pit1 Pit2  \n"
				   "%4d %7d %5d %5d \n\n",
				   person, wumpus, pit1, pit2);
			break;

		case 'p':
			printf("\n");
			displayCave();
			break;

		case 'r':
			// Prompt for user when they choose to reset
			printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: \n");
			scanf("%d %d %d %d", &person, &wumpus, &pit1, &pit2);
			printf("\n");
			break;

		case 'g':
			// Prompt for user when they choose to quit
			printf("Enter room (1..20) you think Wumpus is in: ");
			scanf("%d", &move);
			if (move == wumpus)
			{
				printf("You won!\n");
				printf("\nExiting Program ...\n");
				// Set the done flag to true to exit the game loop
				done = true;
			}
			else
			{
				printf("You lost.\n");
				printf("\nExiting Program ...\n");
				// Set the done flag to true to exit the game loop
				done = true;
			}
			break;
		}
	}
	// return 0 to indicate successful completion
	return 0;
}

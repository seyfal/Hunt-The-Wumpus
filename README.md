Hunt the Wumpus
This is a text-based adventure game called "Hunt the Wumpus". The Wumpus lives in a completely dark cave of 20 rooms. Each room has 3 tunnels leading to other rooms.

Installation
Clone the repository or download the ZIP file and extract the files.

sh
Copy code
git clone https://github.com/example/hunt-the-wumpus.git
Usage
Run the program from the command line or terminal.

sh
Copy code
cd hunt-the-wumpus
./wumpus
Rules of the Game
The game is played in a dark cave of 20 rooms.
There are two rooms that have bottomless pits in them. If the player enters one of these rooms, they fall and die.
The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is asleep. He will wake up if the player enters his room. When the player moves into the Wumpus' room, then he wakes and moves if he is in an odd-numbered room, but stays still otherwise. After that, if he is in the player's room, he snaps the player's neck and the player dies!
On each move, the player can do the following:
Move into an adjacent room. To move, enter 'M' followed by a space and then a room number.
Enter 'R' to reset the person and hazard locations, useful for testing.
Enter 'C' to cheat and display current board positions.
Enter 'D' to display the set of instructions.
Enter 'P' to print the maze room layout.
Enter 'G' to guess which room the Wumpus is in, to win or lose the game!
Enter 'X' to exit the game.
Contributing
Bug reports and pull requests are welcome on GitHub at https://github.com/example/hunt-the-wumpus.

License
The code is available as open source under the terms of the MIT License.

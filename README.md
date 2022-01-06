# Dragon-Terminal-Game
This is a little game you can run on the terminal. It's got ASCII graphics and cool dragons!


How to Run:
You'll need to compile this in the terminal. I only know how to use the Linux GCC terminal so I can give those commands.
Have all the files in the same directory then run this command: gcc main.c -o DragonGame
This will create an executable called 'DragonGame' in the current directory. Run 'DragonGame' and you can start the game!

To run this on Windows you need to boot up your favorite C++ IDE or Visual Studio.
Create a windows C++ terminal project then add all the files to that project.
Build the project then run the debugger to run the game in the IDE's terminal

How to Play:
When the game starts it will ask for your name. 
After giving it your name the main menu will appear:
  
|    What would you like to do?	                                      |
|       1. Search for an egg                                          |
|       2. Try to hatch egg                                           |
|       3. Display all dragons and eggs                               |
|       4. Attack!                                                    |
|       5. Quit                                                       |

The first menu option allows you to search for eggs of various rarity. You need eggs to hatch into dragons and you need dragons to fight other dragons.

The second option lets you hatch eggs you have found. You can't hatch eggs if you don't have any eggs.

The third option shows all the eggs and dragons you have and their status.

The fourth option lets you battle an enemy dragon. If your dragon defeats the enemy dragon then your dragon will grow bigger.
The bigger your dragon, the more likely you are to win.
  
The fifth and final option lets you quit the game and return to the terminal.

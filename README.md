# Emulator8080

Description: This Repository is focused on building an Emulator for the 8080 processor with a group of 4 fellow students over the course of 3 months. Our eventual goal is to run the Space invaders game on it. As a side effect of the above goal, I hope to further my knowledge of the C++ and C programming languages as well as Assembly Language and the low level programming that is involved with operating computer systems.

## Project outline and order of goals:

The following will be the basic order in which our team tackles building our project:

- Set up environment and ensure team members can successfully compile code with requisite basic libraries
- Build a disassembler for the Space Invaders ROM.
    - Based on 8080 opcode
    - Document disassembled code for human readability
- Build an Emulator File for the 8080 Processor.
    - Write emulator shell
    - Implement code for basic logic groups
    - Implement instructions required for 8080 assembly code
    - Debug, debug, debug
- Build an emulator file for the hardware of the arcade processor.
    - Visual interrupts
    - Processor timing
    - Audio outputs
    - Keyboard inputs
    - Debug
- Build a file for interpreting i/o from our computers
    - Keyboard inputs
    - Audio outputs
    - Platform-specific instructions/code
    - Debug
- Build a GUI to interact with the Emulator
    - Start game option
    - Exit game option
- (Optional) Add additional games for emulation
    - Implement additional assembly instructions
    - Add game-selection for GUI
    - Debug and ensure that hardware i/o is consistent
- Play the Game

# INSTALLATION GUIDE
Intel8080 Emulator For Space Invaders
Installation and Instructions

William Franklin, Aidan MacKenzie, Daniel Murray, Sami Syed, James Tauzin

The Emulator is written to be compatible with Windows, Mac, and Linux environments. Windows is the easiest environment to use, as the .dll files can be included in the project folders. Windows also allows for the use of .exe files, making it the easiest Operating System to use for playing our emulator.
Windows 
To install and run the game on windows, either clone or download the zip package from github.

Next navigate to the files location, unzip if needed, and open the project folder.

Double click the space_invaders.exe and have fun! See appendix A for controls

To quit the game, simply click the X in the top right corner of the game window.

## Linux

To run and play the game, clone the repository as above, navigate to the repository’s root and type ./space_invaders_linux into the terminal. This executable is statically compiled, so as long as it is run from the correct file location it should run. A note on this version of the game: the sounds are currently disabled, but it is otherwise playable.

## Mac
Mac is not the preferred operating system for running our emulator. It is possible and runs very well, but requires the installation of the SDL2 and SDL2_mixer libraries and is, generally, unpleasant to compile. If you have homebrew installed on your computer, you can use the commands “brew install sdl2” and “brew install sdl2_mixer” to install those libraries in your computer’s /opt/homebrew/Cellar/ folder, with corresponding binaries installed in the /Library/Developer/CommandLineTools/usr/bin folder. Once you have installed SDL2 and SDL2_mixer libraries and confirmed that their locations match those listed above, you must make several small tweaks to some of the header files for the project. In renderer.h and inputHandler.h, the line “#include <SDL2.h>” must be changed to:
#include “../libs/SDL2-2.30.0/include/SDL.h”
In emulator_shell.h, the line “#include <SDL2_mixer.h>” must be changed to:
#include “../libs/SDL2-2.30.0/include/SDL2_mixer.h”
Once those lines have been changed, run the following command from the folder containing the other project folders (if pulled from our github, that will be the emulator8080 folder.):
g++ -o game ./renderer8080/renderer.cpp ./emulator/main.cpp ./emulator/emulator_shell.cpp ./emulator/disassembler.cpp ./inputoutput/inputHandler.cpp -I/Library/Developer/CommandLineTools/usr/bin/sdl2 -L/opt/homebrew/Cellar/sdl2_mixer/2.8.0/lib -L/opt/homebrew/Cellar/sdl2/2.30.0/lib -lSDL2 -lsdl2main -lSDL2_mixer -std=c++17
If the game does not compile correctly, ensure that your SDL2 and SDL2_mixer libraries are installed in the locations mentioned above. The above command requires that they be there. From the folder that you have compiled Space Invaders, run the command “./game” to play Space Invaders to your heart’s content!

Game Instructions
From the folder where you’ve installed the game, open the game. Depending on your operating system of choice, you may need to do this from the command line. Once the game has started up, it will open with the main menu, as seen below in figure 1. After all the text on the main menu has appeared, the screen will progress to a demo showing what the game looks like when played. To exit the game at any time, simply close the window by clicking on the “x” at the top. 


Figure 1, Space Invaders Menu
![image](https://github.com/saminoorsyed/8080Emulator/assets/91293085/1c316efe-0552-466e-b2e4-1e7b9af83e14)


Because this game is one that was originally for use in arcades, you must insert coins to play. Press the “c” key to insert a coin. Once you have inserted a coin, the screen will appear as it does in figure 2. From this screen, press the “h” key to begin a one-player game of Space Invaders. The “g” key for a two-player game will not work if there is only one credit. Available credits are displayed at all times in the lower right corner of the screen.


Figure 2, One Player Start Screen
![image](https://github.com/saminoorsyed/8080Emulator/assets/91293085/ca275cc0-bf95-4014-b571-726a9da3668b)


To play in two-player mode, press “c” again to insert another coin. The game will take up to 99 credits at a time - inserting more credits (pressing “c”) after there are 99 credits will do nothing, and credits passed 99 are not counted. From the screen displayed in figure 3, press the “h” key to play in single player mode, which will consume one credit, or press the “g” key to play in two-player mode, which will consume two credits.


Figure 3, Two Player Start Screen
![image](https://github.com/saminoorsyed/8080Emulator/assets/91293085/1c78f5da-a5e0-4c39-871a-9e0af6c150b7)


Once a game has been started, as seen in figure 4 below, the screen will display the invaders at the top of the screen, the player’s “tank” at the bottom of the screen, and several bunkers behind which the player can hide from attacks. The player’s available lives are displayed in the lower left corner of the screen.


Figure 4, Playing Game
![image](https://github.com/saminoorsyed/8080Emulator/assets/91293085/b1f3b4e2-8449-4c20-9864-2ea62ba89cd5)


In a one-player game, press “j” and “l” to move left and right, respectively, and “i” to fire at the Invaders. The game ends when you have lost all your lives. In a two-player game, players take turns. Player one will use the same controls as in a one-player game and player two will use “s” and “f” to move left and right, respectively, and “e” to fire at the Invaders. The game ends when both players have lost all their lives. The winner is the player with the highest score, as displayed at the top of the screen in figure 4.




Appendix A: List of Controls

Action
Key
Insert Coin
C
P1 Left
J
P1 Right
L
P1 Fire
I
P2 Left
S
P2 Right
F
P2 Fire
E
P1 Game Start
H
P2 Game Start
G




References
Simple DirectMedia Layer. Available: https://www.libsdl.org/ [Accessed: Jan-Mar, 2024].

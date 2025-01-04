# Space Invaders Game

## Overview
This is a console-based Space Invaders game written in C. The game features two spaceships, a player-controlled spaceship and an enemy spaceship, battling each other by firing bullets. The goal of the game is to reduce the opponent's life points to zero while avoiding their attacks.

## Features
- **Player and Enemy Spaceships**: Controlled by the player and the program respectively.
- **Dynamic Gameplay**: Movement and firing mechanisms for both the player and the enemy.
- **Collision Detection**: Bullets hitting the opponent reduce their life points.
- **Game Status**: Displays remaining life points for both player and enemy.
- **Randomized Enemy Movement**: The enemy spaceship moves to random positions.
- **Help Menu**: Provides game instructions.
- **Sound Effects**: Includes sound for firing bullets.

## Controls
- `A`: Move left
- `D`: Move right
- `Spacebar`: Fire bullets
- `H`: Display help menu
- `Q`: Quit the game

## How to Run
### Prerequisites
- Windows operating system
- GCC compiler (MinGW recommended)

### Steps
1. Clone or download the project to your system.
2. Open a terminal in the project directory.
3. Compile the code using:
   ```bash
   gcc space_invaders.c -o space_invaders.exe -lwinmm
   ```
4. Run the executable:
   ```bash
   space_invaders.exe
   ```

## File Structure
- **space_invaders.c**: Main source code for the game.
- **instructions.txt**: Contains instructions displayed in the help menu.
- **shoot.wav**: Sound effect for firing bullets.

## Code Highlights
### Sound Integration
Sound is implemented using the Windows API:
```c
#include <windows.h>
PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
```

### Game Logic
- The player's and enemy's movements and actions are controlled within a main game loop.
- Randomized enemy movement is achieved with:
```c
int givenXposition[5] = {5, 10, 15, 20, 25};
int r = rand() % 5;
enemy->x = givenXposition[r];
```

## Known Issues
- Ensure `shoot.wav` is in the correct directory or update its path in the code.
- The game runs only on Windows due to its reliance on Windows API for sound.

## Future Improvements
- Enhance graphics using a library like SDL or OpenGL.
- Add more gameplay features like levels, power-ups, or multiple enemies.
- Port the game to a cross-platform environment.

## Credits
- Designed and implemented by Nilabha.
- Inspired by the classic arcade game "Space Invaders."

## License
This project is licensed under the MIT License. See the LICENSE file for details.


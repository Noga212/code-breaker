# code-breaker
This will be a computer game version of the master-mind game.
The computer generates a code, a combination of colors. The length of the combination and the number of colors can be changed (in future versions) and will be known to the player.
The player then guesses the code, and gets hints about the guess - white for a color that exists in the code but not in the right place, and black for a color that is in its right place.
The player needs to discover the code in the least amount of guesses!

# install
## 1. Build the solution
1. Download/clone the repo.
2. Download from https://github.com/wxWidgets/wxWidgets/releases/tag/v3.2.6 the headers and libs for vc14x: wxMSW-3.2.6_vc14x_ReleaseDLL, wxMSW-3.2.6_vc14x_Dev, wxWidgets-3.2.6-headers
3. In the folder vxwidgets - extract wxwidgets files.
4. Make sure both dev and releaseDLL are presented in the vc14x_dll folder
5. Compile in release x32 mode.
## 2. Install with installer
1. Download the installer,
2. Follow the instructions.

# Roadmap
# version 0.1
- Fixed length of combination and number of colors: combination length 4, number of colors 6.
- Basic GUI. 

## Version 0.2

- The number of colors can be changed to player's choice. 

- Improved GUI.

## Version 0.3

- The length of the combination can be changed to player's choice. 

## Version 0.4

- The player can choose if there can be in the code double colors or not. 

- Improved GUI - home page.

## Version 0.5

- Save last scores - number of tries. 

- Improved GUI.

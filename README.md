# ShallowOrange
This is a basic chess engine (the name is a reference to Deep Blue).

To use, open in Docker with the existing Dockerfile\
Create a new build folder with `mkdir build`\
Enter the folder with `cd build` and type `cmake ..`\
Type `make main` and then `./main`.

A config file can be found in the entry folder.\
If the config file is not used, the depth will be 3, and the board will be shown without coordinates from the pov of the color you are playing. The randomness will be based on the difficulty.\
The config file can be used to choose a depth, randomness, color, and visual options.

Best chess.com bot beaten: Emir (1000)

To be implemented:\
-Opening book\
-More sophisticated board evaluation\
-Optimized calculations

Note: En passant is forced

# Computer Graphics Competition 2021
# Raytracing 

**HOW TO COMPILE:**

**Prerequisites:**

- SFML library 
  -> use flags when compiling without provided Makefile: -lsfml-graphics -lsfml-window -lsfml-system 
- OpenMP very much recommended -> flags:                 -fopenmp

**Windows 10**

1. Install Mingw compiler

1.1 follow mingw install instructions on https://code.visualstudio.com/docs/cpp/config-mingw
1.2 download mingw installer: https://sourceforge.net/projects/mingw-w64/
1.3 don't forget to switch to x86_64 architechture


**Linux (Ubuntu):**

1. Install SFML:
sudo apt-get install libsfml-dev

1.1 Install gnu make, if necessary:
sudo apt-get install build-essential

2. Descend into src/

3. Build the executable:

The Makefile already contains the compile flags mentioned above.

make [-jX] 
where X is the amount of jobs, for example equal to your CPU core count.

4. Run executable:

./main

5. Remove SFML:
sudo apt-get remove libsfml-dev



**CONTROLS:**

WASDQE     - forward/backward/left/right/up/down

arrow keys - rotation around X and Z axis (look up/down/left/right)

Spacebar   - start/pause solar system simulation, if using scene "../Scenes/myScenes/7solarSystem.json".


**MODIFY YOURSELF**:
1. Change the scene selection:

Modify the global SCENE in main.cc: "../Scenes/yourFolder/yourScene.json".

2. Modify a scene:

Change the .json files by yourself. You can look at the existing scenes for inspiration.















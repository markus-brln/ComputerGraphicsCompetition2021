# Computer Graphics Competition 2021 - Raytracing 

This project builds upon the code provided in the Computer Graphics course
at the University of Groningen, which can mainly be found in src/raytracerandfriends.
My contribution is introducing proper perspective to the raytracer, 
allowing the camera to move, displaying raytraced images to a window
and building scenes such as a "simulation" of the solar system.
You can find a more detailed description of the process under
documentationProject/doc.txt.

1. Item 1
1. Item 2
1. Item 3
   1. Item 3a
   1. Item 3b

## HOW TO COMPILE:

### Windows 10

1. Install Mingw 8.1.0 compiler if you don't have a compiler yet

1.1 follow Mingw install instructions on https://code.visualstudio.com/docs/cpp/config-mingw
    [download Mingw installer: https://sourceforge.net/projects/mingw-w64/ ]
1.3 don't forget to switch to x86_64 architechture
1.4 don't forget to add Mingw's bin folder to PATH, as described in 1.1



2. Compile the program

in scr/ execute:

```g++ -o main.exe -std=c++2a -I. -L lib/windows  *.cc controller/*.cc utils/*.cc raytracerandfriends/*.cc  raytracerandfriends/lode/*.cc raytracerandfriends/shapes/*.cc  -lm -lsfml-graphics -lsfml-window -lsfml-system -fopenmp```

### Linux (Ubuntu):

#### 
```g++ -o main -std=c++2a -I. -L lib/linux  *.cc controller/*.cc utils/*.cc raytracerandfriends/*.cc  raytracerandfriends/lode/*.cc raytracerandfriends/shapes/*.cc  -lm -lsfml-graphics -lsfml-window -lsfml-system -fopenmp```


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


## Credits

* SFML library used for keyboard 












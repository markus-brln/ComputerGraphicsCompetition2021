# Computer Graphics Competition 2021 - Raytracing 

This project builds upon the code provided in the Computer Graphics course
at the University of Groningen, which can mainly be found in src/raytracerandfriends.
My contribution is introducing proper perspective to the raytracer, 
allowing the camera to move, displaying raytraced images to a window
and building scenes such as a "simulation" of the solar system.  
You can find a more detailed description of the process in
documentationProject/doc.txt.

Videos of different stages of the project can be found in this playlist:  
https://www.youtube.com/watch?v=6rHRHlJg37s&list=PL7uXyOTDLR1gYDpTEuKeJiKMgc_PqlTov&index=1


![bshadowsHighRes](https://user-images.githubusercontent.com/56026631/112717810-2b512c00-8eef-11eb-8249-38791959a4d2.png)
Doesn't Jupiter look majestic? (At this window size the program does ***not*** run smoothly. Modify SIZE in main.cc to adapt 
it to your wishes.)


## Try out yourself:

### Windows 10

#### Use the executable that I provided

If you have trouble compiling (see the following steps) or just quickly want to try out 
the program, simply run ```main.exe``` in the src directory.

#### Compile yourself

1. Install Mingw 8.1.0 compiler if you don't have a compiler yet.

   1.1 follow Mingw install instructions on https://code.visualstudio.com/docs/cpp/config-mingw  
      [download Mingw installer: https://sourceforge.net/projects/mingw-w64/ ]  
   1.2 don't forget to switch to x86_64 architechture  
   1.3 don't forget to add Mingw's bin folder to PATH, as described in 1.1  


2. Compile the program

   in scr/ execute:  

   ```g++ -o main.exe -std=c++2a -I. -L lib/windows  *.cc controller/*.cc utils/*.cc raytracerandfriends/*.cc  raytracerandfriends/lode/*.cc raytracerandfriends/shapes/*.cc  -lm -lsfml-graphics -lsfml-window -lsfml-system -fopenmp```
   
   Compiler flag explanation:    
   - ```-std=c++2a```     Specify C++ standard to use
   - ```-L lib/windows``` Search the library named library when linking.
   - ```-lsfml-graphics -lsfml-window -lsfml-system``` Flags that LSFM library requires, see https://www.sfml-dev.org/tutorials/2.5/start-linux.php
   - ```-fopenmp```       Multithreading with OpenMP, see ```#pragma``` directive in Scene::renderToSFImage()


### Linux:

#### Use the executable that I provided

If you have trouble compiling (see the following steps) or just quickly want to try out 
the program, simply run ```./main``` in the src directory.

#### Compile yourself

I only have experience with Ubuntu, here are some ways of how you can compile 
the project yourself that may or may not apply to other distros.

**1. Compile the program using g++**

   in scr/ execute (note the lib/linux instead of windows):  

   ```g++ -o main -std=c++2a -I. -L lib/linux  *.cc controller/*.cc utils/*.cc raytracerandfriends/*.cc  raytracerandfriends/lode/*.cc raytracerandfriends/shapes/*.cc  -lm -lsfml-graphics -lsfml-window -lsfml-system -fopenmp```

   I tried using OpenACC (requires Linux, Nvidia graphics card and CUDA...), but I was not  
   successful yet. Suggestions on how to parallelize the nested loop in Scene::renderToSFImage()  
   would be appreciated :)  
   ```nvc++ -o main -std=c++2a -I. -L lib/linux  *.cc controller/*.cc utils/*.cc raytracerandfriends/*.cc  raytracerandfriends/lode/*.cc raytracerandfriends/shapes/*.cc  -lm -lsfml-graphics -lsfml-window -lsfml-system -acc -Minfo=accel```

**2. What I did when developing**

   1. Install SFML for your own projects
   ```sudo apt-get install libsfml-dev```

   1.1 Install gnu make, if necessary:
   ```sudo apt-get install build-essential```

   2. Descend into src/

   3. Build the executable:

   The Makefile already contains the compile flags mentioned above. It is written such that only modified sources are recompiled.

   make [-jX] 
   where X is the amount of jobs, for example equal to your CPU core count.

   4. Run executable:

   ./main

   5. Remove SFML:
   sudo apt-get remove libsfml-dev



## Controls:

WASDQE            - forward/backward/left/right/up/down

arrow keys        - rotation around X and Z axis (look up/down/left/right)

Numpad plus/minus - zoom in/out

Spacebar          - start/pause solar system simulation, if using scene "../Scenes/myScenes/9solarSystem.json".
                  (to be honest, I kind of hardcoded that into Controller::run() :) )


## Modify Scene files:

Change the .json files by yourself. You can look at the existing scenes for inspiration.


## Credits

- SFML library used for keyboard input and display output, which is as easy as pygame https://www.sfml-dev.org/
- Teaching Assistant Boris that helped me with compiling on Windows 10
- Jurjen Bokma from the C++ Course for the Makefile that probably saved me like an hour in compile time (and will continue to do so in my future C++ projects...)
- planet textures (including our moon and pluto): http://planetpixelemporium.com/planets.html
- skybox texture https://forums.planetaryannihilation.com/threads/milky-way-skybox.72682/



## Extra: how to use a library like SFML

- copy content of include directory (SFML) to src (in this case it's the same for Linux and Windows)  
- from bin/ copy files (dynamic link libraries) to src  
- copy lib to lib/windows or lib/linux  
![librarySetup](https://user-images.githubusercontent.com/56026631/112718740-39a24680-8ef5-11eb-91f4-1e59d65bbe47.png)







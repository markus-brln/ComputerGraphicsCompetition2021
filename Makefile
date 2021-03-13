LIBS  = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -fopenmp

all:
	@echo "** Building the game"
	g++ -c -fopenmp src/main.cc -o obj/main.o
	g++ -c -fopenmp src/raytracerandfriends/lode/lodepng.cc -o obj/lodepng.o
	g++ -c -fopenmp src/raytracerandfriends/shapes/quad.cc -o obj/quad.o
	g++ -c -fopenmp src/raytracerandfriends/shapes/solvers.cc -o obj/solvers.o
	g++ -c -fopenmp src/raytracerandfriends/shapes/sphere.cc -o obj/sphere.o
	g++ -c -fopenmp src/raytracerandfriends/image.cc -o obj/image.o
	g++ -c -fopenmp src/raytracerandfriends/objloader.cc -o obj/objloader.o
	g++ -c -fopenmp src/raytracerandfriends/raytracer.cc -o obj/raytracer.o
	g++ -c -fopenmp src/raytracerandfriends/scene.cc -o obj/scene.o
	g++ -c -fopenmp src/raytracerandfriends/triple.cc -o obj/triple.o
	
	# building the final main executable from object files
	g++ -o main obj/main.o obj/lodepng.o obj/quad.o obj/solvers.o obj/sphere.o obj/image.o obj/objloader.o obj/raytracer.o obj/scene.o obj/triple.o $(LIBS) -fopenmp

clean:
	@echo "** Removing object files and executable..."
	rm -f main

install:
	@echo '** Installing...'
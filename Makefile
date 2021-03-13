LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:
	@echo "** Building the game"
	g++ -c "main.cc" -o main.o
	#g++ -c "State.cpp" -o State.o
	#g++ -c "PlayState.cpp" -o PlayState.o
	#g++ -c "Game.cpp" -o Game.o
	#g++ -c "Object.hpp" -o Object.o
	#g++ -c "Player.hpp" -o Player.o
	#g++ -o thegame Game.o State.o PlayState.o Object.o Player.o $(LIBS)
	g++ -o main main.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f thegame

install:
	@echo '** Installing...'
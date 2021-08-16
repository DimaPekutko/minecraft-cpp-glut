all: compile run
compile:
	g++ -o trashsquare.out -I ./src *.cpp src/*.cpp  -lglut -lGL -lGLU -lGLEW

run:
	./trashsquare.out
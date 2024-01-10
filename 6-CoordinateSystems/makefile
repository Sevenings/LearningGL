# C++ Makefile
MAIN=main.cpp
PROJECT_NAME=CoordsSystems

INCLUDE_DIR=include
SOURCE_INCLUDE=src/glad.c
FLAGS=-lGL -lglfw

build: $(MAIN)
	g++ -o $(PROJECT_NAME) $(MAIN) $(SOURCE_INCLUDE) -I$(INCLUDE_DIR) $(FLAGS) 

run: $(PROJECT_NAME)
	./$(PROJECT_NAME)



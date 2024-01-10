MAIN=helloTriangle.cpp
PROJECT_NAME=HelloSquare
INCLUDE_DIR=include
FLAGS=-lGL -lglfw
SOURCE_INCLUDE=src/glad.c

build:$(MAIN)
	g++ -o $(PROJECT_NAME) $(MAIN) $(SOURCE_INCLUDE) -I$(INCLUDE_DIR) $(FLAGS) 

run:$(PROJECT_NAME)
	./$(PROJECT_NAME)

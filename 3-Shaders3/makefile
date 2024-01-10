MAIN=shaders.cpp
PROJECT_NAME=Shader
INCLUDE_DIR=include
FLAGS=-lGL -lglfw
SOURCE_INCLUDE=src/glad.c

build:
	g++ -o $(PROJECT_NAME) $(MAIN) $(SOURCE_INCLUDE) -I$(INCLUDE_DIR) $(FLAGS) 

run:$(PROJECT_NAME)
	./$(PROJECT_NAME)

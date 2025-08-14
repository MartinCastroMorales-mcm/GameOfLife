CC = g++
FLAGS = -Wall -Wextra -g
build = build
src = src
lib = -lraylib
include = -I include/GameOfLifeClass -I include/Components -I include/



main: main.o
	$(CC) $(FLAGS) $(include) $(build)/main.o -o $(build)/main $(lib)

main.o: build
	$(CC) $(FLAGS) $(include) -c $(src)/main.cpp -o $(build)/main.o 
build: 
	mkdir build
test:
	$(CC) $(FLAGS) $(include) $(src)/test.cpp -o $(build)/test


#GameOfLife.o:
#$(CC) $(FLAGS) -I $(include) -c $(src)/GameOfLife.cpp -o $(build)/GameOfLife.o

clean:
	rm -rf $(build)/*
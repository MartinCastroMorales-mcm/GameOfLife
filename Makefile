CC = g++
FLAGS = -Wall -Wextra -g
build = build
src = src
lib = -lraylib
include = -I include/GameOfLifeClass -I include/Components -I include/
EMCC = em++
EMFLAGS = -O2 -DPLATFORM_WEB -s USE_GLFW=3 -s ASYNCIFY \
          -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 \
          -s FORCE_FILESYSTEM=1
RAYLIB_WEB_A = libraylib.web.a



main: main.o
	$(CC) $(FLAGS) $(include) $(build)/main.o -o $(build)/main $(lib)

web: 
	$(EMCC) $(EMFLAGS) $(include) \
		$(src)/main.cpp $(RAYLIB_WEB_A) \
		$(RAYLIB_INCLUDE) \
		-o $(build)/index.html

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
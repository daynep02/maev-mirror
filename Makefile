INCLUDE_PYTHON = -lpython3.10 -I/usr/include/python3.10
INCLUDE_OPENGL = -lGL -lglfw
WIN_INCLUDE_OPENGL = -I/mingw64/include -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32

.PHONY: all clean

all:
	g++ -o engine *.cpp $(INCLUDE_PYTHON) $(INCLUDE_OPENGL)

win_all:
	g++ -o engine *.cpp $(WIN_INCLUDE_OPENGL)

run:
	./engine

clean:
	rm -f engine 
	rm -rf *.o

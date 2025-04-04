INCLUDE_OPENGL = -lGL -lglfw
WIN_INCLUDE_OPENGL = -I/mingw64/include -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32

.PHONY: all clean

helloworld: helloworld.cpp
	g++ -o helloworld helloworld.cpp $(INCLUDE_OPENGL)

win_helloworld:
	g++ -o helloworld helloworld.cpp $(WIN_INCLUDE_OPENGL)

all: helloworld

clean:
	rm -f helloworld *.o

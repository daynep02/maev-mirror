INCLUDE_OPENGL = -lGL -lglfw

.PHONY: all clean

helloworld: helloworld.cpp
	g++ -o helloworld helloworld.cpp $(INCLUDE_OPENGL)

all: helloworld

clean:
	rm -f helloworld *.o

INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12

INCLUDE_SFML = -Wl,-rpath=./sfml/lib -I./sfml/include/ -L./sfml/lib -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

.PHONY: all clean

all: engine.cpp

engine: engine.cpp
	g++ -o engine *.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)
		
run:
	./engine

clean:
	rm -f engine 
	rm -rf *.o

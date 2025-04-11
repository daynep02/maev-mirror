INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12
INCLUDE_PYTHON_LAB = -lpython3.10 -I/usr/include/python3.10

INCLUDE_SFML = -Wl,-rpath=../sfml/lib -I../sfml/include/ -L../sfml/lib -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

.PHONY: all clean

all: engine

engine: ../src/engine.cpp
	g++ -o engine ../src/*.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)
		
lab: ../src/engine.cpp
	g++ -o engine ../src/*.cpp $(INCLUDE_PYTHON_LAB) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

run:
	./engine

clean:
	rm -f engine 
	rm -rf *.o

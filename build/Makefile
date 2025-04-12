foo := $${PWD%/*}
previous_dir := $(shell echo $(value foo))

INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12
INCLUDE_PYTHON_LAB = -lpython3.10 -I/usr/include/python3.10

INCLUDE_SFML = -Wl,-rpath=$(previous_dir)/sfml/lib -I$(previous_dir)/sfml/include/ -L$(previous_dir)/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

.PHONY: all clean

all: engine

engine: $(previous_dir)/src/engine.cpp
	g++ -o engine $(previous_dir)/src/*.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

debug: $(previous_dir)/src/engine.cpp
	g++ -g -o engine $(previous_dir)/src/*.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

lab: $(previous_dir)/src/engine.cpp
	g++ -o engine $(previous_dir)/src/*.cpp $(INCLUDE_PYTHON_LAB) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

run:
	./engine game.py
#	 ./engine $(previous_dir)/games/game.py

clean:
	rm -f engine 
	rm -rf *.o

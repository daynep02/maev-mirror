foo := $${PWD%/*}
previous_dir = $(shell echo $(value foo))

ifeq ($(ENV),lab)
	INCLUDE_PYTHON = -lpython3.10 -I/usr/include/python3.10
else
	INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12
endif

# INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12
# INCLUDE_PYTHON_LAB = -lpython3.10 -I/usr/include/python3.10

INCLUDE_SFML = -Wl,-rpath=$(previous_dir)/sfml/lib -I$(previous_dir)/sfml/include/ -L$(previous_dir)/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

.PHONY: all clean

all: engine

engine: $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o
	g++ -g -o engine $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

lab: $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o
	g++ -g -o engine $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o $(INCLUDE_PYTHON_LAB) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

object_handler.o: $(previous_dir)/src/object_handler.cpp
	g++ -g -o object_handler.o -c $(previous_dir)/src/object_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

keyboard.o: $(previous_dir)/src/keyboard.cpp
	g++ -g -o keyboard.o -c $(previous_dir)/src/keyboard.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

box_collider.o: $(previous_dir)/src/box_collider.cpp
	g++ -g -o box_collider.o -c $(previous_dir)/src/box_collider.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

box_collider_handler.o: $(previous_dir)/src/box_collider_handler.cpp
	g++ -g -o box_collider_handler.o -c $(previous_dir)/src/box_collider_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

rigid_body.o: $(previous_dir)/src/rigid_body.cpp
	g++ -g -o rigid_body.o -c $(previous_dir)/src/rigid_body.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

rigid_body_handler.o: $(previous_dir)/src/rigid_body_handler.cpp
	g++ -g -o rigid_body_handler.o -c $(previous_dir)/src/rigid_body_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

run: all
	./engine $(previous_dir)/games game.py

clean:
	rm -f engine 
	rm -rf *.o

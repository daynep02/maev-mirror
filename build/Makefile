foo := $${PWD%/*}
previous_dir = $(shell echo $(value foo))

ifeq ($(ENV),lab)
	INCLUDE_PYTHON = -lpython3.10 -I/usr/include/python3.10
else
	INCLUDE_PYTHON = -lpython3.12 -I/usr/include/python3.12
endif

INCLUDE_FLAC = -Wl,-rpath=$(previous_dir)/FLAC/lib -I$(previous_dir)/FLAC/include/ -L$(previous_dir)/FLAC/lib -lFLAC
INCLUDE_SFML = -Wl,-rpath=$(previous_dir)/sfml/lib -I$(previous_dir)/sfml/include/ -L$(previous_dir)/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network 

FLAGS = -Wall -Wpedantic -Wextra

.PHONY: all clean

all: engine

engine: $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o vector.o audio_handler.o camera_handler.o text_handler.o callback_handler.o window_handler.o collision_layers.o
	g++ -g -o engine $(previous_dir)/src/engine.cpp object_handler.o keyboard.o box_collider.o box_collider_handler.o rigid_body.o rigid_body_handler.o vector.o audio_handler.o camera_handler.o text_handler.o callback_handler.o window_handler.o collision_layers.o $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_FLAC)

object_handler.o: $(previous_dir)/src/object_handler.cpp
	g++ -g -o object_handler.o -c $(previous_dir)/src/object_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

keyboard.o: $(previous_dir)/src/keyboard.cpp
	g++ -g -o keyboard.o -c $(previous_dir)/src/keyboard.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

box_collider.o: $(previous_dir)/src/box_collider.cpp
	g++ -g -o box_collider.o -c $(previous_dir)/src/box_collider.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

vector.o: $(previous_dir)/src/vector.cpp
	g++ -o vector.o -c $(previous_dir)/src/vector.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

box_collider_handler.o: $(previous_dir)/src/box_collider_handler.cpp
	g++ -g -o box_collider_handler.o -c $(previous_dir)/src/box_collider_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

rigid_body.o: $(previous_dir)/src/rigid_body.cpp
	g++ -g -o rigid_body.o -c $(previous_dir)/src/rigid_body.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

rigid_body_handler.o: $(previous_dir)/src/rigid_body_handler.cpp
	g++ -g -o rigid_body_handler.o -c $(previous_dir)/src/rigid_body_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

audio_handler.o: $(previous_dir)/src/audio_handler.cpp
	g++ -g -o audio_handler.o -c $(previous_dir)/src/audio_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_FLAC)

camera_handler.o: $(previous_dir)/src/camera_handler.cpp
	g++ -g -o camera_handler.o -c $(previous_dir)/src/camera_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_FLAC)

text_handler.o: $(previous_dir)/src/text_handler.cpp
	g++ -g -o text_handler.o -c $(previous_dir)/src/text_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

callback_handler.o: $(previous_dir)/src/callback_handler.cpp
	g++ -g -o callback_handler.o -c $(previous_dir)/src/callback_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

window_handler.o: $(previous_dir)/src/window_handler.cpp
	g++ -g -o window_handler.o -c $(previous_dir)/src/window_handler.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

collision_layers.o: $(previous_dir)/src/collision_layers.cpp
	g++ -g -o collision_layers.o -c $(previous_dir)/src/collision_layers.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

run: all
	LD_LIBRARY_PATH="$(previous_dir)/FLAC/lib:$LD_LIBRARY_PATH" ./engine $(previous_dir)/games/testing game.py

run_dochs: all
	LD_LIBRARY_PATH="$(previous_dir)/FLAC/lib:$LD_LIBRARY_PATH" ./engine $(previous_dir)/games/dochs mvania.py

r_debug: all 
	LD_LIBRARY_PATH="$(previous_dir)/FLAC/lib:$LD_LIBRARY_PATH" gdb --args ./engine $(previous_dir)/games/testing game.py

runD: all
	LD_LIBRARY_PATH="$(previous_dir)/FLAC/lib:$LD_LIBRARY_PATH" ./engine $(previous_dir)/games/racing game.py


clean:
	rm -f engine 
	rm -rf *.o

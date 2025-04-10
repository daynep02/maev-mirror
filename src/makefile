INCLUDE_PYTHON = -lpython3.10 -I/usr/include/python3.10
INCLUDE_SFML = -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include/SFML/
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network
INCLUDE_GL = -lGL -lGLU -lglut -I/usr/include/GL/

.PHONY: all clean

engine: engine.cpp
	g++ -o engine engine.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML)

all: engine

clean:
	rm -rf engine *.o __pycache__


INCLUDE_OPENGL = -lGL -lglfw
WIN_INCLUDE_OPENGL = -I/mingw64/include -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32

INCLUDE_SFML = -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include/SFML/
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network
INCLUDE_GL = -lGL -lGLU -lglut -I/usr/include/GL/

.PHONY: all clean

helloworld: helloworld.cpp
	g++ -o helloworld helloworld.cpp $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

# win_helloworld:
# 	g++ -o helloworld helloworld.cpp $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

all: helloworld

clean:
	rm -f helloworld *.o

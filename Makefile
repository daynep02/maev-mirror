INCLUDE_PYTHON = -lpython3.10 -I/usr/include/python3.10

INCLUDE_SFML = -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include/SFML/
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

.PHONY: all clean

all: helloworld.cpp
	g++ -o engine *.cpp $(INCLUDE_PYTHON) $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

# win_helloworld:
# 	g++ -o helloworld helloworld.cpp $(INCLUDE_SFML) $(INCLUDE_SFML_EXTRAS)

run:
	./engine

clean:
	rm -f engine 
	rm -rf *.o

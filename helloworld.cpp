#include <Python.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <optional>

// Example code from https://www.glfw.org/documentation.html

int main(int argc, char *argv[]) {
  // Python setup
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }

  // SFML setup
  sf::RenderWindow window(sf::VideoMode({400, 400}), "Hello World!");
  sf::CircleShape shape(200.f);
  shape.setFillColor(sf::Color::Green);

  // Python usage
  Py_Initialize();

#if 1
  PyRun_SimpleString("print('Python initialized!')");
#endif

  // SFML usage
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

#if 1
  PyRun_SimpleString("print('Program finished!')");
#endif

  return 0;
}

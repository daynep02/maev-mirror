#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Example code from https://www.glfw.org/documentation.html

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Hello World!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}


#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
	std::cout << "Starting up" << std::endl;
	
	sf::ContextSettings ctxSettings;
	ctxSettings.depthBits = 32;

	sf::RenderWindow window(sf::VideoMode(640, 480), "My Window", sf::Style::Default, ctxSettings);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		for (sf::Event event; window.pollEvent(event); ) {
			if ((event.type == sf::Event::KeyPressed) &&
					(event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		window.setActive();
		window.clear();

		window.draw(shape);

		window.display();
	}
}

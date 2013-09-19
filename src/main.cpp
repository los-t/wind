#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const float DELTA = 10.f;

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
			switch (event.type) {
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					else {
						switch (event.key.code) {
							case sf::Keyboard::Up: shape.move(0.f, -1.f *DELTA); break;
							case sf::Keyboard::Down: shape.move(0.f, DELTA); break;
							case sf::Keyboard::Left: shape.move(-1.f * DELTA, 0.f); break;
							case sf::Keyboard::Right: shape.move(DELTA, 0.f); break;

							default: break;
						}
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;

				default: break;
			}
		}

		window.setActive();
		window.clear();

		window.draw(shape);

		window.display();
	}
}

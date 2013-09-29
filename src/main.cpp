#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <SFML/Window.hpp>

#include "gl/loader.h"
#include "gl/model.h"
#include "gl/render.h"
#include "gl/scene.h"

const float DELTA = 10.f;

int main() {
	std::cout << "Starting up" << std::endl;

	sf::ContextSettings ctxSettings;
	ctxSettings.depthBits = 32;
	ctxSettings.majorVersion = 3;
	ctxSettings.minorVersion = 1;

	sf::Window window(sf::VideoMode(640, 480), "My Window", sf::Style::Default, ctxSettings);
	window.setVerticalSyncEnabled(true);

	if (GLEW_OK != glewInit()) {
		std::cout << "Could not init glew" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		gl::Model m = gl::Loader::load();
		gl::Scene scn; scn.push(m);
		gl::Render render;

		bool running = true;
		while (running) {
			for (sf::Event event; window.pollEvent(event); ) {
				if ((event.type == sf::Event::KeyPressed) &&
						(event.key.code == sf::Keyboard::Escape)) {
					running = false;
				}

				switch (event.type) {
					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::Escape)
							running = false;
						else {
							switch (event.key.code) {
								//case sf::Keyboard::Up: shape.move(0.f, -1.f *DELTA); break;
								//case sf::Keyboard::Down: shape.move(0.f, DELTA); break;
								//case sf::Keyboard::Left: shape.move(-1.f * DELTA, 0.f); break;
								//case sf::Keyboard::Right: shape.move(DELTA, 0.f); break;

								default: break;
							}
						}
						break;
					case sf::Event::Closed:
						running = false;
						break;

					case sf::Event::Resized:
						glViewport(0, 0, event.size.width, event.size.height);
						break;

					default: break;
				}
			}

			window.setActive();

			render.update(scn);

			window.display();
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Shutting down" << std::endl;
	window.close();
}

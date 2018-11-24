#include "renderer.h"

Renderer::Renderer() {
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
	window->setFramerateLimit(25);
	for(int i = 0; i < 13; i++) {
		textures[i].loadFromFile("contents/cells.png", sf::IntRect(i*16, 0, 16, 16));
	}
	mainMenuTexture.loadFromFile("contents/mainmenu.png");
}

void Renderer::mainLoop() {
	while(window->isOpen()) {
		sf::Event event;
		while(window->pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window->close();
			}
		}

		drawCells();
		window->display();
	}
}

void Renderer::drawCells() {
	auto scale = cellSize / 16;
	sf::Sprite sprite;
	for(int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < fieldHeight; j++) {
			if(logic.getCell(i, j).isOpen == false)
				sprite.setTexture(textures[1]);

			sprite.setPosition(i * cellSize, j * cellSize);
			sprite.setScale(sf::Vector2f(scale, scale));
			window->draw(sprite);
		}
	}
}

void Renderer::drawMainMenu() {
	auto xscale = windowWidth / 512;
	auto yscale = windowHeight / 512;
	sf::Sprite sprite;
	sprite.setTexture(mainMenuTexture);
	sprite.setScale(sf::Vector2f(xscale, yscale));
	window->draw(sprite);
}
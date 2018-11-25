#include "renderer.h"
#include <unistd.h>

Renderer::Renderer() {
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				logic.isInMainMenu = true;
				logic.isFirstTurn = true;
				logic.isLoseOrWin = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				mouseClick(event);
			}
		}

		draw();
		window->display();
	}
}

void Renderer::drawCells() {
	auto scale = cellSize / 16;
	sf::Sprite sprite;
	for(int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < fieldHeight; j++) {
			auto cell = logic.getCell(i, j);
			
			if (cell.isOpen) {
				sprite.setTexture(textures[0]);
				if(cell.neighboringMines == 1)
					sprite.setTexture(textures[2]);
				if(cell.neighboringMines == 2)
					sprite.setTexture(textures[3]);
				if(cell.neighboringMines == 3)
					sprite.setTexture(textures[4]);
				if(cell.neighboringMines == 4)
					sprite.setTexture(textures[5]);
				if(cell.neighboringMines == 5)
					sprite.setTexture(textures[6]);
				if(cell.neighboringMines == 6)
					sprite.setTexture(textures[7]);
				if(cell.neighboringMines == 7)
					sprite.setTexture(textures[8]);
				if(cell.neighboringMines == 8)
					sprite.setTexture(textures[9]);
			}
			else if (!cell.isOpen) {
				sprite.setTexture(textures[1]);
				if(cell.isFlagged)
					sprite.setTexture(textures[11]);
				if(cell.isSuspect)
					sprite.setTexture(textures[10]);
			}
			if(logic.isLoseOrWin && cell.isMine) {
				sprite.setTexture(textures[12]);
			}
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

void Renderer::draw() {
	if(!logic.isInMainMenu)
		drawCells();
	else if(logic.isInMainMenu)
		drawMainMenu();
}

void Renderer::mouseClick(const sf::Event& event) {
	int x = event.mouseButton.x;
	int y = event.mouseButton.y;

	if (x < 0 || y < 0)
		return;

	int columnWidth = window->getSize().x / fieldWidth;
	int rowHeight = window->getSize().y / fieldHeight;

	const unsigned cellX = x / columnWidth;
	const unsigned cellY = y / rowHeight;


	
	if(logic.isLoseOrWin) {
		logic.isInMainMenu = true;
		logic.isFirstTurn = true;
		logic.isLoseOrWin = false;
		return;
	}

	if(logic.isInMainMenu && event.mouseButton.button == sf::Mouse::Left) {

		if(y > 100 && y <= 300) {
			logic.clearField();
			logic.isInMainMenu = false;
			return;
		} else if (y > 300 && y < 512) {
			window->close(); 
		}

	} else if (logic.isFirstTurn && event.mouseButton.button == sf::Mouse::Left) {

		logic.isFirstTurn = false;
		logic.newField(cellX, cellY);
		logic.open(cellX, cellY);
	
	} else if (event.mouseButton.button == sf::Mouse::Left 
								&& !logic.getCell(cellX, cellY).isOpen
								&& !logic.getCell(cellX, cellY).isFlagged
								&& !logic.getCell(cellX, cellY).isSuspect
								&& !logic.isFirstTurn) {

		int res = logic.open(cellX, cellY);
		if(res == 0) {
			logic.isLoseOrWin = true;
		}
		if(logic.remainingMines == 0) {
			logic.isLoseOrWin = true;
		}

	} else if (event.mouseButton.button == sf::Mouse::Right) {
		logic.mark(cellX, cellY);
		if(logic.remainingMines == 0) {
			logic.isLoseOrWin = true;
		}
	} 
}
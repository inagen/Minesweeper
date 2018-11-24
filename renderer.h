#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include "logic.h"

constexpr unsigned cellSize     = 32;
constexpr unsigned windowWidth  = fieldWidth*cellSize;
constexpr unsigned windowHeight = fieldHeight*cellSize;

class Renderer {
private:
	GameLogic logic;
	sf::RenderWindow* window;
	std::array<sf::Texture, 13> textures;
	sf::Texture mainMenuTexture;
public:
	Renderer();
	void mainLoop();
private:
	void mouseClick();
	void drawCells();
	void drawMainMenu();
};
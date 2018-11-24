#pragma once
#include <array>

const unsigned fieldWidth = 64;
const unsigned fieldHeight = 64;

struct Cell {
	bool isMine = false;
	unsigned neighboringMines = 0;
};

using cArray = std::array<Cell, fieldWidth*fieldHeight>;

class GameLogic {
public:
	unsigned const numberOfMines = (fieldWidth*fieldHeight) / 10;
	cArray field;
public:
	cArray getNewField(unsigned, unsigned);
	void clearField();
	bool isCellHere(unsigned, unsigned);
	bool isMine(unsigned, unsigned);
	unsigned calculateNeighboringMines(unsigned, unsigned);
	void calculateNeighboringMinesForAll();
};
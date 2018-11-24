#pragma once
#include <array>

constexpr unsigned fieldWidth    = 16;
constexpr unsigned fieldHeight   = 16;
constexpr unsigned numberOfMines = (fieldWidth*fieldHeight) / 10;

struct Cell {
	bool isOpen = false;
	bool isFlagged = false;
	bool isSuspect = false;
	bool isMine = false;
	unsigned neighboringMines = 0;
};

using cArray = std::array<Cell, fieldWidth*fieldHeight>;

class GameLogic {
public:
	bool isFirstTurn = false;
	bool isStarted = false;
	cArray field;
public:
	cArray getNewField(unsigned, unsigned);
	void clearField();
	bool isCellHere(unsigned, unsigned);
	bool isMine(unsigned, unsigned);
	unsigned calculateNeighboringMines(unsigned, unsigned);
	void calculateNeighboringMinesForAll();
	Cell getCell(unsigned, unsigned);
	int open(unsigned, unsigned);
	void revOpen(unsigned, unsigned);
};
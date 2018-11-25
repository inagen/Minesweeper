#pragma once
#include <array>

constexpr unsigned fieldWidth    = 16;
constexpr unsigned fieldHeight   = 16;
constexpr unsigned numberOfMines = (fieldWidth*fieldHeight) / 32;

struct Cell {
	bool isOpen = false;
	bool isFlagged = false;
	bool isSuspect = false;
	bool isMine = false;
	unsigned neighboringMines = -1;
};

using cArray = std::array<Cell, fieldWidth*fieldHeight>;

class GameLogic {
public:
	bool isLoseOrWin = false;
	bool isFirstTurn = true;
	bool isInMainMenu = true;
	int remainingMines = numberOfMines;
	cArray field;
public:
	void newField(unsigned, unsigned);
	void clearField();
	bool isCellHere(unsigned, unsigned);
	bool isMine(unsigned, unsigned);
	unsigned calculateNeighboringMines(unsigned, unsigned);
	void calculateNeighboringMinesForAll();
	Cell getCell(unsigned, unsigned);
	int open(unsigned, unsigned);
	void recOpen(unsigned, unsigned);
	void mark(unsigned, unsigned);
};
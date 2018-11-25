#include "logic.h"
#include "time.h"
#include <iostream>

void GameLogic::newField(unsigned xpos, unsigned ypos) {
	std::cout << "remainingMines: " << remainingMines << std::endl;
	srand(time(NULL));
	for(int i = 0; i < numberOfMines; i++) {
		unsigned x = rand() % fieldWidth;
		unsigned y = rand() % fieldHeight;  
		if(x == xpos && y == ypos) {
			i--;
			continue;
		}
		x %= fieldWidth;
		y %= fieldHeight;
		field[x + y * fieldWidth].isMine = true;
	}
	calculateNeighboringMinesForAll();
}

void GameLogic::clearField() {
	field = cArray();
}

bool GameLogic::isCellHere(unsigned x, unsigned y) {
	if(x < 0 || x >= fieldWidth || y < 0 || y >= fieldHeight)
		return false;
	else
		return true;
}

bool GameLogic::isMine(unsigned x, unsigned y) {
	if(!isCellHere(x, y))
		return false;
	x %= fieldWidth;
	y %= fieldHeight;
	return field[x + y * fieldWidth].isMine;
}

unsigned GameLogic::calculateNeighboringMines(unsigned x, unsigned y) {
	unsigned n = 0;
	if(isMine(x, y)) { return 0; }

	if(isMine(x+1, y)) { n++; }
	if(isMine(x-1, y)) { n++; }
	if(isMine(x, y+1)) { n++; }
	if(isMine(x, y-1)) { n++; }

	if(isMine(x+1, y+1)) { n++; }
	if(isMine(x+1, y-1)) { n++; }
	if(isMine(x-1, y+1)) { n++; }
	if(isMine(x-1, y-1)) { n++; }

	return n;
}

void GameLogic::calculateNeighboringMinesForAll() {
	for (int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < fieldHeight; j++) {
			int x = i;
			int y = j;
			x %= fieldWidth;
			y %= fieldHeight;
			field[x + y * fieldWidth].neighboringMines = calculateNeighboringMines(i, j);
		}
	}
}

Cell GameLogic::getCell(unsigned x, unsigned y) {
	x %= fieldWidth;
	y %= fieldHeight;
	return field[x + y * fieldWidth];
}

int GameLogic::open(unsigned x, unsigned y) {
	auto cell = getCell(x, y);
	auto ax = x;
	auto ay = y;
	ax %= fieldWidth;
	ay %= fieldHeight;

	if(cell.isMine)
		return 0;

	recOpen(x, y);
	//field[ax + ay * fieldWidth].isOpen = true;
	
	return 1;
}

void GameLogic::recOpen(unsigned x, unsigned y) {
	if(!isCellHere(x, y)){
		return;
	}
	
	
	auto cell = getCell(x, y);
	auto ax = x;
	auto ay = y;
	ax %= fieldWidth;
	ay %= fieldHeight;

	auto nm = cell.neighboringMines;
	if(nm !=0 && !cell.isOpen) {
		field[ax + ay * fieldWidth].isOpen = true;
		return;
	}
	if(cell.isOpen || cell.isFlagged || cell.isSuspect) {
		return;
	}
 	
	if(!cell.isMine) {
		field[ax + ay * fieldWidth].isOpen = true;
		recOpen(x+1, y);
		recOpen(x-1, y);
		recOpen(x, y+1);
		recOpen(x, y-1);
		recOpen(x+1, y+1);
		recOpen(x+1, y-1);
		recOpen(x-1, y+1);
		recOpen(x-1, y-1);
	}
}

void GameLogic::mark(unsigned x, unsigned y) {
	auto cell = getCell(x, y);
	if(cell.isOpen)
		return;

	bool isMine = cell.isMine;
	bool isFlagged = cell.isFlagged;
	bool isSuspect = cell.isSuspect;
	x %= fieldWidth;
	y %= fieldHeight;
	
	if(!isFlagged && !isSuspect) {
		if(isMine) {
			remainingMines--;
		}
		std::cout << "remainingMines: " << remainingMines << std::endl;
		field[x + y * fieldWidth].isFlagged = true;
	}
	else if (isFlagged && !isSuspect) {
		if(isMine) {
			remainingMines++;
		}
		std::cout << "remainingMines: " << remainingMines << std::endl;
		field[x + y * fieldWidth].isSuspect = true;
		field[x + y * fieldWidth].isFlagged = false;
	} else if (!isFlagged && isSuspect) {
		field[x + y * fieldWidth].isSuspect = false;
		field[x + y * fieldWidth].isFlagged = false;
	}
}
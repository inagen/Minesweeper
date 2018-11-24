#include "logic.h"
#include "time.h"

cArray GameLogic::getNewField(unsigned xpos, unsigned ypos) {
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
	return field;
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
	x %= fieldWidth;
	y %= fieldHeight;
	return field[x + y * fieldWidth].isMine;
}

unsigned GameLogic::calculateNeighboringMines(unsigned x, unsigned y) {
	unsigned n = 0;
	if(isCellHere(x, y) && isMine(x, y)) { return 0;}

	if(isCellHere(x+1, y) && isMine(x+1, y)) { n++; }
	if(isCellHere(x-1, y) && isMine(x-1, y)) { n++; }

	if(isCellHere(x, y+1) && isMine(x, y+1)) { n++; }
	if(isCellHere(x, y-1) && isMine(x, y-1)) { n++; }

	if(isCellHere(x+1, y+1) && isMine(x+1, y+1)) { n++; }
	if(isCellHere(x+1, y-1) && isMine(x+1, y-1)) { n++; }

	if(isCellHere(x+1, y-1) && isMine(x+1, y-1)) { n++; }
	if(isCellHere(x-1, y-1) && isMine(x-1, y-1)) { n++; }

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
	if(getCell(x, y).isMine)
		return 0;
	else
		revOpen(x, y);
	return 1;
}

void GameLogic::revOpen(unsigned x, unsigned y) {
	if(!isCellHere(x, y))
		return;
	
	auto cell = getCell(x, y);
	auto ax = x;
	auto ay = y;
	x %= fieldWidth;
	y %= fieldHeight;
	
	if(cell.isOpen || cell.isMine || cell.isFlagged || cell.isSuspect)
		return;
	
	if(cell.neighboringMines != 0 && !cell.isMine) {
		field[x + y * fieldWidth].isOpen = true;
		revOpen(ax, ay + 1);
		revOpen(ax, ay - 1);
		revOpen(ax + 1, ay);
		revOpen(ax - 1, ay);
		revOpen(ax + 1, ay + 1);
		revOpen(ax + 1, ay - 1);
		revOpen(ax - 1, ay + 1);
		revOpen(ax - 1, ay - 1);
	}
}
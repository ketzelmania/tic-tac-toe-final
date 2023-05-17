#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Position {
	int row;
	int col;
	Position(int r, int c);
};

class Board {
private:
	string State[3][3];
public:
	Board();

	void SetPosition(int row, int col, string player);
	string GetPosition(int row, int col);
	void PrintPosition();
	void ClearBoard();

	Position ConvertMoveIndexToPosition(int MoveIndex);
	bool IsMovesRemaining();

	int Minimax(int depth, bool is_maxing_player, string player);

	string GetVictoryState(int RecentMove = -1);
	Position GetBestMove(string player);
};
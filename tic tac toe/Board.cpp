#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

Position::Position(int r, int c) {
	row = r; col = c;
}

Board::Board() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			State[r][c] = "_";
		}
	}
}

void Board::SetPosition(int row, int col, string player) {
	State[row][col] = player;
}

string Board::GetPosition(int row, int col) {
	return State[row][col];
}

void Board::PrintPosition() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cout << State[r][c] << " ";
		}
		cout << endl;
	}
}

void Board::ClearBoard() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			State[r][c] = "_";
		}
	}
}
 
bool Board::IsMovesRemaining() {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (State[r][c] == "_") return true;
		}
	}
	return false;
}

Position Board::ConvertMoveIndexToPosition(int MoveIndex) {
	int row = floor(MoveIndex / 3);
	int col = MoveIndex % 3;
	Position NewPos(row,col);
	return NewPos;
}

string Board::GetVictoryState(int RecentMove) {
	if (RecentMove != -1) {
		Position RecentPosition = ConvertMoveIndexToPosition(RecentMove);

		string InitialCharacter = State[RecentPosition.row][RecentPosition.col];
		if (InitialCharacter == "_") return "_";

		bool Success = true;

		// check row
		for (int c = 0; c < 3; c++) {
			if (State[RecentPosition.row][c] != InitialCharacter) {
				Success = false;
				break;
			}
		}

		if (Success) return InitialCharacter;
		Success = true;

		// check column
		for (int r = 0; r < 3; r++) {
			if (State[r][RecentPosition.col] != InitialCharacter) {
				Success = false;
				break;
			}
		}

		if (Success) return InitialCharacter;
		Success = true;

		if (!(RecentMove == 0 || RecentMove == 2 || RecentMove == 4 || RecentMove == 6 || RecentMove == 8)) {
			return "_";
		}

		// check diagonally
		if (State[0][0] != "_" && State[0][0] == State[1][1] && State[1][1] == State[2][2]) {
			return State[0][0];
		}

		if (State[0][2] != "_" && State[0][2] == State[1][1] && State[1][1] == State[2][0]) {
			return State[0][2];
		}

		return "_";
	}

	// check horizontally
	string InitialCharacter;
	for (int r = 0; r < 3; r++) {
		InitialCharacter = State[r][0];
		if (InitialCharacter == "_") continue;

		bool Broken = false;
		for (int c = 0; c < 3; c++) {
			if (State[r][c] != InitialCharacter) {
				Broken = true;
				break;
			}
		}
		if (Broken == true) continue;
		return InitialCharacter;
	}

	// check vertically
	for (int c = 0; c < 3; c++) {
		InitialCharacter = State[0][c];
		if (InitialCharacter == "_") continue;

		bool Broken = false;
		for (int r = 0; r < 3; r++) {
			if (State[r][c] != InitialCharacter) {
				Broken = true;
				break;
			}
		}
		if (Broken == true) continue;
		return InitialCharacter;
	}

	// check diagonally
	if (State[0][0] != "_" && State[0][0] == State[1][1] && State[1][1] == State[2][2]) {
		return State[0][0];
	}

	if (State[0][2] != "_" && State[0][2] == State[1][1] && State[1][1] == State[2][0]) {
		return State[0][2];
	}

	return "_";
}

int Board::Minimax(int depth, bool is_maxing_player, string player) {
	if (GetVictoryState() == player) return 10 - depth;
	if (GetVictoryState() != "_") return -100;
	if (!IsMovesRemaining()) return 0;

	if (!is_maxing_player) {
		int BestValue = -1000;
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				if (State[r][c] != "_") continue;
				State[r][c] = player;

				State[r][c] = player;
				BestValue = max(BestValue, Minimax(depth + 1, !is_maxing_player, player));
				State[r][c] = "_";
			}
		}
		return BestValue;
	}
	else {
		int BestValue = 1000;
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				if (State[r][c] != "_") continue;

				string opponent = "X";
				if (player == opponent) opponent = "O";

				State[r][c] = opponent;
				BestValue = min(BestValue, Minimax(depth + 1, !is_maxing_player, player));
				State[r][c] = "_";
			}
		}
		return BestValue;
	}
}

Position Board::GetBestMove(string player) {
	int BestValue = -1000;
	Position BestMove(-1, -1);

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (State[r][c] != "_") continue;

			State[r][c] = player;
			int ThisValue = Minimax(0, true, player);
			State[r][c] = "_";

			if (ThisValue > BestValue) {
				BestMove.row = r;
				BestMove.col = c;
				BestValue = ThisValue;
			}
		}
	}

	cout << BestValue << endl;
	return BestMove;
}
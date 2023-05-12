#include "Board.h"

using namespace std;

void DisplayTitle() {
	cout << "TIC TAC TOE" << endl << endl;
	cout << "Rules:" << endl;
	cout << "\tPlay on a 3x3 board." << endl;
	cout << "\tWe will alternate which player goes first. The player who goes first will be 'X'." << endl;
	cout << "\tThe human player goes first initially." << endl << endl;

	cout << "\tOn your turn, type a number 1-9 representing one of the 9 spaces on the board." << endl << "\tThis will be your move." << endl;
	cout << "\t1 represents the top left corner, 4 is the middle left, and 9 is the bottom right." << endl;
	cout << "\Alternate until somebody has 3 in a row, or there are no moves available." << endl;
}

enum TURNS {
	PLAYER, COMPUTER
};

int main() {
	Board NewBoard;

	int CurrentTurn = PLAYER;
	string PlayerIcon = "X";

	string PlayAgain = "Y";
	while (PlayAgain == "Y" or PlayAgain == "y") {
		DisplayTitle();
		NewBoard.ClearBoard();
		NewBoard.PrintPosition();

		while (NewBoard.IsMovesRemaining() && (NewBoard.GetVictoryState() == "_")) {
			if (CurrentTurn == PLAYER) {
				cout << "Your Turn! Pick your number: " << endl;
				int PlayerMoveIndex;
				cin >> PlayerMoveIndex;

				while (PlayerMoveIndex < 1 || PlayerMoveIndex > 9) {
					cout << "Invalid choice. Pick a number 1-9: " << endl;
					cin >> PlayerMoveIndex;
				}

				PlayerMoveIndex--;

				Position ConvertedPlayerPosition = NewBoard.ConvertMoveIndexToPosition(PlayerMoveIndex);
				NewBoard.SetPosition(ConvertedPlayerPosition.row, ConvertedPlayerPosition.col, PlayerIcon);
				NewBoard.PrintPosition();
			}
			else {
				string ComputerIcon = "O";
				if (PlayerIcon == ComputerIcon) ComputerIcon = "X";

				Position BestMove = NewBoard.GetBestMove(ComputerIcon);
				cout << "I pick row " << BestMove.row << ", column " << BestMove.col << "!" << endl;

				NewBoard.SetPosition(BestMove.row, BestMove.col, ComputerIcon);
				NewBoard.PrintPosition();
			}
			CurrentTurn = (CurrentTurn + 1) % 2;
		}

		cout << "Game Over!" << endl;
		cout << NewBoard.GetVictoryState() << " Wins!" << endl << endl;
		cout << "Play again? (Y/N)" << endl;
		cin >> PlayAgain;

		if (PlayerIcon == "X") {
			PlayerIcon = "O";
		}
		else {
			PlayerIcon = "X";
		}
	}

	return 0;
}
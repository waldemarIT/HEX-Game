#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Board.h"
using namespace std;


int main() {
    char command[7024];
    Board board_method;
    int num = 2000;
    while (num) {
        int rows, cols, maxCols = 0;
        bool endSession = false;
        char** board = board_method.loadBoard(rows, cols, command, endSession);
        int size = board_method.calculateBoardSize();
        int** values = new int* [rows];
        bool success = false;

        //int** values = new int* [cols];
        if (endSession) {
            break;

        }

        if (strcmp(command, "IS_BOARD_CORRECT") == 0) {
            if (board_method.isBoardCorrect(board, rows)) {
                cout << "YES" << endl;
                cout << endl;
            }
            else {
                cout << "NO" << endl;
                cout << endl;
            }
        }
        else if (strcmp(command, "BOARD_SIZE") == 0) {
            cout << board_method.calculateBoardSize() << endl;
        }
        else if (strcmp(command, "PAWNS_NUMBER") == 0) {
            int redCount, blueCount;
            board_method.countPieces(board, rows, redCount, blueCount);
            int sum = redCount + blueCount;
            cout << sum << endl;
        }
        else if (strcmp(command, "IS_GAME_OVER") == 0) {

            board_method.conversion_coordinates_for_game_over(board, rows, success);

        }
        else if (strcmp(command, "IS_BOARD_POSSIBLE") == 0) {

            board_method.is_board_possible(board, rows, success);
        }

        else {
            for (int i = 0; i < rows; ++i) {
                delete[] board[i];
            }
            delete[] board;
            break;
        }

        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
        //break;
    }

    return 0;
}
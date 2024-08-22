#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;


//const char* COMMANDS[] = { "CORRECT_BOARD", "BOARD_SIZE" , "IS_BOARD_CORRECT" , "PAWNS_NUMBER" , "IS_GAME_OVER", "IS_BOARD_POSSIBLE" };
//const int NUM_COMMANDS = 6;

bool Board::isCommand(const char* line) {
    for (int i = 0; i < NUM_COMMANDS; ++i) {
        if (strcmp(line, commands[i]) == 0) {
            return true;
        }
    }
    return false;
}

//char** Board::loadBoard(int& rows, int& maxCols, char* command, bool& endSession) {
//    int capacity = 10;
//    char** board = new char* [capacity];
//    vector<vector<char>> boards;
//
//    char tempLine[1024];
//    rows = 0;
//    maxCols = 0;
//    bool wasLastLineEmpty = false; // Track if the last line was empty
//
//    while (true) {
//        cin.getline(tempLine, sizeof(tempLine));
//        if (isCommand(tempLine)) {
//            strcpy(command, tempLine);
//            break;
//        }
//        if (strlen(tempLine) == 0) {
//            if (wasLastLineEmpty) { // If this and the last line are empty, end session
//                endSession = true;
//                break;
//            }
//            wasLastLineEmpty = true; // Mark this line as empty for the next iteration
//            continue; // Skip further processing for this iteration
//        }
//        else {
//            wasLastLineEmpty = false; // Reset since this line is not empty
//        }
//
//        if (rows >= capacity) {
//            capacity *= 2;
//            char** newBoard = new char* [capacity];
//            for (int i = 0; i < rows; ++i) {
//                newBoard[i] = board[i];
//            }
//            delete[] board;
//            board = newBoard;
//        }
//
//        int lineLength = strlen(tempLine);
//        board[rows] = new char[lineLength + 1];
//        strcpy(board[rows], tempLine);
//
//        if (lineLength > maxCols) {
//            maxCols = lineLength;
//        }
//
//        rows++;
//    }
//    this->rows = rows;
//    this->cols = cols;
//    this->board = board;
//    return board;
//}
char** Board::loadBoard(int& outputRows, int& maxCols, char* command, bool& endSession) {
    int capacity = 10;
    board = new char* [capacity];

    char tempLine[1024];
    rows = 0;
    maxCols = 0;
    bool wasLastLineEmpty = false;

    while (true) {
        std::cin.getline(tempLine, sizeof(tempLine));
        if (isCommand(tempLine)) {
            strcpy(command, tempLine);
            break;
        }
        if (strlen(tempLine) == 0) {
            if (wasLastLineEmpty) {
                endSession = true;
                break;
            }
            wasLastLineEmpty = true;
            continue;
        }
        else {
            wasLastLineEmpty = false;
        }

        if (rows >= capacity) {
            capacity *= 2;
            char** newBoard = new char* [capacity];
            memcpy(newBoard, board, rows * sizeof(char*));
            delete[] board;
            board = newBoard;
        }

        int lineLength = strlen(tempLine);
        board[rows] = new char[lineLength + 1];
        strcpy(board[rows], tempLine);

        if (lineLength > maxCols) {
            maxCols = lineLength;
        }
        rows++;
    }

    outputRows = rows;
    this->cols = maxCols;

    return board;
}

int Board::calculateBoardSize() {

    /* int size = 0;

     if (rows % 2 == 0) {
         size = rows / 2;
     }
     else {
         size = (rows / 2);
     }
     return size;*/
    return rows / 2;
}

bool Board::isBoardCorrect(char** board, int rows) {
    int r = 0;
    int b = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; board[i][j] != '\0'; ++j) {
            if (board[i][j] == 'r') {
                r++;
            }
            else if (board[i][j] == 'b') {
                b++;
            }

        }
    }
    if (r == b || r == b + 1) {
        return true;
    }
    else if (r == 0 && b == 0) {
        return true;
    }


    else {
        return false;
    }
}

void Board::countPieces(char** board, int rows, int& redCount, int& blueCount) {
    redCount = 0;
    blueCount = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; board[i][j] != '\0'; ++j) {
            if (board[i][j] == 'r') redCount++;
            else if (board[i][j] == 'b') blueCount++;
        }
    }
}

void Board::conversion_coordinates_for_game_over(char** board, int rows, bool& success) {
    int size = calculateBoardSize();
    int** table = new int* [size];
    int redwins;
    int bluewins;
    success = false;
    // Allocate memory for each row
    for (int i = 0; i < size; i++) {
        table[i] = new int[size];
    }

    bool** visited = new bool* [size];
    for (int i = 0; i < size; i++) {
        visited[i] = new bool[size] {false};
    }

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {

            int column_board = 2 + 3 * row + 3 * col;
            int row_board = size + row - col;

            table[row][col] = board[row_board][column_board];
        }
    }

    bool is_game_end = false;
    bool is_second_path = false;
    if (isBoardCorrect(board, rows)) {
        // Start DFS for 'r' from the top of the board
        for (int j = 0; j < size; j++) {
            if (table[0][j] == 'r') {
                redwins = DFS(table, visited, 0, j, 'r');
                if (redwins > 0) {
                    cout << "YES RED" << endl;
                    is_game_end = true;
                    success = true;
                    break;
                }

                for (int k = 0; k < size; k++) {
                    for (int m = 0; m < size; m++) {
                        visited[k][m] = false;
                    }
                }
            }
        }


        if (!is_game_end) {
            for (int i = 0; i < size; i++) {
                if (table[i][0] == 'b') {
                    bluewins = DFS(table, visited, i, 0, 'b');

                    if (bluewins > 0) {
                        //cout << bluewins << endl;
                        cout << "YES BLUE" << endl;
                        is_game_end = true;
                        success = true;
                        break;
                    }

                    for (int k = 0; k < size; k++) {
                        for (int m = 0; m < size; m++) {
                            visited[k][m] = false;
                        }
                    }
                }
            }
        }
    }

    if (success == false) {
        cout << "NO" << endl;
    }


    /*for (int i = 0; i < size; i++) {
        delete[] table[i];
        delete[] visited[i];
    }

    delete[] table;
    delete[] visited;*/

}

void Board::is_board_possible(char** board, int rows, bool& success) {
    int size = calculateBoardSize();
    int** table = new int* [size];
    int redwins = 0;
    int bluewins = 0;
    success = false;
    //std::ofstream outfiles("output.txt", std::ios::app);
    //if (!outfiles.is_open()) {
    //    std::cerr << "Nie udaÅo siÄ otworzyÄ pliku output.txt do zapisu." << std::endl;
    //    return;  // Wczesne zakoÅczenie jeÅli plik nie mÃ³gÅ zostaÄ otwarty
    //}
    for (int i = 0; i < size; i++) {
        table[i] = new int[size];
    }

    this->visited = new bool* [size];
    for (int i = 0; i < size; i++) {
        visited[i] = new bool[size] {false};
    }

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {

            int column_board = 2 + 3 * row + 3 * col;
            int row_board = size + row - col;

            table[row][col] = board[row_board][column_board];
        }
    }

    bool space = true;
    if (isBoardCorrect(board, rows)) {

        for (int j = 0; j < size; j++) {
            if (table[0][j] == 'r') {
                redwins += DFS(table, visited, 0, j, 'r');
                if (redwins > 1) {
                    success = false;
                    space = false;
                    break;
                }
            }
        }
        if (redwins < 2) {
            success = true;
            space = false;
        }

        if (redwins == 0) {
            for (int i = 0; i < size; i++) {
                if (table[i][0] == 'b') {
                    bluewins += DFS(table, visited, i, 0, 'b');
                    if (bluewins > 1) {
                        success = false;
                        space = false;
                        break;
                    }
                }
            }
            if (bluewins < 2) {
                success = true;
                space = false;
            }
        }

        if (space) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (table[i][j] != 'r' && table[i][j] != 'b') {
                        success = true;
                        break;
                    }
                }
                break;
            }
        }
    }

    if (success == false) {
        /* outfiles << "NO" << '\n';
         outfiles.flush();*/
        cout << "NO" << endl;

    }
    else if (success == true) {
        /* outfiles << "YES" << '\n';
         outfiles.flush();*/
        cout << "YES" << endl;
    }
    /* outfiles << '\n';
     outfiles.flush();*/
    cout << endl;
    /* for (int i = 0; i < size; i++) {
         delete[] table[i];
         delete[] visited[i];
     }

     delete[] table;
     delete[] visited;*/
     //outfiles.close();
}


int rowNum[] = { -1, 1, 0, 0, -1, 1 };
int colNum[] = { 0, 0, -1, 1, 1, -1 };

bool Board::isValid(int x, int y, bool** visited, int** table, char color) {
    int size = calculateBoardSize();
    color != ' ';
    return (x >= 0) && (x < size) && (y >= 0) && (y < size) && !visited[x][y] && table[x][y] == color;

}

int Board::DFS(int** table, bool** visited, int x, int y, char color) {
    visited[x][y] = true;
    int count = 0;
    int size = calculateBoardSize();
    // cout << "visited in: " << x << ", " << y << " with value " << table[x][y] << endl;

    for (int i = 0; i < 6; i++) {
        int nextX = x + rowNum[i];
        int nextY = y + colNum[i];
        if (isValid(nextX, nextY, visited, table, color)) {
            count += DFS(table, visited, nextX, nextY, color);
            if (count >= 3) {
                //visited[x][y] = false;

                return count;
            }

        }
    }



    if (x == size - 1 && color == 'r') {
        count++;
        //visited[x][y] = false;
        if (count >= 3) {
            // visited[x][y] = false;

            return count;
        }

    }
    else  if (y == size - 1 && color == 'b') {
        count++;
        //visited[x][y] = false;
        if (count >= 3) {
            //visited[x][y] = false;

            return count;
        }
    }


    //visited[x][y] == false;
    return count;
}
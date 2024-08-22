#ifndef BOARD_H
#define BOARD_H
using namespace std;

class Board
{
public:

    char** board;
    bool** visited;
    int rows, cols;
    const char** commands;
    const int NUM_COMMANDS = 6;

    //vector<vector<bool>> visited;
    //Board(int r, int c) : rows(r), cols(c) {}

    //Board() {}
    Board() : board(nullptr), visited(nullptr), rows(0), cols(0), commands(nullptr) {
        initializeCommands();
    }

    void initializeCommands() {
        commands = new const char* [NUM_COMMANDS] {
            "CORRECT_BOARD", "BOARD_SIZE", "IS_BOARD_CORRECT", "PAWNS_NUMBER",
                "IS_GAME_OVER", "IS_BOARD_POSSIBLE"
            };
    }

    bool isCommand(const char* line);

    char** loadBoard(int& rows, int& maxCols, char* command, bool& endSession);

    int calculateBoardSize();

    bool isBoardCorrect(char** board, int rows);

    void countPieces(char** board, int rows, int& redCount, int& blueCount);

    void conversion_coordinates_for_game_over(char** board, int rows, bool& success);

    bool isValid(int x, int y, bool** visited, int** table, char color);

    int DFS(int** table, bool** visited, int x, int y, char color);

    void is_board_possible(char** board, int rows, bool& success);

    void findigPath(int** table, bool* visited, int x, int y, char color, bool& success);

    void findigPath(bool** visited, int x, int y, char color);

    bool DFS_(int** table, bool** visited, int x, int y, char color);

    ~Board() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
            delete[] visited[i];

        }
        delete[] board;
        delete[] commands;
        delete[] visited;
    }
};


#endif // BOARD_H
// Twenty Forty-Eight, by Al Sweigart
// A sliding tile game to combine exponentially-increasing numbers.
// Inspired by Gabriele Cirulli's 2048, which is a clone of Veewo Studios'
// 1024, which in turn is a clone of the Threes! game.
// More info at https://en.wikipedia.org/wiki/2048_(video_game)
// This code is available at https://nostarch.com/big-book-small-python-programming
// #79 TWENTY FORTY - EIGHT

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// Set up the constants:
string BLANK = ""; // A value that represents a blank space on the board.
vector<vector<string>> getNewBoard();
void drawBoard(vector<vector<string>> board);
int getScore(vector<vector<string>>& board);
void addTwoToBoard(vector<vector<string>>& board);
bool isFull(vector<vector<string>>& board);
string askForPlayerMove();
vector<string> combineTilesInColumn(vector<string> column);
vector<vector<string>> makeMove(vector<vector<string>> board, string move);

int main() {
    cout << "Twenty Forty - Eight, by Al Sweigart al@inventwithpython.com\n\n";
    cout << "Slide all the tiles on the board in one of four directions.Tiles with\n";
    cout << "like numbers will combine into larger - numbered tiles.A new 2 tile is\n";
    cout << "added to the board on each move.You win if you can create a 2048 tile.\n";
    cout << "You lose if the board fills up the tiles before then.\n";

    vector<vector<string>> gameBoard = getNewBoard();

    while (1) { // Main game loop.
        drawBoard(gameBoard);
        cout << "Score: " << getScore(gameBoard) << "\n";
        string playerMove = askForPlayerMove();
        gameBoard = makeMove(gameBoard, playerMove);
        addTwoToBoard(gameBoard);
        if (isFull(gameBoard)) {
            drawBoard(gameBoard);
            cout << "Game Over - Thanks for playing!\n";
            return 0;
        }
    }

    return 0;
}


vector<vector<string>> getNewBoard() {
    // Returns a new data structure that represents a board.
    // It's a dictionary with keys of (x, y) tuples and values of the tile
    // at that space.The tile is either a power - of - two integer or BLANK.
    // The coordinates are laid out as :
    //  X0 1 2 3
    // Y+-+-+-+-+
    // 0| | | | |
    //  +-+-+-+-+
    // 1| | | | |
    //  +-+-+-+-+
    // 2| | | | |
    //  +-+-+-+-+
    // 3| | | | |
    //  +-+-+-+-+
    vector<vector<string>> newBoard; // Contains the board data structure to be returned.
    // Loop over every possible space and set all the tiles to blank :
    for (int i = 0; i < 4; ++i) {
        vector<string> tmp(4, BLANK);
        newBoard.push_back(tmp);
    }

    // Pick two random spaces for the two starting 2's:
    int startingTwosPlaced = 0; // The number of starting spaces picked.
    while (startingTwosPlaced < 2) { // Repeat for duplicate spaces.
        std::random_device rd;  // Seed the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister PRNG engine
        std::uniform_int_distribution<int> distribution(0, 3); // Define the range
        // Generate a random number
        int randomSpace1 = distribution(gen);
        int randomSpace2 = distribution(gen);
        // Make sure the randomly selected space isn't already taken:
        if (newBoard[randomSpace1][randomSpace2] == BLANK) {
            newBoard[randomSpace1][randomSpace2] = "2";
            startingTwosPlaced++;
        }
    }

    return newBoard;
}

void drawBoard(vector<vector<string>> board) {
    // Draws the board data structure on the screen.
    
    // Go through each possible space left to right, top to bottom, and
    // create a list of what each space's label should be.
    
    cout << "+-----+-----+-----+-----+\n|     |     |     |     |\n";
    string one = "|";
    for (int i = 0; i < 4; ++i) {
        if (board[0][i] == "") {
            one += "     |";
        } else if (board[0][i] == "2") {
            one += "  2  |";
        } else if (board[0][i] == "4") {
            one += "  4  |";
        } else if (board[0][i] == "8") {
            one += "  8  |";
        } else if (board[0][i] == "16") {
            one += " 16  |";
        } else if (board[0][i] == "32") {
            one += " 32  |";
        } else if (board[0][i] == "64") {
            one += " 64  |";
        } else if (board[0][i] == "128") {
            one += " 128 |";
        } else if (board[0][i] == "256") {
            one += " 256 |";
        } else if (board[0][i] == "512") {
            one += " 512 |";
        } else if (board[0][i] == "1024") {
            one += "1024 |";
        } else {
            cout << "Error\n";
            cout << "board[0][i] = |" << board[0][i] << "|\n";
        }
    }
    cout << one << '\n';
    cout << "|     |     |     |     |\n";
    cout << "+-----+-----+-----+-----+\n|     |     |     |     |\n";
    string two = "|";
    for (int i = 0; i < 4; ++i) {
        if (board[1][i] == "") {
            two += "     |";
        } else if (board[1][i] == "2") {
            two += "  2  |";
        } else if (board[1][i] == "4") {
            two += "  4  |";
        } else if (board[1][i] == "8") {
            two += "  8  |";
        } else if (board[1][i] == "16") {
            two += " 16  |";
        } else if (board[1][i] == "32") {
            two += " 32  |";
        } else if (board[1][i] == "64") {
            two += " 64  |";
        } else if (board[1][i] == "128") {
            two += " 128 |";
        } else if (board[1][i] == "256") {
            two += " 256 |";
        } else if (board[1][i] == "512") {
            two += " 512 |";
        } else if (board[1][i] == "1024") {
            two += "1024 |";
        } else {
            cout << "Error\n";
            cout << "board[1][i] = |" << board[1][i] << "|\n";
        }
    }
    cout << two << '\n';
    cout << "|     |     |     |     |\n";
    cout << "+-----+-----+-----+-----+\n|     |     |     |     |\n";
    string three = "|";
    for (int i = 0; i < 4; ++i) {
        if (board[2][i] == "") {
            three += "     |";
        } else if (board[2][i] == "2") {
            three += "  2  |";
        } else if (board[2][i] == "4") {
            three += "  4  |";
        } else if (board[2][i] == "8") {
            three += "  8  |";
        } else if (board[2][i] == "16") {
            three += " 16  |";
        } else if (board[2][i] == "32") {
            three += " 32  |";
        } else if (board[2][i] == "64") {
            three += " 64  |";
        } else if (board[2][i] == "128") {
            three += " 128 |";
        } else if (board[2][i] == "256") {
            three += " 256 |";
        } else if (board[2][i] == "512") {
            three += " 512 |";
        } else if (board[2][i] == "1024") {
            three += "1024 |";
        } else {
            cout << "Error\n";
            cout << "board[2][i] = |" << board[2][i] << "|\n";
        }
    }
    cout << three << '\n';
    cout << "|     |     |     |     |\n";
    cout << "+-----+-----+-----+-----+\n|     |     |     |     |\n";
    string four = "|";
    for (int i = 0; i < 4; ++i) {
        if (board[3][i] == "") {
            four += "     |";
        } else if (board[3][i] == "2") {
            four += "  2  |";
        } else if (board[3][i] == "4") {
            four += "  4  |";
        } else if (board[3][i] == "8") {
            four += "  8  |";
        } else if (board[3][i] == "16") {
            four += " 16  |";
        } else if (board[3][i] == "32") {
            four += " 32  |";
        } else if (board[3][i] == "64") {
            four += " 64  |";
        } else if (board[3][i] == "128") {
            four += " 128 |";
        } else if (board[3][i] == "256") {
            four += " 256 |";
        } else if (board[3][i] == "512") {
            four += " 512 |";
        } else if (board[3][i] == "1024") {
            four += "1024 |";
        } else {
            cout << "Error\n";
            cout << "board[3][i] = |" << board[3][i] << "|\n";
        }
    }
    cout << four << '\n';
    cout << "|     |     |     |     |\n";
    cout << "+-----+-----+-----+-----+\n\n";
}

int getScore(vector<vector<string>>& board) {
    // Returns the sum of all the tiles on the board data structure.
    int score = 0;
    // Loop over every space and add the tile to the score:
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Only add non-blank tiles to the score:
            if (board[i][j] != BLANK) {
                int tmp = stoi(board[i][j]);
                score += tmp;
            }
        }
    }

    return score;
}

void addTwoToBoard(vector<vector<string>>& board) {
    // Adds a new 2 tile randomly to the board.
    while (1) {
        std::random_device rd;  // Seed the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister PRNG engine
        std::uniform_int_distribution<int> distribution(0, 3); // Define the range
        // Generate a random number
        int randomSpace1 = distribution(gen);
        int randomSpace2 = distribution(gen);
        // Make sure the randomly selected space isn't already taken:
        if (board[randomSpace1][randomSpace2] == BLANK) {
            board[randomSpace1][randomSpace2] = "2";
            return; // Return after finding one non - blank tile.
        }
    }
}

bool isFull(vector<vector<string>>& board) {
    // Returns True if the board data structure has no blanks.
    // Loop over every space on the board:
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // If a space is blank, return False:
            if (board[i][j] == BLANK) {
                return false;
            }
        }
    }

    return true; // No space is blank, so return True.
}

string askForPlayerMove() {
    // Asks the player for the direction of their next move (or quit).
    // Ensures they enter a valid move: either 'W', 'A', 'S' or 'D'.
    cout << "Enter move: (WASD or Q to quit)\n";
    while (1) { // Keep looping until they enter a valid move.
        string move = "";
        std::cout << "> ";
        cin >> move;
        transform(move.begin(), move.end(), move.begin(), ::toupper);
        if (move == "Q") {
            // End the program:
            cout << "Thanks for playing!\n";
            exit(0);
        }

        // Either return the valid move, or loop back and ask again:
        if (move == "W" || move == "A" || move == "S" || move == "D") {
            return move;
        } else {
            cout << "Enter one of 'W', 'A', 'S', 'D', or 'Q'.\n";
        }
    }
}

vector<vector<string>> makeMove(vector<vector<string>> board, string move) {
    // Carries out the move on the board.
    // The move argument is either 'W', 'A', 'S', or 'D' and the function
    // returns the resulting board data structure.
    // The board is split up into four columns, which are different
    // depending on the direction of the move:
    vector<vector<vector<int>>> allColumnsSpaces;
    if (move == "A") {
        allColumnsSpaces = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
                            {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
                            {{3, 0}, {3, 1}, {3, 2}, {3, 3}} };
    } else if (move == "W") {
        allColumnsSpaces = { {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                            {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
                            {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
                            {{0, 3}, {1, 3}, {2, 3}, {3, 3}} };
    } else if (move == "D") {
        allColumnsSpaces = { {{0, 3}, {0, 2}, {0, 1}, {0, 0}},
                            {{1, 3}, {1, 2}, {1, 1}, {1, 0}},
                            {{2, 3}, {2, 2}, {2, 1}, {2, 0}},
                            {{3, 3}, {3, 2}, {3, 1}, {3, 0}} };
    } else if (move == "S") {
        allColumnsSpaces = { {{3, 0}, {2, 0}, {1, 0}, {0, 0}},
                            {{3, 1}, {2, 1}, {1, 1}, {0, 1}},
                            {{3, 2}, {2, 2}, {1, 2}, {0, 2}},
                            {{3, 3}, {2, 3}, {1, 3}, {0, 3}} };
    } else {
        cout << "\n!!!\nERROR\n!!!\n";
    }

    // The board data structure after making the move:
    vector<vector<string>> boardAfterMove;
    for (int i = 0; i < 4; ++i) {
        vector<string> tmp(4, BLANK);
        boardAfterMove.push_back(tmp);
    }
    for (auto columnSpaces : allColumnsSpaces) { // Loop over all 4 columns.
        // Get the tiles of this column (The first tile is the "bottom"
        // of the column):
        vector<int> firstTileSpace = columnSpaces[0];
        vector<int> secondTileSpace = columnSpaces[1];
        vector<int> thirdTileSpace = columnSpaces[2];
        vector<int> fourthTileSpace = columnSpaces[3];

        string firstTile = board[firstTileSpace[0]][firstTileSpace[1]];
        string secondTile = board[secondTileSpace[0]][secondTileSpace[1]];
        string thirdTile = board[thirdTileSpace[0]][thirdTileSpace[1]];
        string fourthTile = board[fourthTileSpace[0]][fourthTileSpace[1]];

        // Form the column and combine the tiles in it:
        vector<string> column = { firstTile, secondTile, thirdTile, fourthTile };
        vector<string> combinedTilesColumn = combineTilesInColumn(column);
        // Set up the new board data structure with the combined tiles:
        boardAfterMove[firstTileSpace[0]][firstTileSpace[1]] = combinedTilesColumn[0];
        boardAfterMove[secondTileSpace[0]][secondTileSpace[1]] = combinedTilesColumn[1];
        boardAfterMove[thirdTileSpace[0]][thirdTileSpace[1]] = combinedTilesColumn[2];
        boardAfterMove[fourthTileSpace[0]][fourthTileSpace[1]] = combinedTilesColumn[3];
    }

    return boardAfterMove;
}

vector<string> combineTilesInColumn(vector<string> column) {
    // The column is a list of four tile. Index 0 is the "bottom" of
    // the column, and tiles are pulled "down" and combine if they are the
    // same. For example, combineTilesInColumn([2, BLANK, 2, BLANK])
    // returns [4, BLANK, BLANK, BLANK].
    
    // Copy only the numbers (not blanks) from column to combinedTiles
    vector<string> combinedTiles; // A list of the non-blank tiles in column.

    for (int i = 0; i < 4; ++i) {
        if (column[i] != BLANK) {
            combinedTiles.push_back(column[i]);
        }
    }
    
    // Keep adding blanks until there are 4 tiles:
    while (combinedTiles.size() < 4) { 
        combinedTiles.push_back(BLANK);
    }

    // Combine numbers if the one "above" it is the same, and double it.
    for (int i = 0; i < 3; ++i) { // Skip index 3: it's the topmost space.
        if (combinedTiles[i] == combinedTiles[i + 1]) {
            int help = 0;
            if (combinedTiles[i] != BLANK) { // Double the number in the tile.
                help = stoi(combinedTiles[i]);
                help *= 2;
                combinedTiles[i] = to_string(help);
            }

            // Move the tiles above it down one space:
            for (int j = i + 1; j < 3; ++j) {
                combinedTiles[j] = combinedTiles[j + 1];
            }
            combinedTiles[3] = BLANK; // Topmost space is always BLANK.
        }
    }

    return combinedTiles;
}
#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

class Piece {
    std::string piece_type;
    int color;
    int value; // Chess piece values; add later
    static const std::unordered_map<std::string, int> piece_values;

public:
    Piece() {
        piece_type = "none";
        color = -1;
        value = 0;
    }

    Piece(std::string i_piece_type, int i_color) {
        if(i_color > 1 || i_color < 0) {
            throw std::out_of_range("Unexpected value for color when assigning pieces to players.\n");
        }
        if(piece_values.find(i_piece_type) == piece_values.end()) {
            throw std::invalid_argument("Piece type was invalid whilst constructing piece.\n");
        }


        piece_type = i_piece_type;
        color = i_color;
        value = piece_values.at(i_piece_type);
    }
};

struct Board {
    Piece* board_ranks[8][8];
    Piece* board_files[8][8];

    Board() {
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                board_ranks[i][j] = new Piece();
                board_files[j][i] = board_ranks[i][j];
                *board_ranks[i][j] = Piece();
            }
        }
    }
};

class Player {
public:
    std::string name;
    Board board;
    Player() {
        
    }
};

class Game {
    /*
        This should contain:
            - The players playing
            - The board state
            - Whose turn it is
    */


};
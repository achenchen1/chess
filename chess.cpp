#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "chess.h"

const std::unordered_map<std::string, int> Piece::piece_values = {{"pawn", 1}, {"knight", 3}, {"bishop", 3}, {"rook", 5}, {"queen", 9}};


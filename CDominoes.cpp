/*
 * CDominoes.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#include "CDominoes.h"
#include <stdexcept>
#include <algorithm>

// Constructor
CDominoes::CDominoes() {
    initializePieces();
}

// Destructor
CDominoes::~CDominoes() {
    pieces.clear();
}

// Returns a modifiable reference to the pieces
std::vector<std::pair<int, int>>& CDominoes::getPieces() {
    return pieces;
}

// Draws a piece from the available pieces
std::pair<int, int> CDominoes::drawPiece() {
    if (pieces.empty()) {
        throw std::out_of_range("No more pieces to draw.");
    }
    std::pair<int, int> piece = pieces.back();
    pieces.pop_back();
    return piece;
}

// Initializes pieces and shuffles them
void CDominoes::initializePieces() {
    pieces.clear();
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            pieces.emplace_back(i, j);
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);
}

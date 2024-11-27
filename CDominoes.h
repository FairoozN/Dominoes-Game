/*
 * CDominoes.h
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#ifndef CDOMINOES_H
#define CDOMINOES_H

#include <vector>
#include <utility>
#include <random>

class CDominoes {
private:
    std::vector<std::pair<int, int>> pieces;

public:
    CDominoes();
    ~CDominoes();
    std::vector<std::pair<int, int>>& getPieces();
    std::pair<int, int> drawPiece();
    void initializePieces();
};

#endif

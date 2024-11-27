/*
 * CRandom.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#include "CRandom.h"
#include <algorithm>
#include <random>

// Constructor
CRandom::CRandom() {}

// Shuffle the domino pieces
void CRandom::shuffle(std::vector<std::pair<int, int>>& pieces) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);
}

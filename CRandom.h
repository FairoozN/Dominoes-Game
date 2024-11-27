/*
 * CRandom.h
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#ifndef CRANDOM_H
#define CRANDOM_H

#include <vector>
#include <utility>

class CRandom {
public:
    CRandom();
    void shuffle(std::vector<std::pair<int, int>>& pieces);
};

#endif


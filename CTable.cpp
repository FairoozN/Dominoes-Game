/*
 * CTable.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */


#include "CTable.h"
#include <iostream>

void CTable::displayBoard(const std::vector<std::pair<int, int>>& pieces) {
    for (const auto& piece : pieces) {
        std::cout << "[" << piece.first << "|" << piece.second << "] ";
    }
    std::cout << std::endl;
}




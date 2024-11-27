/*
 * CPlayer.h
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#ifndef CPLAYER_H
#define CPLAYER_H

#include <vector>
#include <utility>

class CPlayer {
private:
    std::vector<std::pair<int, int>> hand;

public:
    CPlayer();
    ~CPlayer();
    void pickPiece(std::pair<int, int> piece);
    void showHand() const;
    bool canPlay(const int head, const int tail) const;
    std::pair<int, int> playPiece(int& head, int& tail);
    bool handEmpty() const;
    size_t handSize() const;
    const std::vector<std::pair<int, int>>& getHand() const;
};

#endif

/*
 * CPlayer.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#include "CPlayer.h"
#include <iostream>
#include <stdexcept>

// Constructor
CPlayer::CPlayer() {}

// Destructor
CPlayer::~CPlayer() {
    hand.clear();
}

// Add a piece to the player's hand
void CPlayer::pickPiece(std::pair<int, int> piece) {
    hand.push_back(piece);
}

// Display the player's hand
void CPlayer::showHand() const {
    for (const auto& piece : hand) {
        std::cout << "[" << piece.first << "|" << piece.second << "] ";
    }
    std::cout << std::endl;
}

// Check if the player can play
bool CPlayer::canPlay(const int head, const int tail) const {
    for (const auto& piece : hand) {
        if (piece.first == head || piece.second == head ||
            piece.first == tail || piece.second == tail) {
            return true;
        }
    }
    return false;
}

// Play a piece and update the head or tail
std::pair<int, int> CPlayer::playPiece(int& head, int& tail) {
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        if (it->first == head || it->second == head || it->first == tail || it->second == tail) {
            std::pair<int, int> piece = *it;
            hand.erase(it);

            // Update head or tail
            if (piece.first == head) head = piece.second;
            else if (piece.second == head) head = piece.first;
            else if (piece.first == tail) tail = piece.second;
            else tail = piece.first;

            return piece;
        }
    }
    throw std::logic_error("No playable piece in hand.");
}

// Check if hand is empty
bool CPlayer::handEmpty() const {
    return hand.empty();
}

// Return the size of the hand
size_t CPlayer::handSize() const {
    return hand.size();
}

// Return the hand for read-only access
const std::vector<std::pair<int, int>>& CPlayer::getHand() const {
    return hand;
}


/*
 * main.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: fairooz
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "CRandom.h"
#include "CTable.h"
#include "CDominoes.h"
#include "CPlayer.h"

std::vector<std::pair<int, int>> dominoTable;
std::mutex tableMutex;
std::mutex turnMutex;
std::condition_variable turnCV;
bool isPlayer1Turn = true;  // True if it's Player 1's turn
bool gameWon = false;       // Flag to indicate if the game has been won
std::string winner;         // To store the winner's name
int consecutivePasses = 0;  // Count the number of consecutive passes
bool gameOver = false;      // Flag to mark when the game is over

// Player turn logic
void playerTurn(CPlayer& player, CDominoes& deck, const std::string& playerName, bool isThisPlayer1, int& head, int& tail) {
    while (true) {
        std::unique_lock<std::mutex> lock(turnMutex);

        // Wait for turn or game over, with a timeout
        turnCV.wait_for(lock, std::chrono::seconds(5), [&]() { return isPlayer1Turn == isThisPlayer1 || gameOver; });

        if (gameOver) {
            return;  // Exit the thread
        }

        {
            std::lock_guard<std::mutex> tableLock(tableMutex);

            // Check if the player has played all their pieces
            if (player.handEmpty()) {
                winner = playerName;
                gameWon = true;
                gameOver = true;  // Mark the game as over
                return;  // Exit the thread
            }

            // If player can play, they do
            if (player.canPlay(head, tail)) {
                auto piece = player.playPiece(head, tail);
                dominoTable.push_back(piece);
                std::cout << playerName << " played: [" << piece.first << "|" << piece.second << "]" << std::endl;
                std::cout << "Updated ";
                CTable().displayBoard(dominoTable);
                consecutivePasses = 0;  // Reset pass counter
            }
            // If they can't play, they draw a piece
            else if (!deck.getPieces().empty()) {
                auto piece = deck.drawPiece();
                player.pickPiece(piece);
                std::cout << playerName << " drew a piece." << std::endl;
                consecutivePasses = 0;  // Reset pass counter
            }
            // If no playable piece and no available pieces, pass the turn
            else {
                std::cout << playerName << " passed." << std::endl;
                consecutivePasses++;
            }
        }

        // Check for game-ending condition: both players pass consecutively
        if (consecutivePasses == 2) {
            gameOver = true;
            return;  // Exit the thread
        }

        // Switch turn
        isPlayer1Turn = !isPlayer1Turn;
        lock.unlock();
        turnCV.notify_all();  // Notify the other player
    }
}

int main() {
    CDominoes deck;
    CRandom randomizer;

    // Shuffle and initialize pieces
    randomizer.shuffle(deck.getPieces());

    CTable table;
    CPlayer player1, player2;

    // Distribute 10 pieces to each player
    for (int i = 0; i < 10; ++i) {
        player1.pickPiece(deck.drawPiece());
        player2.pickPiece(deck.drawPiece());
    }

    // Start the game with one piece on the table
    dominoTable.push_back(deck.drawPiece());
    int head = dominoTable.front().first;
    int tail = dominoTable.front().second;

    // Randomly decide who starts
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    isPlayer1Turn = dist(gen) == 0;
    std::cout << "First player to play: " << (isPlayer1Turn ? "Player 1" : "Player 2") << std::endl;

    // Start game
    std::cout << "Starting table: ";
    table.displayBoard(dominoTable);

    // Multithreaded game: start player threads
    std::thread player1Thread(playerTurn, std::ref(player1), std::ref(deck), "Player 1", true, std::ref(head), std::ref(tail));
    std::thread player2Thread(playerTurn, std::ref(player2), std::ref(deck), "Player 2", false, std::ref(head), std::ref(tail));

    // Wait for players to finish
    player1Thread.join();
    player2Thread.join();

    // Display final results
    if (gameOver) {
        std::cout << "\n============================================================\n";
        std::cout << "Game Over!" << std::endl;
        if (gameWon) {
            std::cout << "Winner: " << winner << std::endl;
        } else {
            std::cout << "The game ended in a draw." << std::endl;
        }

        std::cout << "\nRemaining Pieces:\n";
        std::cout << "Player 1: ";
        player1.showHand();
        std::cout << "Player 2: ";
        player2.showHand();

        std::cout << "\nFinal Dominoes Table:" << std::endl;
        CTable().displayBoard(dominoTable);
        std::cout << "============================================================\n";
    }

    return 0;
}

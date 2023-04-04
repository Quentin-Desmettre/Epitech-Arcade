/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameUtils
*/

#ifndef EPITECH_ARCADE_GAMEUTILS_HPP
#define EPITECH_ARCADE_GAMEUTILS_HPP
#include <string>
#include <fstream>
#include <iostream>

/**
 * @brief Namespace containing utility functions for games
 */
namespace Arcade::Games::GameUtils {
    /**
     * @brief Gets the best score (and the user that made it) of a game.
     * @param gameName The name of the game.
     * @param username A reference to the name of the user.
     * @param score A reference to the score.
     */
    void fetchBestScores(const std::string &gameName, std::string &username, int &score) {
        std::ifstream file("scores/" + gameName + ".score");
        if (!file)
            return;

        // Reset
        username = "N/A";
        score = 0;

        // Fetch username
        if (!std::getline(file, username))
            return;

        // Fetch score
        try {
            std::string line;
            if (!std::getline(file, line))
                throw std::exception(); // To catch in the catch block
            score = std::stoi(line);
        } catch (...) {
            score = 0;
        }
    }

    /**
     * @brief Saves a score for a game.
     *
     * @param gameName The name of the game.
     * @param username The name of the user.
     * @param score The score.
     */
    void saveScore(const std::string &gameName, const std::string &username, int score) {
        std::ofstream file("scores/" + gameName + ".score");

        if (!file)
            return;
        file << username << std::endl << score << std::endl;
    }
}

#endif //EPITECH_ARCADE_GAMEUTILS_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

int loadHighScore(const std::string& filename) {
    std::ifstream file(filename);
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

void saveHighScore(const std::string& filename, int score) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << score;
        file.close();
    }
}
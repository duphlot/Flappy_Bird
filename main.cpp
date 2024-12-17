#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
/*
Author: Phan Thuy Dung (ptdung)
GitHub: duphlot (https/github.com/duphlot)
Program: Flappy Bird
Version: 1.0
Date Start: 16/12/2024
Date End: ?
More information: Read the README.md file in the repository 
                  (https/github.com/duphlot/flappy_bird)
*/
#include "bird.h"
#include "pipe.h"
#include "highScore.h"
#include "layout.h"


// Global variables
int Height;

// Function to reset the game
void resetGame(bool& gameover, std::vector<Pipe>& pipes, Bird& bird, int& score, bool& started, sf::Clock& clock) {
    gameover = false;
    pipes.clear();
    bird.shape.setPosition(100, 400);
    score = 0;
    started = false;
    initializePipes(pipes, Height);
    clock.restart();
}

int main() {
	// Create the window
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(500, 1000), "Flappy Bird");
	// Load font
    sf::Font font;
    font.loadFromFile("assets/font/pixel_font.ttf");
	// Load background
    sf::Texture backgroundTexture;
    sf::Sprite background1, background2;
    initializeBackground(window, backgroundTexture, background1, background2);
	// Load pipes
    std::vector<Pipe> pipes;
    initializePipes(pipes,Height);
	// Load bird
    Bird bird;
    sf::Clock clock;
    bool gameover = false;
	// Load text
    sf::Text startText, restartText;
    initializeText(startText, font, "Press Space to Start", 24, sf::Color::White, 100, 300);
    initializeText(restartText, font, "Press R to Restart", 24, sf::Color::White, 120, 300);
    bool started = false;
    int count = 0;
	// Score
    int score = 0;
    int highScore = loadHighScore("highscore.txt");
	// Main loop
    while (window.isOpen()) {
		// Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // start game logic
        if (!started) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                started = true;
            }
            window.draw(startText);
        }
        if (started && !gameover) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                count++;
                if (count < 2) {
                    bird.flap();
                }
            } else count = 0;

            bird.update();
            for (auto& pipe : pipes) {
                pipe.update();
            }
            if (bird.shape.getPosition().y > window.getSize().y) {
                gameover = true;
            }
            for (const auto& pipe : pipes) {
                if (bird.shape.getGlobalBounds().intersects(pipe.pipeTop.getGlobalBounds()) || bird.shape.getGlobalBounds().intersects(pipe.pipeBot.getGlobalBounds())) {
                    gameover = true;
                }
            }
            if (clock.getElapsedTime().asSeconds() > 2) {
                int newHeight;
                do {
                    newHeight = std::max(200, std::min(Height + (rand() % 600 - 300), 600));
                } while (newHeight == Height);
                Height = newHeight;
                pipes.emplace_back(1200, Height);
                clock.restart();
            }
            if (pipes[0].pipeTop.getPosition().x < bird.shape.getPosition().x) {
                score++;
            }
            pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) { return pipe.pipeTop.getPosition().x < -60; }), pipes.end());

            background1.move(-1, 0);
            background2.move(-1, 0);
            if (background1.getPosition().x + background1.getGlobalBounds().width <= 0) {
                background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0);
            }
            if (background2.getPosition().x + background2.getGlobalBounds().width <= 0) {
                background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            resetGame(gameover, pipes, bird, score, started, clock);
        }

        sf::Text scoreText, highScoreText;
        initializeText(scoreText, font, "Score: " + std::to_string(score), 29, sf::Color::White, 10, 10);
        initializeText(highScoreText, font, "High Score: " + std::to_string(highScore), 24, sf::Color::Red, 10, 50);

        if (gameover) {
            sf::Text gameOverText;
            initializeText(gameOverText, font, "Game Over! Final Score: " + std::to_string(score), 30, sf::Color::Red, 50, 250);
            window.draw(gameOverText);
            window.draw(restartText);
            window.display();
            continue;
        }

        window.draw(background1);
        window.draw(background2);
        window.draw(bird.shape);
        for (const auto& pipe : pipes) {
            window.draw(pipe.pipeTop);
            window.draw(pipe.pipeBot);
        }
        window.draw(scoreText);
        window.draw(highScoreText);
        window.display();

        if (score > highScore) {
            highScore = score;
            saveHighScore("highscore.txt", highScore);
        }
        // end game logic
        sf::sleep(sf::milliseconds(10));
    }
}

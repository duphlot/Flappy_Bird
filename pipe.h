#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

class Pipe {
public:
	Pipe(float x, float height) {
		// Load textures asynchronously
		std::thread loadTexturesThread(&Pipe::loadTextures, this);
		loadTexturesThread.join();

		// top pipe
		pipeTop.setTexture(textureTop);
		pipeTop.setPosition(x, 0);
		pipeTop.setOrigin(30, 0);
        pipeTop.setScale(1.0f, height / textureTop.getSize().y);
		// bottom pipe
		pipeBot.setTexture(textureBot);
		pipeBot.setPosition(x, height + 300);
		pipeBot.setOrigin(30, 0);
        pipeBot.setScale(1.0f, (1000.0f - height - 300.0f) / textureBot.getSize().y);
	}

	void update() {
		pipeTop.move(-2, 0);
		pipeBot.move(-2, 0);
	}

	sf::Sprite pipeTop, pipeBot;

private:
	sf::Texture textureTop, textureBot;

	void loadTextures() {
		if (!textureTop.loadFromFile("assets/images/pipeTop.png") || !textureBot.loadFromFile("assets/images/pipeBot.png")) {
			std::cerr << "Error loading pipe images" << std::endl;
		}
	}
};

// Function to initialize pipes
void initializePipes(std::vector<Pipe>& pipes, int& Height) {
	Height = rand() % 400 + 100;
	pipes.emplace_back(400, Height);
	for (int i = 1; i < 3; i++) {
		int newHeight;
		do {
			newHeight = std::max(200, std::min(Height + (rand() % 600 - 300), 600));
		} while (newHeight == Height);
		Height = newHeight;
		pipes.emplace_back(400 + i * 350, Height);
	}
}

#pragma once
// Function prototypes
void initializeBackground(sf::RenderWindow& window, sf::Texture& backgroundTexture, sf::Sprite& background1, sf::Sprite& background2) {
    backgroundTexture.loadFromFile("assets/images/background.png");
    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);
    background2.setPosition(background1.getGlobalBounds().width, 0);
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
}

// Function to initialize text
void initializeText(sf::Text& text, sf::Font& font, const std::string& str, int size, sf::Color color, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
}

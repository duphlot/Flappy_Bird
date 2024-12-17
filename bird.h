#pragma once  
#include <SFML/Graphics.hpp>
#include <iostream>  
#include <vector>  
#include <cmath>  
#include <algorithm>  
#include <random>  
#include <chrono>  
#include <thread>  

class Bird {  
public:  
    sf::Sprite shape;  
    sf::Texture texture;  
    
    Bird() {  
        if (!texture.loadFromFile("assets/images/bird.png")) {  
            std::cerr << "Error loading bird.png" << std::endl;  
        }  
        shape.setTexture(texture);  
        shape.setScale(0.25f, 0.25f); 
        shape.setOrigin(static_cast<float>(texture.getSize().x) / 2.0f, static_cast<float>(texture.getSize().y) / 2.0f);  
        shape.setPosition(100, 400);
    }  
    
    void flap() {  
        velocity = -3;  
        // head up
        for (int i = 0 ;i < 25; i++){
            shape.setRotation(shape.getRotation() - 1);
        }
    }  
    
    void update() {  
        velocity += 0.08f;  
        shape.move(0, velocity);  

        if (shape.getRotation() < 0) {
            shape.setRotation(shape.getRotation() + 1);
        }

    }  
    
    float velocity = 0;  
};
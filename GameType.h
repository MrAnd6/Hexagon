
#ifndef HEXAGON_GAMETYPE_H
#define HEXAGON_GAMETYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class GameType {
private:
    //Variables
    bool mouseHeld;

    //GUI components
    sf::RectangleShape background;
    std::vector<sf::Text> texts;
    sf::Vector2f mousePos;
    sf::Font font = sf::Font();

    //Private functions
    void initVariables();
    void initGUI();
    void setPos();
    int actionListener();

public:
    //Constructor and destructor
    GameType();
    ~GameType();

    //Public functions
    void update(sf::Vector2f pos, int & state, bool & player);
    void render(sf::RenderTarget & target);
};


#endif //HEXAGON_GAMETYPE_H

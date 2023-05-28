
#ifndef HEXAGON_GAMETYPE_H
#define HEXAGON_GAMETYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class GameType {
private:
    //Variables
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    //GUI components
    sf::RectangleShape background;  ///Background shape for the game type choosing
    std::vector<sf::Text> texts;    ///Vector of text components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window
    sf::Font font = sf::Font();     ///Font for the game type choosing texts

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

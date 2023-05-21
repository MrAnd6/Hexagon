
#ifndef HEXAGON_MENU_H
#define HEXAGON_MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
class Menu {
private:
    //Variables
    sf::RectangleShape mbg;
    sf::Text menu;
    std::vector<sf::Text> texts;
    sf::Font font = sf::Font();
    sf::Vector2f mousePos;
    bool mouseHeld=false;

    //Private functions
    void initTexts();
    void initMenu();
    void setPos(sf::RenderTarget & target);
    int eventListener();

public:
    //Constructor and destructor
    Menu();
    ~Menu();

    //Public functions
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);

};


#endif //HEXAGON_MENU_H

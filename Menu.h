
#ifndef HEXAGON_MENU_H
#define HEXAGON_MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
class Menu {
private:
    ///Variables
    bool mouseHeld=false;           ///Flag indicating if the mouse button is held

    ///GUI components
    sf::RectangleShape mbg;         ///Background shape for the menu
    sf::Text menu;                  ///Text for the menu title
    std::vector<sf::Text> texts;    ///Vector of menu option texts
    sf::Font font = sf::Font();     ///Font for the menu texts
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window


    ///Private functions
    void initTexts();
    void initMenu();
    void setPos(sf::RenderTarget & target);
    int eventListener();

public:
    ///Constructor and destructor
    Menu();
    ~Menu();

    ///Public functions
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);

};


#endif //HEXAGON_MENU_H

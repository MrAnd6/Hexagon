
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
    /**
     * \brief Initializes texts
     */
    void initTexts();

    /**
     * \brief Initializes menu background
     */
    void initMenu();

    /**
     * Sets positions of GUI components
     *
     * \param target Target where components are drawn
     */
    void setPos(sf::RenderTarget & target);

    /**
     * \brief Listens for mouse event happened
     *
     * \return Value that changes state in Window class
     */
    int eventListener();

public:
    ///Constructor and destructor
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    Menu();

    /**
     * \brief Destructor
     */
    ~Menu();

    ///Public functions
    /**
     * \brief Updates mouse position and state
     *
     * \param pos Mouse position
     * \param state State from Window class
     */
    void update(sf::Vector2f pos, int & state);

    /**
     * \brief Draws menu components
     *
     * \param target Target where components are drawn
     */
    void render(sf::RenderTarget & target);

};


#endif //HEXAGON_MENU_H

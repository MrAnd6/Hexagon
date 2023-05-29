
#ifndef HEXAGON_GAMETYPE_H
#define HEXAGON_GAMETYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class GameType {
private:
    ///Variables
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    ///GUI components
    sf::RectangleShape background;  ///Background shape for the game type choosing
    std::vector<sf::Text> texts;    ///Vector of text components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window
    sf::Font font = sf::Font();     ///Font for the game type choosing texts

    ///Private functions
    /**
     * \brief Initializes default values of variables
     */
    void initVariables();

    /**
     * \brief Initializes GUI components
     */
    void initGUI();

    /**
     * \brief Sets positions of GUI components
     */
    void setPos();

    /**
     * \brief Listens for mouse event happened
     *
     * \return Value that sets game type
     */
    int actionListener();

public:
    ///Constructor and destructor
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    GameType();

    /**
     * \brief Destructor
     */
    ~GameType();

    ///Public functions
    /**
     * \brief Updates state and which game type was chosen
     *
     * \param pos Mouse position
     * \param state State from the Window class
     * \param player Variable from Window class that is used to check who will play(player or computer)
     */
    void update(sf::Vector2f pos, int & state, bool & player);

    /**
     * \brief Draws menu components
     *
     * \param target Target where components are drawn
     */
    void render(sf::RenderTarget & target);
};


#endif //HEXAGON_GAMETYPE_H


#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include "Hexagon.cpp"

class Saver {
private:
    ///Variables
    int state;                      ///Current saver state
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    ///GUI components
    sf::RectangleShape bg;          ///Background shape for loading or saving the game
    std::vector<sf::Text> texts;    ///Vector of texts components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window
    sf::Font font;                  ///Font for the saver texts

    ///Private functions
    /**
     * \brief Initializes default values of variables
     */
    void initVariables();

    /**
     * \brief Initializes GUI elements of saver class
     */
    void initGUI();

    /**
     * \brief Event listener for the event happened
     */
    void eventListener();

    /**
     * \brief Sets positions of GUI elements
     */
    void setPos();

    /**
     * \brief Saves the game data to a file
     *
     * Saves the game data to the file that user entered to the console
     */
    void saveGame();
public:
    ///Cunstructor and Destructor
    /**
    * \brief Default constructor
    *
    * Using other methods initializes and sets default values and positions
    */
    Saver();

    /**
     * \brief Destructor
     */
    ~Saver();

    ///Public functions
    /**
     * \brief Loads game data from file
     *
     * Loads game data from file that user entered to the console to a vector of ints,
     * then calls loadGame() method in Hexagon class to convert this data
     */
    void loadGame();

    /**
     * \brief Updates state
     *
     * \param pos Mouse position
     * \param state State from Window class
     */
    void update(sf::Vector2f pos, int & state);

    /**
     * \brief Draws GUI elements
     *
     * \param target Target where components are drawn
     */
    void render(sf::RenderTarget & target);

    /**
     * \brief Chages state
     *
     * \param state New state
     */
    void changeState(int state);
};


#endif //HEXAGON_SAVER_H


#ifndef HEXAGON_SCOREBOARD_H
#define HEXAGON_SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>
#include <cmath>

class ScoreBoard {
private:
    ///Variables
    static std::vector<int> scores; ///Static vector to store the scores
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    ///GUI components
    sf::RectangleShape bg;          ///Background shape for the score board
    sf::Font font;                  ///Font for the score board texts
    std::vector<sf::Text> texts;    ///Vector of text components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window

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
     * \return Value that changes state in Window class
     */
    int eventListener();

    /**
     * \brief Reads scores from the file
     */
    void read();

    /**
     * \brief Writes scores to the file
     */
    static void write();

    /**
     * \brief Updates texts that lists scores on the screen
     *
     * Using string stream reads scores from scores vector and
     * updates texts that are listing them on the screen
     */
    void updateScores();
public:
    ///Constructor and Destructor
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    ScoreBoard();

    /**
     * \brief Destructor
     */
    ~ScoreBoard();

    ///Public functions

    /**
     * \brief Saves result
     *
     * \param result Vector with results
     *
     * Adds new results to the vector with them if it has less that 5 results or
     * if new results have a greater difference than the previous, then
     * calls write() method to write new result into file
     */
    static void save(sf::Vector2i result);

    /**
     * \brief Updates state and updates scores
     *
     * \param pos Mouse position
     * \param state State from Window class
     */
    void update(sf::Vector2f pos, int & state);

    /**
     * \brief Renders GUI components in the window
     *
     * \param target Target where components are drawn
     */
    void render(sf::RenderTarget & target);
};

#endif //HEXAGON_SCOREBOARD_H

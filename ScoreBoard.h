
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
    //Variables
    static std::vector<int> scores; ///Static vector to store the scores
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    //GUI components
    sf::RectangleShape bg;          ///Background shape for the score board
    sf::Font font;                  ///Font for the score board texts
    std::vector<sf::Text> texts;    ///Vector of text components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window

    //Private functions
    void initVariables();
    void initGUI();
    void setPos();
    int eventListener();
    void read();
    static void write();
    void updateScores();
public:
    //Constructor and Destructor
    ScoreBoard();
    ~ScoreBoard();

    //Public functions
    static void save(sf::Vector2i result);
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
};

#endif //HEXAGON_SCOREBOARD_H

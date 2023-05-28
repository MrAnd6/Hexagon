
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
    static std::vector<int> scores;
    bool mouseHeld;

    //GUI components
    sf::RectangleShape bg;
    sf::Font font;
    std::vector<sf::Text> texts;
    sf::Vector2f mousePos;

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

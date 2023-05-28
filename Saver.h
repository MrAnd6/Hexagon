
#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include "Hexagon.cpp"

class Saver {
private:
    //Variables
    int state;                      ///Current saver state
    bool mouseHeld;                 ///Flag indicating if mouse button is held

    //GUI components
    sf::RectangleShape bg;          ///Background shape for loading or saving the game
    std::vector<sf::Text> texts;    ///Vector of texts components
    sf::Vector2f mousePos;          ///Vector of mouse position relative to the window
    sf::Font font;                  ///Font for the saver texts

    //Private functions
    void initVariables();
    void initGUI();
    void eventListener();
    void setPos();
    void saveGame();
public:
    //Cunstructor and Destructor
    Saver();
    ~Saver();

    //Public functions
    void loadGame();
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
    void changeState(int state);
};


#endif //HEXAGON_SAVER_H

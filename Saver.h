
#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include "Hexagon.cpp"

class Saver {
private:
    //Variables
    int state;
    bool mouseHeld;

    //GUI components
    sf::RectangleShape bg;
    std::vector<sf::Text> texts;
    sf::Vector2f mousePos;
    sf::Font font;

    //Private functions
    void initVariables();
    void initGUI();
    void eventListener();
    void setPos();
    void loadGame();
    void saveGame();
public:
    //Cunstructor and Destructor
    Saver();
    ~Saver();

    //Public functions
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
    void changeState(int state);
};


#endif //HEXAGON_SAVER_H

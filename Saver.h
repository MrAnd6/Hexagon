
#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include <fstream>

class Saver {
private:
    //Variables
    std::vector<int> scores;
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
public:
    //Cunstructor and Destructor
    Saver();
    ~Saver();

    //Public functions
    int* loadGame();
    static void saveGame();
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
    void changeState(int state);
};


#endif //HEXAGON_SAVER_H

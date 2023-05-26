

#ifndef HEXAGON_WINDOW_H
#define HEXAGON_WINDOW_H

#include "Menu.cpp"
#include "Hexagon.cpp"
#include "GameType.cpp"

class Window {
private:
    //Variables
    int state;
    int prevState;
    bool player;

    //GUI components
    sf::RenderWindow* window;
    sf::VideoMode vm;
    sf::Event ev;
    sf::Vector2f mousePos;

    //Objects of helping classes
    Menu menu;
    Hexagon hexagon;
    GameType gameType;
    Saver saver;

    //Private functions
    void initWindow();
    void initVariables();
    void eventListener();
    void updateMousePos();

public:
    //Constructor and destructor
    Window();
    ~Window();

    //Getters
    bool working() const;


    //Functions
    void update();
    void render();
};


#endif //HEXAGON_WINDOW_H

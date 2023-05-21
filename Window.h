

#ifndef HEXAGON_WINDOW_H
#define HEXAGON_WINDOW_H

#include "Menu.cpp"
#include "Hexagon.cpp"

class Window {
private:
    //Variables
    sf::RenderWindow* window;
    sf::VideoMode vm;
    sf::Event ev;
    int state;
    int prevState;
    bool player;
    sf::Vector2f mousePos;

    //Objects of helping classes
    Menu menu;
    Hexagon hexagon;

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
    void changeState(int state);



};


#endif //HEXAGON_WINDOW_H

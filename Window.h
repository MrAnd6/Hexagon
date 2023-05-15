

#ifndef HEXAGON_WINDOW_H
#define HEXAGON_WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Window {
private:
    //Variables
    sf::RenderWindow* window;
    sf::VideoMode vm;
    sf::Event ev;
    int state;

    //Private functions
    void initWindow();
    void initVariables();
    void eventListener();

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

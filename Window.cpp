

#include "Window.h"

//Private functions
void Window::initWindow() {
    this->vm.size = sf::Vector2u{1200,800};
    this->window = new sf::RenderWindow(this->vm, "Hexxagon", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Window::initVariables() {
    this->window = nullptr;
    this->state=0;
}

void Window::eventListener() {
    /**
        Listens for the events that happened
     */
    while(this->window->pollEvent(this->ev)){
        switch (this->ev.type) {
            case sf::Event::Closed: //Close button pressed
                this->window->close();
                break;
        }
    }

}

void Window::updateMousePos() {
    sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
    this->mousePos = this->window->mapPixelToCoords(pos);
}

//Constructor and destructor
Window::Window(){
    this->initVariables();
    this->initWindow();
}

Window::~Window() {
    delete this->window;
}

//Getters
bool Window::working() const {
    return this->window->isOpen();
}

//Functions
void Window::update() {
    this->updateMousePos();
    this->eventListener();
    if(prevState != state){
        switch(state){
            case 1:
                this->hexagon.eraseField();
        }
        prevState = state;
    }
    switch (state){
        case 0: //menu
            this->menu.update(this->mousePos, this->state);
            break;
        case 1: //New game
            this->hexagon.update(this->mousePos, this->state);
            break;
        case 2: //Load Game
            break;
        case 3: //Score board
            break;
        case 4: //Chooser of game type
            break;
    }

}

void Window::render() {
    /**
           Renders objects in window

           -clears frame
           -render objects
           -display frame

     */

    this->window->clear();
    switch (state){
        case 0: //menu
            this->menu.render(*this->window);
            break;
        case 1: //Hexagon game
            this->hexagon.render(*this->window);
            break;
        case 2: //Load Game
            break;
        case 3: //Score board
            break;
        case 4: //Chooser of game type
            break;
    }

    this->window->display();
}

void Window::changeState(int state) {
    this->state=state;
}




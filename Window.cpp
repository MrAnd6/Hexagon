//
// Created by User on 14.05.2023.
//

#include "Window.h"

//Private functions
void Window::initWindow() {
    this->vm.size = sf::Vector2u{1200,800};
    this->window = new sf::RenderWindow(this->vm, "Hexxagon", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Window::initVariables() {
    this->window = nullptr;
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

//Constructor and destructor
Window::Window() {
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
    this->eventListener();
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
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }

    this->window->display();
}




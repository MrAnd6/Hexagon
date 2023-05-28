

#include "Window.h"

//Private functions
void Window::initVariables() {
    this->window = nullptr;
    this->state=4;
}

void Window::initGUI() {
    this->vm.size = sf::Vector2u{1200,800};
    this->window = new sf::RenderWindow(this->vm, "Hexxagon", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    if(!this->texture.loadFromFile("Galaxy.png"))
        std::cout << " ERROR::WINDOW::TEXTURE::COULD NOT LOAD TEXTURE FROM FILE" << "\n";
    this->bg.setSize({1200,800});
    this->bg.setTexture(&texture);
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
    this->initGUI();
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
                if(prevState == 2)
                  saver.loadGame();
                this->hexagon.setGameType(player);
                break;
            case 2:
                this->saver.changeState(2);
                break;
            case 5:
                this->saver.changeState(5);
                break;
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
            this->saver.update(this->mousePos, this->state);
            break;
        case 3: //Score board
            this->scores.update(this->mousePos, this->state);
            break;
        case 4: //Chooser of game type
            this->gameType.update(this->mousePos, this->state, this->player);
            break;
        case 5: //Save the game
            this->saver.update(this->mousePos, this->state);
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
    if(this->state != 1)
        this->window->draw(bg);
    switch (state){
        case 0: //menu
            this->menu.render(*this->window);
            break;
        case 1: //Hexagon game
            this->hexagon.render(*this->window);
            break;
        case 2: //Load Game
            this->saver.render(*this->window);
            break;
        case 3: //Score board
            this->scores.render(*this->window);
            break;
        case 4: //Chooser of game type
            this->gameType.render(*this->window);
            break;
        case 5://Save game
            this->saver.render(*this->window);
            break;
    }

    this->window->display();
}






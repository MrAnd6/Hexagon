
#include "Saver.h"

//Private functions

void Saver::initVariables() {
    this->mouseHeld = false;
}

void Saver::initGUI() {
    bg.setSize({400,300});
    bg.setFillColor(sf::Color(200, 0, 250));
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::HEXAGON::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    texts.push_back(sf::Text(font, "Load Game", 50));
    texts.push_back(sf::Text(font, "Please enter a file path\nto the console", 30));
}

void Saver::setPos() {

}

void Saver::eventListener() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!mouseHeld) {
            mouseHeld = true;

        } else mouseHeld = false;
    }
}

//Constructor and Destructor
Saver::Saver() {
    this->initVariables();
    this->initGUI();
}

Saver::~Saver() {
    delete this;
}

//Public functions

void Saver::update(sf::Vector2f pos, int & state) {
    this->mousePos = pos;
    this->eventListener();
}

void Saver::render(sf::RenderTarget &target) {

}

void Saver::saveGame() {

}

void Saver::changeState(int state) {

}

int *Saver::loadGame() {
    return nullptr;
}

